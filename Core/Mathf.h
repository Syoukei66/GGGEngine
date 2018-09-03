#pragma once

#include "../Core/NativeType.h"
#include "PerlinNoiseGenerator.h"
#include "RandomGenerator.h"

namespace Mathf
{

#undef PI
static const T_FLOAT PI = 3.14159265358979f;
static const T_FLOAT PI_2 = PI * 2.0f;
static const T_FLOAT PI_1_2 = PI * 0.5f;
static const T_FLOAT PI_1_4 = PI * 0.25f;

static const T_FLOAT DEG_TO_RAD = 1.0f / 180.0f * PI;
static const T_FLOAT RAD_TO_DEG = 1.0f / PI * 180.0f;

inline T_FLOAT DegToRad(T_FLOAT deg)
{
  return deg / 180.0f * PI;
}

inline T_FLOAT RadToDeg(T_FLOAT rad)
{
  return rad / PI * 180.0f;
}

inline T_FLOAT Lerp(T_FLOAT a, T_FLOAT b, T_FLOAT t)
{
  return a * (b - a) * t;
}

template<typename T>
inline T Clamp(T value, T min, T max)
{
  if (value < min)
  {
    return min;
  }
  if (value > max)
  {
    return max;
  }
  return value;
}

inline T_UINT16 CalcTwoPowerValue(T_UINT16 val)
{
  T_UINT16 t = 1;
  while (t < val)
  {
    t <<= 1;
  }
  return t;
}

inline PerlinNoiseGenerator& PerlinNoise()
{
  static PerlinNoiseGenerator generator;
  return generator;
}

inline RondomGenerator& Random()
{
  static RondomGenerator generator;
  return generator;
}

}