#include "Color.h"

#include <stdlib.h>
#include "Util.h"

#include "NativeMethod.h"

// =================================================================
// Constants
// =================================================================
const Color4F Color4F::WHITE = Color4F(1.0f, 1.0f, 1.0f);
const Color4F Color4F::GRAY = Color4F(0.5f, 0.5f, 0.5f);
const Color4F Color4F::BLACK = Color4F(0.0f, 0.0f, 0.0f);

const Color4F Color4F::RED = Color4F(1.0f, 0.0f, 0.0f);
const Color4F Color4F::GREEN = Color4F(0.0f, 1.0f, 0.0f);
const Color4F Color4F::BLUE = Color4F(0.0f, 0.0f, 1.0f);
const Color4F Color4F::YELLOW = Color4F(1.0f, 1.0f, 0.0f);
const Color4F Color4F::LIGHT_BLUE = Color4F(0.0f, 1.0f, 1.0f);
const Color4F Color4F::PINK = Color4F(1.0f, 0.0f, 1.0f);
const Color4F Color4F::PURPLE = Color4F(0.5f, 0.0f, 0.5f);

// =================================================================
// Constructor / Destructor
// =================================================================
Color4F::Color4F()
  : col_{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  : col_{ r, g, b, 1.0f }
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  : col_{ r, g, b, a }
{}

// =================================================================
// Setter / Getter
// =================================================================
void Color4F::SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
{
  this->col_[0] = r;
  this->col_[1] = g;
  this->col_[2] = b;
}

void Color4F::SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
{
  this->col_[0] = r;
  this->col_[1] = g;
  this->col_[2] = b;
  this->col_[3] = a;
}
