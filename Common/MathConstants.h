#pragma once

#include "NativeType.h"

namespace MathConstants
{

#undef PI
static const T_FLOAT PI = 3.14159265358979f;
static const T_FLOAT PI_2 = PI * 2.0f;
static const T_FLOAT PI_1_2 = PI * 0.5f;
static const T_FLOAT PI_1_4 = PI * 0.25f;

static const T_FLOAT DEG_TO_RAD = 1.0f / 180.0f * PI;
static const T_FLOAT RAD_TO_DEG = 1.0f / PI * 180.0f;

static T_FLOAT DegToRad(T_FLOAT deg)
{
  return deg / 180.0f * PI;
}

static T_FLOAT RadToDeg(T_FLOAT rad)
{
  return rad / PI * 180.0f;
}

}