#include "Color.h"

#include <stdlib.h>
#include "Util.h"

#include "NativeMethod.h"

// =================================================================
// Color (8bit unsigned int [0~255])
// =================================================================

// =================================================================
// Constants
// =================================================================
const T_UINT8 Color::GMIN = 0;
const T_UINT8 Color::GMAX = 255;

const T_UINT32 Color::PACKED_WHITE = 0xFFFFFFFF;

const Color Color::WHITE = Color(255, 255, 255);
const Color Color::GRAY = Color(128, 128, 128);
const Color Color::BLACK = Color(0, 0, 0);

const Color Color::RED = Color(255, 0, 0);
const Color Color::GREEN = Color(0, 255, 0);
const Color Color::BLUE = Color(0, 0, 255);
const Color Color::YELLOW = Color(255, 255, 0);
const Color Color::LIGHT_BLUE = Color(0, 255, 255);
const Color Color::PINK = Color(255, 0, 255);
const Color Color::PURPLE = Color(128, 0, 128);

// =================================================================
// Constructor / Destructor
// =================================================================
Color::Color()
  : TColor<T_UINT8>(GMAX, GMAX, GMAX, GMAX)
{}

Color::Color(T_UINT8 r, T_UINT8 g, T_UINT8 b)
  : TColor<T_UINT8>(r, g, b, GMAX)
{}

Color::Color(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
  : TColor<T_UINT8>(r, g, b, a)
{}

// =================================================================
// Operators
// =================================================================
Color::operator Color4F() const
{
  return Color4F(
    (T_FLOAT)this->r_ / GMAX,
    (T_FLOAT)this->g_ / GMAX,
    (T_FLOAT)this->b_ / GMAX,
    (T_FLOAT)this->a_ / GMAX
  );
}

// =================================================================
// Setter / Getter
// =================================================================
void Color::PackColor()
{
  NativeMethod::Graphics().Graphics_PackColor4u8(
    &this->packed_color_,
    this->r_,
    this->g_,
    this->b_,
    this->a_
  );
  this->color_dirty_ = false;
}

T_PACKED_COLOR_UINT32 Color::GetPackedColor()
{
  if (this->color_dirty_)
  {
    this->PackColor();
  }
  return this->packed_color_;
}

// =================================================================
// Color (float [0.0f~1.0f])
// =================================================================
// =================================================================
// Constants
// =================================================================
const T_FLOAT Color4F::GMIN = 0.0f;
const T_FLOAT Color4F::GMAX = 1.0f;

const T_UINT32 Color4F::PACKED_WHITE = 0xFFFFFFFF;

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
  : TColor<T_FLOAT>(GMAX, GMAX, GMAX, GMAX)
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  : TColor<T_FLOAT>(r, g, b, GMAX)
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  : TColor<T_FLOAT>(r, g, b, a)
{}

void Color4F::PackColor()
{
  NativeMethod::Graphics().Graphics_PackColor4u8(
    &this->packed_color_,
    (T_UINT8)(this->r_ * Color::GMAX),
    (T_UINT8)(this->g_ * Color::GMAX),
    (T_UINT8)(this->b_ * Color::GMAX),
    (T_UINT8)(this->a_ * Color::GMAX)
  );
  this->color_dirty_ = false;
}

// =================================================================
// Setter / Getter
// =================================================================
T_PACKED_COLOR_UINT32 Color4F::GetPackedColor()
{
  if (this->color_dirty_)
  {
    this->PackColor();
  }
  return this->packed_color_;
}