#pragma once

namespace MathConstants
{

#undef PI
static const float PI = 3.14159265358979f;
static const float PI_2 = PI * 2.0f;
static const float PI_1_2 = PI * 0.5f;
static const float PI_1_4 = PI * 0.25f;

static T_FLOAT DegToRad(T_FLOAT deg)
{
  return deg / 180.0f * PI;
}

static T_FLOAT RadToDeg(T_FLOAT rad)
{
  return rad / PI * 180.0f;
}

}