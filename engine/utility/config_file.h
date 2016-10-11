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
  // The desired behavior if an error occurs. Note: WARN_COUT is available to 
  // log warnings without using the logger. This is required to log early 
  // initialization errors that occur before the Logging subsystems has been 
  // initialized. 
  enum ErrorHandling {
    IGNORE,
    WARN,
    WARN_COUT,
    SHUT_DOWN
  };

  ConfigFile(std::string filename, ErrorHandling file_error_handling = WARN, ErrorHandling property_error_handling = WARN);
  template<typename T> bool ReadProperty(std::string property, T* out_value, T default = T()) const {
    if (file_read_successfully_ == false) {
      DoPropertyErrorHandling("The configuration file could not be opened correctly. Therefore property cannot be read.", property);
      *out_value = default;
      return false;
    }
    try {
      *out_value = config_properties_.get<T>(property);
    } catch (boost::property_tree::ptree_error error) {
      DoPropertyErrorHandling(error.what(), property);
      *out_value = default;
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
  void DoFileErrorHandling(std::string message, unsigned long int line) const;
  void DoPropertyErrorHandling(std::string message, std::string property) const;

  std::string filename_;
  ErrorHandling file_error_handling_;
  ErrorHandling property_error_handling_;
  boost::property_tree::ptree config_properties_;
  bool file_read_successfully_{ false };
};

} // namespace

#endif // ENGINE_UTILITY_CONFIGFILE_H_