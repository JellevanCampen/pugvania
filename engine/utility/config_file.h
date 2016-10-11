#pragma once
#ifndef ENGINE_UTILITY_CONFIGFILE_H_
#define ENGINE_UTILITY_CONFIGFILE_H_

#include <string>
#include "boost\property_tree\ptree.hpp"

namespace engine {

// Represents a configuration file. Used to read and write configuration 
// values. 
class ConfigFile {
 public:
  // The desired behavior if an error occurs.
  enum ErrorHandling {
    IGNORE,
    WARN,
    SHUT_DOWN
  };

  ConfigFile(std::string filename, ErrorHandling file_error_handling, ErrorHandling property_error_handling);
  template<typename T> bool ReadProperty(std::string property, T* out_value, T default = T()) {
    if (file_read_successfully_ == false) {
      DoPropertyErrorHandling("The configuration file could not be opened correctly. Therefore properties cannot be read.");
      return false;
    }
    try {
      *out_value = config_properties_.get<T>(property);
    } catch (boost::property_tree::ptree_error error) {
      DoPropertyErrorHandling(error.what());
      return false;
    }
    return true;
  }
  template<typename T> bool WriteProperty(std::string property, T value) {
    config_properties_.put(property, value);
    boost::property_tree::ini_parser::write_ini(filename_, config_properties_);
  }

 private:
  bool ReadIniFile();
  void DoFileErrorHandling(std::string message, unsigned long int line);
  void DoPropertyErrorHandling(std::string message);

  std::string filename_;
  ErrorHandling file_error_handling_;
  ErrorHandling property_error_handling_;
  boost::property_tree::ptree config_properties_;
  bool file_read_successfully_{ false };
};

} // namespace

#endif // ENGINE_UTILITY_CONFIGFILE_H_