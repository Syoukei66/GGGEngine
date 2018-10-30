#pragma once

namespace Mathf
{

#undef PI
constexpr T_FLOAT PI = 3.14159265358979f;
constexpr T_FLOAT PI_2 = PI * 2.0f;
constexpr T_FLOAT PI_1_2 = PI * 0.5f;
constexpr T_FLOAT PI_1_4 = PI_1_2 * 0.5f;
constexpr T_FLOAT PI_1_8 = PI_1_4 * 0.5f;
constexpr T_FLOAT PI_1_16 = PI_1_8 * 0.5f;
constexpr T_FLOAT PI_1_32 = PI_1_16 * 0.5f;
constexpr T_FLOAT PI_1_64 = PI_1_32 * 0.5f;

constexpr T_FLOAT DEG_TO_RAD = 1.0f / 180.0f * PI;
constexpr T_FLOAT RAD_TO_DEG = 1.0f / PI * 180.0f;

constexpr T_FLOAT DegToRad(T_FLOAT deg)
{
  return deg / 180.0f * PI;
}

constexpr T_FLOAT RadToDeg(T_FLOAT rad)
{
  return rad / PI * 180.0f;
}

template <typename T>
constexpr T Lerp(const T& a, const T& b, T_FLOAT t)
{
  return a * (b - a) * t;
}

template <typename T>
constexpr T Clamp(const T& value, const T& min, const T& max)
{
  return std::max(min, std::min(max, value));
}

template <typename T>
constexpr T CalcTwoPowerValue(const T& val)
{
  T t = 1;
  while (t < val)
  {
    t <<= 1;
  }
  return t;
}

}