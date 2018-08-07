#pragma once

#include <string>
#include <vector>
#include "../Common/Vector2.h"
#include "../Common/Vector3.h"
#include "../Common/Vector4.h"
#include "../Common/Color.h"
#include "../Common/Matrix4x4.h"
#include "../Common/Bounds.h"

class BaseConverterTest
{
protected:
  void Compare(bool a, bool b);
  void Compare(T_UINT8 a, T_UINT8 b);
  void Compare(T_UINT32 a, T_UINT32 b);
  void Compare(T_INT32 a, T_INT32 b);
  void Compare(T_FLOAT a, T_FLOAT b);
  void Compare(const std::string& a, const std::string& b);
  void Compare(const TVec2f& a, const TVec2f& b);
  void Compare(const TVec3f& a, const TVec3f& b);
  void Compare(const TVec4f& a, const TVec4f& b);
  void Compare(const TColor& a, const TColor& b);
  void Compare(const Matrix4x4& a, const Matrix4x4& b);
  void Compare(const Bounds& a, const Bounds& b);

  void PushState(const std::string& state);
  void PopState();
  void AddMessage(const std::string& message);
  void AddMessage(const std::string& a, const std::string& b);
  template<typename T>
  void AddMessage(T a, T b)
  {
    AddMessage(std::to_string(a), std::to_string(b));
  }

public:
  void ResetMessages();
  void PrintMessages();

public:
  inline bool HasMessage()
  {
    return this->messages_.size() > 0;
  }

private:
  std::vector<std::string> state_stack_;
  std::vector<std::string> messages_;
};
