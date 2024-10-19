#include "../../Crow-Engine/CrowEngine/libs/cppr/cppr.hpp"

struct MyStruct
{
  std::vector<int> vector = {5, 0};
  std::string* num[4];
  REFLECT()
};

REFLECT_STRUCT_BEGIN(MyStruct)
  REFLECT_STRUCT_MEMBER(vector)
  REFLECT_STRUCT_MEMBER(num)
REFLECT_STRUCT_END()

int main()
{
  std::string numbers[4] = {"hi","Hello","y0","m8m"};

  MyStruct myStruct{{4,2}, {&numbers[0], &numbers[1], &numbers[2], &numbers[3]}};

  myStruct.structDesc.To_Json("dump.txt", &myStruct);
  myStruct.num[0] = &numbers[2];

  myStruct.structDesc.From_Json("dump.txt", &myStruct);

  std::cout << static_cast<void*>(myStruct.num[0]) << std::endl;
  std::cout << static_cast<void*>(myStruct.num[1]) << std::endl;
  std::cout << static_cast<void*>(myStruct.num[2]) << std::endl;
  std::cout << static_cast<void*>(myStruct.num[3]) << std::endl << std::endl;
  return 0;
}