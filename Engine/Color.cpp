#include "Color.h"
#include "NativeProcess.h"

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
  : col{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  : col{ r, g, b, 1.0f }
{}

Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  : col{ r, g, b, a }
{}

// =================================================================
// Setter / Getter
// =================================================================
T_PACKED_COLOR_UINT32 Color4F::GetPackedColor()
{
  T_PACKED_COLOR_UINT32 ret;
  NativeProcess::Graphics::PackColor4u8(
    &ret,
    this->col[0] * 255,
    this->col[1] * 255,
    this->col[2] * 255,
    this->col[3] * 255
  );
  return ret;
}
