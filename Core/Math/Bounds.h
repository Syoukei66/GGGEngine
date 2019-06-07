#pragma once

#include "Vector3.h"

struct Bounds
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SERIALIZABLE(Bounds)
  {
    archive(center);
    archive(extents);
  }
  
  // =================================================================
  // Data Members
  // =================================================================
public:
  TVec3f center;
  TVec3f extents;
};