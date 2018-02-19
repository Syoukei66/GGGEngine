#pragma once
#include <algorithm>
#include "NativeType.h"
#undef min
#undef max

class Color4F
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
      this->col_[0] + other.col_[0],
      this->col_[1] + other.col_[1],
      this->col_[2] + other.col_[2],
      this->col_[3] + other.col_[3]
    );
  }

  const Color4F operator* (T_FLOAT v) const
  {
    return Color4F(
      this->col_[0] * v,
      this->col_[1] * v,
      this->col_[2] * v,
      this->col_[3] * v
    );
  }

  const Color4F operator* (const Color4F& other) const
  {
    return Color4F(
      this->col_[0] * other.col_[0],
      this->col_[1] * other.col_[1],
      this->col_[2] * other.col_[2],
      this->col_[3] * other.col_[3]
    );
  }
  
  Color4F& operator*= (const Color4F& other)
  {
    this->col_[0] = this->col_[0] * other.col_[0];
    this->col_[1] = this->col_[1] * other.col_[1];
    this->col_[2] = this->col_[2] * other.col_[2];
    this->col_[3] = this->col_[3] * other.col_[3];
    return *this;
  }

  const Color4F operator/ (const Color4F& other) const
  {
    return Color4F(
      this->col_[0] / other.col_[0],
      this->col_[1] / other.col_[1],
      this->col_[2] / other.col_[2],
      this->col_[3] / other.col_[3]
    );
  }

  Color4F& operator/= (const Color4F& other)
  {
    this->col_[0] = this->col_[0] / other.col_[0];
    this->col_[1] = this->col_[1] / other.col_[1];
    this->col_[2] = this->col_[2] / other.col_[2];
    this->col_[3] = this->col_[3] / other.col_[3];
    return *this;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  inline bool Equals(const Color4F& c) const
  {
    return 
      this->col_[0] == c.col_[0] &&
      this->col_[1] == c.col_[1] &&
      this->col_[2] == c.col_[2] &&
      this->col_[3] == c.col_[3]
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b) const
  {
    return 
      this->col_[0] == r &&
      this->col_[1] == g &&
      this->col_[2] == b
      ;
  }

  inline bool Equals(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a) const
  {
    return
      this->col_[0] == r &&
      this->col_[1] == g &&
      this->col_[2] == b &&
      this->col_[3] == a
      ;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  T_PACKED_COLOR_UINT32 GetPackedColor();
  void SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b);
  void SetColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a);
  void GetColors(T_FLOAT color[4]) const;
  inline const T_FLOAT* GetColors() const
  {
    return this->col_;
  }

  inline void SetRed(T_FLOAT r)
  {
    this->col_[0] = std::min(1.0f, std::max(0.0f, r));
  }
  inline T_FLOAT GetRed() const
  {
    return this->col_[0];
  }

  inline void SetGreen(T_FLOAT g)
  {
    this->col_[1] = std::min(1.0f, std::max(0.0f, g));
  }
  inline T_FLOAT GetGreen() const
  {
    return this->col_[1];
  }

  inline void SetBlue(T_FLOAT b)
  {
    this->col_[2] = std::min(1.0f, std::max(0.0f, b));
  }
  inline T_FLOAT GetBlue() const
  {
    return this->col_[2];
  }

  inline void SetAlpha(T_FLOAT a)
  {
    this->col_[3] = std::min(1.0f, std::max(0.0f, a));
  }
  inline T_FLOAT GetAlpha() const
  {
    return this->col_[3];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_FLOAT col_[4];

};
