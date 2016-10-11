#include "config_file.h"
#include "boost/property_tree/ini_parser.hpp"
#include "boost/algorithm/string.hpp"
#include "engine.h"

namespace engine {

ConfigFile::ConfigFile(std::string filename, ErrorHandling file_error_handling, ErrorHandling property_error_handling) {
  filename_ = filename;
  file_error_handling_ = file_error_handling;
  property_error_handling_ = property_error_handling;
  
  // Select the correct parser depending on the filetype
  std::string extension = filename.substr(filename.rfind('.'));
  boost::to_lower(extension);
  if (extension.compare("ini") == 0)
    file_read_successfully_ = ReadIniFile();
}

bool ConfigFile::ReadIniFile() {
  try {
    boost::property_tree::ini_parser::read_ini(filename_, config_properties_);
  }
  catch (boost::property_tree::ini_parser_error err) {
    std::stringstream message;
    switch (file_error_handling_) {
    case IGNORE:
      return false;
    case WARN:
      message << "Error reading ini configuration file. Default config values will be used. File ("
        << err.filename()
        << " at line "
        << err.line()
        << "): "
        << err.message();
      g_log(message.str(), log::kWarning);
      return false;
    case SHUT_DOWN:
      message << "Error reading ini configuration file. This is a critical error, shutting down the engine. File ("
        << err.filename()
        << " at line "
        << err.line()
        << "): "
        << err.message();
      g_log(message.str(), log::kError);
      std::cout << "Press enter to shut down the engine... ";
      std::cin.get();
      exit(1);
      return false;
    }
  }
  return true;
}

} // namespace