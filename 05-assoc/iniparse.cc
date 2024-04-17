/**********************************************************************************************
 * NIU CSCI 340 Section 0003                                                                  *
 * Assignment 5                                                                              *
 * Phoenix Chheav - Z1966108 - phoenixchh                                                     *
 *                                                                                            *
 *   I certify that everything I am submitting is either provided by the professor for use in *
 * the assignment, or work done by me personally. I understand that if I am caught submitting *
 * the work of others (including StackOverflow or ChatGPT) as my own is an act of Academic    *
 * Misconduct and will be punished as such.                                                   *
 *                                                                                            *
 **********************************************************************************************/
// Implement these functions to make the INI file parsing features work.
// See details in README.md.

// This will be compiled to iniparse.o and linked in when needed by make.

#include "settings.h"
#include "iniparse.h"
#include <sstream>
#include <string>

bool not_whitespace(int character){
  return !std::isspace(character);
}

/**
 * @brief function to read data from 'input' stream a line at a time
 * 
 * @param input an input stream to read from.
 * @param verbosity verbosity level, controls how much debug info will be shown
 * @return INI_CONFIG that built up from input file
 */
INI_CONFIG read_ini(std::istream &input, int verbosity) {
   INI_CONFIG config;
  std::string current;

  std::string lines;
  int count_line = 0;

  //erase leading whitespace
  while(std::getline(input, lines)){

    ++count_line;
    //remove leading whitespace
    lines.erase(std::remove_if(lines.begin(), lines.end(), ::isspace), lines.end());
    //lines.erase(lines.begin(), std::find_if(lines.begin(), lines.end(), not_whitespace));

    //remove trailing whitespace
    //lines.erase(std::find_if(lines.rbegin(), lines.rend(), not_whitespace).base(), lines.end()); //base: convert the reverse iterator back into a regular iterator

    //if it's empty line skip
    if(lines.empty()){
      continue;
    }
    //";" are to be config as commens, and ignored
    if(lines[0] == ';'){
      continue;
    }
    if(lines[0] == '['){

      size_t close_bracket = lines.find(']'); 
      if(close_bracket != std::string::npos){
        current = lines.substr(1, close_bracket - 1);
       config[current] = {};
       if (config[current].empty())
       {
        config.erase(current);
       }
      }else if(verbosity >= 2){
        std::cerr << "Error: invalid section" << std::endl;
      }

    }else if(lines.find('=') != std::string::npos){//if it is not invalid
      if(!current.empty()){
        size_t position = lines.find("=");
        std::string key = lines.substr(0, position);
        std::string value = lines.substr(position + 1);


        config[current][key] = value;
        if(verbosity >= 1){
         std::cout << "Section = " << current << ", Key: " << key << ", Value: " << value << std::endl;
       }
      }else if(verbosity >= 2){
        //the pair of key-value are not in any of the section
        std::cerr << "Error: Invalid key-value pair." << std::endl;
      }
    }else if(verbosity >= 2){
      std::cerr << "Error: Invalid line." << std::endl;
    }
  } 
  return config;
}
/**
 * @brief output all the keys foind in 'config' so that the output could be used
 *        with 'read_ini' to restore the same config(except for any section that have no keys).
 * 
 * @param ost output stream to write the INI data to
 * @param config the `INI_CONFIG` we are writing to the output stream
 * @return true if output stream is valid
 * @return false if ost is invalid
 */
bool write_ini( std::ostream & ost, const INI_CONFIG & config ) {
  //if ost is not valid
  if(!ost){
    return false;
  }

  for(const auto& section : config){
    if(!section.second.empty()){
      ost << "[" << section.first << "]" << std::endl;

      for(const auto& key : section.second){
        ost << key.first << " = " << key.second << std::endl;
      }
    }
  }

  return true;
}

/**
 * @brief print the configuration data from config with one key per line
 * 
 * @param ost output stream to print to
 * @param config the `INI_CONFIG` whose info we would like to print
 */
void print_ini( std::ostream & ost, const INI_CONFIG & config ) {
  if(config.empty()){
    ost << "Configuration is empty. Nothing to print\n";
  }
    for(const auto& section : config){
      if(section.second.empty()){
        ost << "Section \"" << section.first << "\" is empty\n";
      }

      for(const auto& key : section.second){
        ost << section.first << "." << key.first << " = \"" << key.second << "\"" << std::endl;
      }
    }
  ost << std::endl;
}

/**
 * @brief function to add a new empty map to holds the keys if the section is not yet created.
 *        the section may contain later and add it into the outer map using the section name as the key
 * 
 * @param config the 'INI_CONFIG' to add the section to
 * @param section string contain the name if the sectino to add
 */
void add_ini_section(INI_CONFIG & config, const std::string &section) {
  if(config.find(section) == config.end()){
    config[section] = std::map<std::string, std::string>();
  }
}

/**
 * @brief remove a specific section and its key if it's already exist
 * 
 * @param config 'INI_CONFIG' to remove the section from
 * @param section string contain the name of the section to remove
 */
void remove_ini_section(INI_CONFIG & config, const std::string &section) {
  auto section_it = config.find(section);
  if(section_it != config.end()){
    config.erase(section_it);
  }
}

/**
 * @brief Get the ini key object
 * 
 * @param config 'INI_CONFIG' to retireve the key from
 * @param section string containing the name if the section containing the key
 * @param key string contain the name of key whose value is desired
 * @return the value
 */
std::string get_ini_key(const INI_CONFIG &config, const std::string &section, const std::string &key) {
  auto section_it = config.find(section);
  if(section_it != config.end()){
    const std::map<std::string, std::string> &section_key = section_it->second;
    auto key_it = section_key.find(key);
    if(key_it != section_key.end()){
      return key_it->second;
    }
  }
  return "";
}

/**
 * @brief Set the ini key object
 * 
 * @param config `INI_CONFIG` to set the key in.
 * @param section string containing the name of the section containing the key desired
 * @param key string containing the name of the key whose value should be set.
 * @param value string for the new value of the key.
 */
void set_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key, const std::string & value) {
  auto &section_key = config[section]; //find or add section
  section_key[key] = value;//set it to 'value'
}

/**
 * @brief this function will remove the given key in the given section
 * 
 * @param config to remove the key from.
 * @param section string containing the name of the section containing the key.
 * @param key string containing the name of the key to remove.
 * @return number of keys actually removed
 */
int remove_ini_key(INI_CONFIG &config, const std::string &section, const std::string &key) {
  auto section_it = config.find(section);
  if(section_it != config.end()){
    auto &section_key = section_it->second;
    auto key_it = section_key.find(key);
    if(key_it != section_key.end()){
      section_key.erase(key_it);
      return 1;
    }
  }

  return 0;
}
