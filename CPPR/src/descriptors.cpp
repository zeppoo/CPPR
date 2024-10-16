#include "../../../Crow-Engine/CrowEngine/libs/cppr/descriptors.hpp"

namespace reflect
{
  TypeDescriptor::TypeDescriptor(const char *memberName, size_t size, size_t memberOffset)
  {
    offset = memberOffset;
  }

  StructDescriptor::StructDescriptor(const char* name, size_t size) {}

  StructDescriptor::StructDescriptor(void (*init)(StructDescriptor*)) : StructDescriptor{nullptr, 0} {
    init(this);
  }

  template<typename T>
  void StructDescriptor::AddMember(const char *memberName, size_t size, size_t memberOffset)
  {
    TypeDescriptor member{memberName, size, memberOffset};
    member.type = create_type_info<T>(memberName);
    if (member.type->kind == UNKNOWN) {
      throw std::runtime_error("Unkown Type detected, member name: " + std::string(memberName));
      return;
    }
    members.push_back(std::move(member));
  }

  void *StructDescriptor::GetMemberMemAdress(void *reference, size_t offset)
  {
    char *bytePtr = static_cast<char *>(reference);
    return bytePtr + offset;
  }

  void StructDescriptor::To_Json(const char* filePath, void* structRef)
  {
    std::string content = "\"" + std::string(name) + "\": {\n";
    for (const auto &member: members)
    {
      void *memberPtr = GetMemberMemAdress(structRef, member.offset);
      content += member.type->serialize(memberPtr);
    }
    content += "}";
    split(content, '\n');
    WriteToFile(filePath, content);
  }

  void StructDescriptor::From_Json(const char* filePath, void* structRef)
  {
    std::string content = ReadFromFile(filePath);
    strip(content, ' ');

    for (auto &member: members)
    {
      void *memberPtr = GetMemberMemAdress(structRef, member.offset);
      member.type->deserialize(content, memberPtr);
    }
  }
}