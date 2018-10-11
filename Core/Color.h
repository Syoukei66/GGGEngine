#pragma once
#include <algorithm>
#include "NativeType.h"
#undef min
#undef max

union TColor
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const TColor WHITE;
  static const TColor GRAY;
  static const TColor BLACK;

  static const TColor RED;
  static const TColor GREEN;
  static const TColor BLUE;
  static const TColor YELLOW;
  static const TColor LIGHT_BLUE;
  static const TColor PINK;
  static const TColor PURPLE;

  // =================================================================
  // Create Method
  // =================================================================
public:
  static TColor CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b);
  static TColor CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);

  inline static TColor Lerp(const TColor& a, const TColor&b, T_FLOAT t)
  {
    return a * (1 - t) + b * t;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TColor();
  TColor(T_FLOAT r, T_FLOAT g, T_FLOAT b);
  TColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a);

  // =================================================================
  // Operators
  // =================================================================
public:
  const TColor operator+ (const TColor& other) const
  {
    return TColor(
      this->data[0] + other.data[0],
      this->data[1] + other.data[1],
      this->data[2] + other.data[2],
      this->data[3] + other.data[3]
    );
  }

  const TColor operator* (T_FLOAT v) const
  {
    return TColor(
      this->data[0] * v,
      this->data[1] * v,
      this->data[2] * v,
      this->data[3] * v
    );
  }

  const TColor operator* (const TColor& other) const
  {
    return TColor(
      this->data[0] * other.data[0],
      this->data[1] * other.data[1],
      this->data[2] * other.data[2],
      this->data[3] * other.data[3]
    );
  }
  
  TColor& operator*= (const TColor& other)
  {
    this->data[0] = this->data[0] * other.data[0];
    this->data[1] = this->data[1] * other.data[1];
    this->data[2] = this->data[2] * other.data[2];
    this->data[3] = this->data[3] * other.data[3];
    return *this;
  }

  const TColor operator/ (const TColor& other) const
  {
    return TColor(
      this->data[0] / other.data[0],
      this->data[1] / other.data[1],
      this->data[2] / other.data[2],
      this->data[3] / other.data[3]
    );
  }

  TColor& operator/= (const TColor& other)
  {
    this->data[0] = this->data[0] / other.data[0];
    this->data[1] = this->data[1] / other.data[1];
    this->data[2] = this->data[2] / other.data[2];
    this->data[3] = this->data[3] / other.data[3];
    return *this;
  }

  bool operator== (const TColor& other)
  {
    return
      this->data[0] == other.data[0] &&
      this->data[1] == other.data[1] &&
      this->data[2] == other.data[2] &&
      this->data[3] == other.data[3]
      ;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  inline bool Equals(const TColor& c) const
  {
    return 
      this->data[0] == c.data[0] &&
      this->data[1] == c.data[1] &&
      this->data[2] == c.data[2] &&
      this->data[3] == c.data[3]
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b) const
  {
    return 
      this->data[0] == r &&
      this->data[1] == g &&
      this->data[2] == b
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a) const
  {
    return
      this->data[0] == r &&
      this->data[1] == g &&
      this->data[2] == b &&
      this->data[3] == a
      ;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  T_PACKED_COLOR_UINT32 GetPackedColor() const;

  // =================================================================
  // Data Member
  // =================================================================
public:
  struct
  {
    T_FLOAT r, g, b, a;
  };
  T_FLOAT data[4];

};
