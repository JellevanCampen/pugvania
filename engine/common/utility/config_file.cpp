#include "config_file.h"
#include <sstream>
#include "boost/property_tree/ini_parser.hpp"
#include "boost/algorithm/string.hpp"
#include "engine.h"

namespace engine {

ConfigFile::ConfigFile(std::string filename, ErrorHandling file_error_handling, ErrorHandling property_error_handling) {
  filename_ = filename;
  file_error_handling_ = file_error_handling;
  property_error_handling_ = property_error_handling;
  
  // Select the correct parser depending on the filetype
  std::string extension = filename.substr(filename.rfind('.') + 1);
  boost::to_lower(extension);
  if (extension.compare("ini") == 0) {
    file_read_successfully_ = ReadIniFile();
    return;
  }
  std::stringstream message;
  message << "The config file could not be read because there is no parser for the "
    << extension
    << " file format.";
  DoFileErrorHandling(message.str(), 0);
}

bool ConfigFile::ReadIniFile() {
  try {
    boost::property_tree::ini_parser::read_ini(filename_, config_properties_);
  }
  catch (boost::property_tree::ini_parser_error error) {
    DoFileErrorHandling(error.what(), error.line());
    return false;
  }
  return true;
}

void ConfigFile::DoFileErrorHandling(std::string message, unsigned long int line) const {
  std::stringstream log_message;
  switch (file_error_handling_) {
  case kIGNORE:
    return;
  case kWARN:
    log_message << "Error reading ini configuration file. Default config values will be used. File ("
      << filename_
      << " at line "
      << line
      << "): "
      << message;
    g_log(log_message.str(), log::kWarning);
    return;
  case kWARN_COUT:
    log_message << "Error reading ini configuration file. Default config values will be used. File ("
      << filename_
      << " at line "
      << line
      << "): "
      << message;
    std::cout << log_message.str() << std::endl;
    return;
  case kSHUT_DOWN:
    log_message << "Error reading ini configuration file. This is a critical error, shutting down the engine. File ("
      << filename_
      << " at line "
      << line
      << "): "
      << message;
    g_log(log_message.str(), log::kError);
    std::cout << "Press enter to shut down the engine... ";
    std::cin.get();
    exit(1);
    return;
  }
}

void ConfigFile::DoPropertyErrorHandling(std::string message, std::string property) const {
  std::stringstream log_message;
  switch (property_error_handling_) {
  case kIGNORE:
    return;
  case kWARN:
    log_message << "Error reading configuration file property <"
      << property
      << ">. Default config value will be used. File ("
      << filename_
      << "):  "
      << message;
    g_log(log_message.str(), log::kWarning);
    return;
  case kWARN_COUT:
    log_message << "Error reading configuration file property <"
      << property
      << ">. Default config value will be used. File ("
      << filename_
      << "):  "
      << message;
    std::cout << log_message.str() << std::endl;
    return;
  case kSHUT_DOWN:
    log_message << "Error reading configuration file property. This is a critical error, shutting down the engine. File ("
      << filename_
      << "):  "
      << message;
    g_log(log_message.str(), log::kError);
    std::cout << "Press enter to shut down the engine... ";
    std::cin.get();
    exit(1);
    return;
  }
}

} // namespace