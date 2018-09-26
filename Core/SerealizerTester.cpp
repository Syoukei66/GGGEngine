#include "SerializerTester.h"
#include "SerializerTestMacro.hpp"
#include <iostream>

void SerializerTester::Compare(bool a, bool b)
{
  COMPARE(bool)
}

void SerializerTester::Compare(unsigned char a, unsigned char b)
{
  COMPARE(unsigned char)
}

void SerializerTester::Compare(T_UINT32 a, T_UINT32 b)
{
  COMPARE(T_UINT32)
}

void SerializerTester::Compare(T_INT32 a, T_INT32 b)
{
  COMPARE(T_INT32)
}

void SerializerTester::Compare(T_FLOAT a, T_FLOAT b)
{
  if (isnan(a) && isnan(b))
  {
    return;
  }
  COMPARE(T_FLOAT)
}

void SerializerTester::Compare(size_t a, size_t b)
{
  COMPARE(size_t)
}

void SerializerTester::Compare(const std::string& a, const std::string& b)
{
  COMPARE(std::string)
}

void SerializerTester::Compare(const TVec2f& a, const TVec2f& b)
{
  PushState("vec2");
  COMPARE_ATTR(x);
  COMPARE_ATTR(y);
  PopState();
}

void SerializerTester::Compare(const TVec3f& a, const TVec3f& b)
{
  PushState("vec3");
  COMPARE_ATTR(x);
  COMPARE_ATTR(y);
  COMPARE_ATTR(z);
  PopState();
}

void SerializerTester::Compare(const TVec4f& a, const TVec4f& b)
{
  PushState("vec4");
  COMPARE_ATTR(x);
  COMPARE_ATTR(y);
  COMPARE_ATTR(z);
  COMPARE_ATTR(w);
  PopState();
}

void SerializerTester::Compare(const TColor& a, const TColor& b)
{
  PushState("TColor");
  COMPARE_ATTR(r);
  COMPARE_ATTR(g);
  COMPARE_ATTR(b);
  COMPARE_ATTR(a);
  PopState();
}

void SerializerTester::Compare(const Matrix4x4& a, const Matrix4x4& b)
{
  PushState("TMatrix");
  COMPARE_ATTR(_11);  COMPARE_ATTR(_12);  COMPARE_ATTR(_13);  COMPARE_ATTR(_14);
  COMPARE_ATTR(_21);  COMPARE_ATTR(_22);  COMPARE_ATTR(_23);  COMPARE_ATTR(_24);
  COMPARE_ATTR(_31);  COMPARE_ATTR(_32);  COMPARE_ATTR(_33);  COMPARE_ATTR(_34);
  COMPARE_ATTR(_41);  COMPARE_ATTR(_42);  COMPARE_ATTR(_43);  COMPARE_ATTR(_44);
  PopState();
}

void SerializerTester::Compare(const Bounds& a, const Bounds& b)
{
  PushState("Bounds");
  COMPARE_ATTR(center);
  COMPARE_ATTR(extents);
  PopState();
}

void SerializerTester::PushState(const std::string& state)
{
  this->state_stack_.push_back(state);
}

void SerializerTester::PopState()
{
  this->state_stack_.pop_back();
}

void SerializerTester::AddMessage(const std::string& message)
{
  std::string full_message = "";
  for (const std::string& state : this->state_stack_)
  {
    full_message.append(state);
    full_message.append(" > ");
  }
  full_message.append(message);
  this->messages_.push_back(full_message);
}

void SerializerTester::AddMessage(const std::string& a, const std::string& b)
{
  std::string message;
  message.append("a(");
  message.append(a);
  message.append(") != b(");
  message.append(b);
  message.append(")");
  AddMessage(message);
}

void SerializerTester::ResetMessages()
{
  this->messages_.clear();
}

void SerializerTester::PrintMessages()
{
  if (this->messages_.size() == 0)
  {
    std::cout << "perfect converted." << std::endl << std::endl;
    return;
  }
  std::cout << "- discover the difference of the converted data! -" << std::endl;
  for (const std::string& message : this->messages_)
  {
    std::cout << message << std::endl;
  }
  std::cout << "--------------------------------------------------" << std::endl << std::endl;
}
