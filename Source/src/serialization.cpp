#include "../include/serialization.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

namespace reflect
{
  void WriteToFile(const char* path, std::string content)
  {
    std::ofstream outFile(path);
    if (!outFile) {
      std::cerr << "Error opening file!" << std::endl;
    }
    outFile << content;
    outFile.close();
  }

  std::string ReadFromFile(const char* path)
  {
    std::ifstream file(path);
    if (!file) {std::cerr << "Error opening file!" << std::endl;}
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string fileContent = buffer.str();
    file.close();
    return fileContent;
  }

  std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    for (char ch : str) {
      if (ch == delimiter) {
        if (!token.empty()) {
          result.push_back(token);
          token.clear();
        }
      } else {
        token += ch;
      }
    }
    // Add the last token if not empty
    if (!token.empty()) {
      result.push_back(token);
    }
    return result;
  }

  void strip(std::string& str, const char delimiter)
  {
    str.erase(std::remove(str.begin(), str.end(), delimiter), str.end());
  }

  std::string extract_json_value(const std::string& json, const std::string& field, const std::string& parent) {
    auto start_pos = json.find("\"" + parent + "\":");
    start_pos = json.find("\"" + field + "\":", start_pos);
    if (start_pos == std::string::npos) return ""; // field not found

    start_pos = json.find_first_of(":", start_pos) + 1;
    auto end_pos = json.find_first_of(",\n}", start_pos);
    std::string value = json.substr(start_pos, end_pos - start_pos);

    strip(value, '\"');
    strip(value, '\'');
    strip(value, ',');
    return value;
  }

  std::vector<std::string> extract_json_values(const std::string& json, const std::string& field, const std::string& parent) {
    std::vector<std::string> result;
    std::size_t idPos = json.find("\""+ field + "\":[");
    // Find the array part between '[' and ']'
    size_t start = json.find('[', idPos);
    size_t end = json.find(']', start);

    // Extract the substring containing the array elements
    std::string array_content = json.substr(start + 1, end - start - 1);
    strip(array_content, '\"');
    strip(array_content, '\'');

    // Split the string by commas to get individual elements
    result = split(array_content, ',');
    return result;
  }
}