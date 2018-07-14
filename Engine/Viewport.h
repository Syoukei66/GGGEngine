#pragma once

#include "Director.h"
#include "Vector2.h"
#include "Geometry.h"

struct Viewport
{
  TVec2i position;
  TSize size;
  T_FLOAT z_min, z_max;

  Viewport()
    : position()
    , size((T_FLOAT)Director::GetInstance()->GetScreenWidth(), (T_FLOAT)Director::GetInstance()->GetScreenHeight())
    , z_min()
    , z_max()
  {}

  Viewport(const TVec2i& position, const TSize& size, T_FLOAT z_min, T_FLOAT z_max)
    : position(position)
    , size(size)
    , z_min(z_min)
    , z_max(z_max)
  {}
};