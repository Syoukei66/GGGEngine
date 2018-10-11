#include "Color.h"
#include "NativeProcess.h"

// =================================================================
// Constants
// =================================================================
const TColor TColor::WHITE = TColor(1.0f, 1.0f, 1.0f);
const TColor TColor::GRAY = TColor(0.5f, 0.5f, 0.5f);
const TColor TColor::BLACK = TColor(0.0f, 0.0f, 0.0f);

const TColor TColor::RED = TColor(1.0f, 0.0f, 0.0f);
const TColor TColor::GREEN = TColor(0.0f, 1.0f, 0.0f);
const TColor TColor::BLUE = TColor(0.0f, 0.0f, 1.0f);
const TColor TColor::YELLOW = TColor(1.0f, 1.0f, 0.0f);
const TColor TColor::LIGHT_BLUE = TColor(0.0f, 1.0f, 1.0f);
const TColor TColor::PINK = TColor(1.0f, 0.0f, 1.0f);
const TColor TColor::PURPLE = TColor(0.5f, 0.0f, 0.5f);

// =================================================================
// Create Method
// =================================================================
TColor TColor::CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b)
{
  return TColor( r / 255.0f, g / 255.0f, b / 255.0f );
}

TColor TColor::CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
{
  return TColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

// =================================================================
// Constructor / Destructor
// =================================================================
TColor::TColor()
  : data{ 1.0f, 1.0f, 1.0f, 1.0f }
{}

TColor::TColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  : data{ r, g, b, 1.0f }
{}

TColor::TColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  : data{ r, g, b, a }
{}

// =================================================================
// Setter / Getter
// =================================================================
T_PACKED_COLOR_UINT32 TColor::GetPackedColor() const
{
  T_PACKED_COLOR_UINT32 ret;
  NativeProcess::Graphics::PackColor4u8(
    &ret,
    (T_UINT8)(this->data[0] * 255),
    (T_UINT8)(this->data[1] * 255),
    (T_UINT8)(this->data[2] * 255),
    (T_UINT8)(this->data[3] * 255)
  );
  return ret;
}
