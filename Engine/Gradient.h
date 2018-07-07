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
    TColor color;
    GradientTable(T_UINT8 id, T_FLOAT location, TColor color)
      : id(id)
      , location(location)
      , color(color)
    {}
  };

public:
  Gradient();

public:
  void Reset();
  GradientTable& AddColor(T_FLOAT location, const TColor& color);
  void RemoveColor(const GradientTable& id);
  void RemoveColor(T_UINT8 id);
  TColor Evaluate(T_FLOAT time) const;

private:
  T_UINT8 id_max_;
  std::vector<GradientTable> table_;
};