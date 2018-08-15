#pragma once

#include "../Core/NativeType.h"

namespace Mathf
{

T_FLOAT Lerp(T_FLOAT a, T_FLOAT b, T_FLOAT t)
{
  return a * (b - a) * t;
}

}