#ifndef HAL_ENGINE_UTIL_UTIL_H
#define HAL_ENGINE_UTIL_UTIL_H

#include <stdlib.h>
#include <time.h>

#include "NativeType.h"
#include "RandomGenerator.h"
#include "PerlinNoiseGenerator.h"

namespace Util
{
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

  inline RondomGenerator& Rondom()
  {
    static RondomGenerator generator;
    return generator;
  }

  inline PerlinNoiseGenerator& PerlinNoise()
  {
    static PerlinNoiseGenerator generator;
    return generator;
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

};

#endif//HAL_ENGINE_UTIL_UTIL_H
