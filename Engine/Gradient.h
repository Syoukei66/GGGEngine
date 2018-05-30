#pragma once

#include <vector>
#include "Color.h"

class Gradient
{
public:
  struct GradientTable
  {
    T_UINT8 id;
    T_FLOAT location;
    Color4F color;
  };

public:
  Gradient();

public:
  void Reset();
  GradientTable& AddColor(T_FLOAT location, const Color4F& color);
  void RemoveColor(const GradientTable& id);
  void RemoveColor(T_UINT8 id);
  Color4F Evaluate(T_FLOAT time);

private:
  T_UINT8 id_max_;
  std::vector<GradientTable> table_;
};