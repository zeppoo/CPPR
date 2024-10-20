#include "include/test.hpp"

int main()
{
  std::string names[4] = {"hi","Hello","y0","m8m"};

  MyStruct myStruct{3 , {4,2}, {&names[0], &names[1], &names[2], &names[3]}};

  SerializeStructsToFile("dump.txt", &myStruct);

  DeserializeStructsFromFile("dump.txt", &myStruct);

  std::cout << "\nTest 1 Complete!\n" << std::endl;

  std::string names2[4] = {"hi","Hello","y0","m8m"};

  MyStruct2 myStruct2{6 , {8,4}, {&names2[0], &names2[1], &names2[2], &names2[3]}};

  SerializeStructsToFile("dump.txt", &myStruct2);

  DeserializeStructsFromFile("dump.txt", &myStruct2);

  std::cout << "\nTest 2 Complete!\n" << std::endl;

  std::string names3[4] = {"hi","Hello","y0","m8m"};

  MyStruct3 myStruct3{9 , {12,6}, {&names3[0], &names3[1], &names3[2], &names3[3]}};

  SerializeStructsToFile("dump.txt", &myStruct3);

  DeserializeStructsFromFile("dump.txt", &myStruct3);

  std::cout << "\nTest 3 Complete!\n" << std::endl;

  MyStruct4 myStruct4{0, myStruct, myStruct2, myStruct3};

  SerializeInternalStructsToFile("dump.txt", &myStruct4, &myStruct4.internal1, &myStruct4.internal2,&myStruct4.internal3);

  DeserializeStructsFromFile("dump.txt", &myStruct4, &myStruct, &myStruct2,&myStruct3);

  std::cout << "Test 4 Complete" << std::endl;

  std::cout << "\nAll Tests Successful!\n" << std::endl;
  return 0;
}