#include "Color.h"
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
// Create Method
// =================================================================
Color4F Color4F::CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b)
{
  return Color4F( r / 255.0f, g / 255.0f, b / 255.0f );
}

Color4F Color4F::CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  return Color4F(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

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
T_PACKED_COLOR_UINT32 Color4F::GetPackedColor()
{
  T_PACKED_COLOR_UINT32 ret;
  NativeMethod::Graphics().Graphics_PackColor4u8(
    &ret,
    this->col_[0] * 255,
    this->col_[1] * 255,
    this->col_[2] * 255,
    this->col_[3] * 255
  );
  return ret;
}

void Color4F::SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
{
  this->col_[0] = std::min(1.0f, std::max(0.0f, r));
  this->col_[1] = std::min(1.0f, std::max(0.0f, g));
  this->col_[2] = std::min(1.0f, std::max(0.0f, b));
}

void Color4F::SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
{
  this->col_[0] = std::min(1.0f, std::max(0.0f, r));
  this->col_[1] = std::min(1.0f, std::max(0.0f, g));
  this->col_[2] = std::min(1.0f, std::max(0.0f, b));
  this->col_[3] = std::min(1.0f, std::max(0.0f, a));
}

void Color4F::GetColors(T_FLOAT color[4]) const
{
  color[0] = this->col_[0];
  color[1] = this->col_[1];
  color[2] = this->col_[2];
  color[3] = this->col_[3];
}
