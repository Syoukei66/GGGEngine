#ifndef HAL_ENGINE_UTIL_UTIL_H
#define HAL_ENGINE_UTIL_UTIL_H

#include <stdlib.h>
#include <time.h>

#include "NativeType.h"

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

  static bool RANDOM_INITIALIZED = false;
  
  inline void RandomInit()
  {
    //srand(time(0));
    RANDOM_INITIALIZED = true;
  }

  inline T_INT32 GetRandom(T_INT32 min, T_INT32 max)
  {
    if (!RANDOM_INITIALIZED)
    {
      RandomInit();
    }
    return min + (T_INT32)(((T_DOUBLE)rand() / (RAND_MAX + 1)) * (T_DOUBLE)(max - min));
  }

  inline T_FLOAT GetRandom(T_FLOAT min, T_FLOAT max)
  {
    if (!RANDOM_INITIALIZED)
    {
      RandomInit();
    }
    return min + (T_FLOAT)(((T_DOUBLE)rand() / (RAND_MAX + 1)) * (T_DOUBLE)(max - min));
  }

  inline T_DOUBLE GetRandom(T_DOUBLE min, T_DOUBLE max)
  {
    if (!RANDOM_INITIALIZED)
    {
      RandomInit();
    }
    return min + (T_DOUBLE)(((T_DOUBLE)rand() / (RAND_MAX + 1)) * (T_DOUBLE)(max - min));
  }

  inline T_UINT32 GetRandom(T_UINT32 max)
  {
    return GetRandom(0, max);
  }

};

#endif//HAL_ENGINE_UTIL_UTIL_H
