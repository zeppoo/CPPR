#include "../../../Crow-Engine/CrowEngine/libs/cppr/cppr_tests.hpp"

namespace reflect
{
  int Test1(const char* filePath)
  {
    char initials = 'T';
    std::string name1 = "Mark";
    std::string name2 = "Elon";
    std::string name3 = "Jeff";
    Struct1 myStruct = {30, true, 1234567890, {5, 3, 3}, &initials, {&name1, &name2, &name3}};

    try {
      myStruct.structDesc.To_Json(filePath, &myStruct);
      myStruct.structDesc.From_Json(filePath, &myStruct);
    }
    catch (const std::exception& e) {
      // Catch the exception and print the error message
      std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    return 0;
  }
}
