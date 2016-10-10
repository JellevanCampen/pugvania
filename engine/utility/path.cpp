#include "utility\path.h"
#include <sstream>
#include <iostream>
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"
#include <boost/algorithm/string.hpp>

namespace engine {

void Path::Initialize() {
  boost::property_tree::ptree pt;
  try {
    boost::property_tree::ini_parser::read_ini(root_ + "path_config.ini", pt);
    
    // Iterate over all keys in the paths section of path_config.ini and add 
    // them to the map
    for (auto path : pt.get_child("paths"))
      directories_.insert(std::pair<std::string, std::string>(path.first, path.second.data()));

    const void* adress = static_cast<const void*>(this);
    std::stringstream init_message;
    init_message << "Path subsystem initialized at 0x" << adress;
    // Printing the error directly to the console as the Path subsystem is 
    // initialized before the logger. 
    std::cout << init_message.str() << std::endl;
  }
  catch (boost::property_tree::ini_parser_error err) {
    std::stringstream error_message;
    error_message << "Error reading path config, unable to access resources. File ("
      << err.filename()
      << " at line "
      << err.line()
      << "): "
      << err.message();
    // Printing the error directly to the console as the Path subsystem is 
    // initialized before the logger. 
    std::cout << error_message.str() << std::endl;
    // TODO(Jelle): Offer to create a test file to indicate what directory the 
    // engine considers its root directory. Shut down the Engine afterwards as 
    // this is a critical error. 
  }
}

void Path::Terminate() {
  std::cout << "Logging subsystem terminated." << std::endl;
}

const std::string & Path::operator[](const std::string directory) const {
  if (directories_.count(directory) == 0) {
    std::stringstream error_message;
    std::string dir{ directory };
    boost::to_upper(dir);
    error_message << dir << "_DIRECTORY_NOT_FOUND";
    return error_message.str();
  }
  return root_ + directories_.at(directory);
}

} // namespace