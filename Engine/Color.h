#pragma once
#include <algorithm>
#include "NativeType.h"
#undef min
#undef max

union Color4F
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const Color4F WHITE;
  static const Color4F GRAY;
  static const Color4F BLACK;

  static const Color4F RED;
  static const Color4F GREEN;
  static const Color4F BLUE;
  static const Color4F YELLOW;
  static const Color4F LIGHT_BLUE;
  static const Color4F PINK;
  static const Color4F PURPLE;

  // =================================================================
  // Create Method
  // =================================================================
public:
  static Color4F CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b);
  static Color4F CreateBy4BitFormat(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);

  inline static Color4F Lerp(const Color4F& a, const Color4F&b, T_FLOAT t)
  {
    return a * (1 - t) + b * t;
  }

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Color4F();
  Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b);
  Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a);

  // =================================================================
  // Operators
  // =================================================================
public:
  const Color4F operator+ (const Color4F& other) const
  {
    return Color4F(
      this->col[0] + other.col[0],
      this->col[1] + other.col[1],
      this->col[2] + other.col[2],
      this->col[3] + other.col[3]
    );
  }

  const Color4F operator* (T_FLOAT v) const
  {
    return Color4F(
      this->col[0] * v,
      this->col[1] * v,
      this->col[2] * v,
      this->col[3] * v
    );
  }

  const Color4F operator* (const Color4F& other) const
  {
    return Color4F(
      this->col[0] * other.col[0],
      this->col[1] * other.col[1],
      this->col[2] * other.col[2],
      this->col[3] * other.col[3]
    );
  }
  
  Color4F& operator*= (const Color4F& other)
  {
    this->col[0] = this->col[0] * other.col[0];
    this->col[1] = this->col[1] * other.col[1];
    this->col[2] = this->col[2] * other.col[2];
    this->col[3] = this->col[3] * other.col[3];
    return *this;
  }

  const Color4F operator/ (const Color4F& other) const
  {
    return Color4F(
      this->col[0] / other.col[0],
      this->col[1] / other.col[1],
      this->col[2] / other.col[2],
      this->col[3] / other.col[3]
    );
  }

  Color4F& operator/= (const Color4F& other)
  {
    this->col[0] = this->col[0] / other.col[0];
    this->col[1] = this->col[1] / other.col[1];
    this->col[2] = this->col[2] / other.col[2];
    this->col[3] = this->col[3] / other.col[3];
    return *this;
  }

  bool operator== (const Color4F& other)
  {
    return
      this->col[0] == other.col[0] &&
      this->col[1] == other.col[1] &&
      this->col[2] == other.col[2] &&
      this->col[3] == other.col[3]
      ;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  inline bool Equals(const Color4F& c) const
  {
    return 
      this->col[0] == c.col[0] &&
      this->col[1] == c.col[1] &&
      this->col[2] == c.col[2] &&
      this->col[3] == c.col[3]
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b) const
  {
    return 
      this->col[0] == r &&
      this->col[1] == g &&
      this->col[2] == b
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a) const
  {
    return
      this->col[0] == r &&
      this->col[1] == g &&
      this->col[2] == b &&
      this->col[3] == a
      ;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  T_PACKED_COLOR_UINT32 GetPackedColor();

  // =================================================================
  // Data Member
  // =================================================================
public:
  struct
  {
    T_FLOAT r, g, b, a;
  };
  T_FLOAT col[4];

};
