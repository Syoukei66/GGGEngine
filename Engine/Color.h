#ifndef HAL_ENGINE_STRUCTURE_COLOR_H_
#define HAL_ENGINE_STRUCTURE_COLOR_H_

#include "NativeType.h"

template <typename T>
class TColor
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TColor(T r, T g, T b, T a)
    : r_(r)
    , g_(g)
    , b_(b)
    , a_(a)
    , color_dirty_(true)
    , packed_color_(0)
  {}

  // =================================================================
  // Assignment Operators
  // =================================================================
public:
  TColor<T> &operator = (const TColor<T>& other)
  {
    this->SetColor(other.r_, other.g_, other.b_, other.a_);
    return (*this);
  }
  
  // =================================================================
  // Method
  // =================================================================
public:
  inline bool Equals(const TColor<T> & c) const
  {
    return this->r_ == c.r_ && this->g_ == c.g_ && this->b_ == c.b_ && this->a_ == c.a_;
  }

  inline bool Equals(T r, T g, T b) const
  {
    return this->r_ == r && this->g_ == g && this->b_ == b;
  }

  inline bool Equals(T r, T g, T b, T a) const
  {
    return this->r_ == r && this->g_ == g && this->b_ == b && this->a_ == a;
  }

private:
  void OnUpdateColor()
  {
    this->color_dirty_ = true;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetColor(T r, T g, T b)
  {
    if (this->Equals(r, g, b))
    {
      return;
    }
    this->r_ = r;
    this->g_ = g;
    this->b_ = b;
    this->OnUpdateColor();
  }

  void SetColor(T r, T g, T b, T a)
  {
    if (this->Equals(r, g, b, a))
    {
      return;
    }
    this->r_ = r;
    this->g_ = g;
    this->b_ = b;
    this->a_ = a;
    this->OnUpdateColor();
  }

  void SetRed(T red)
  {
    if (this->r_ == red)
    {
      return;
    }
    this->r_ = red;
    this->OnUpdateColor();
  }

  inline T GetRed() const
  {
    return this->r_;
  }

  void SetGreen(T green)
  {
    if (this->g_ == green)
    {
      return;
    }
    this->g_ = green;
    this->OnUpdateColor();
  }

  inline T GetGreen() const
  {
    return this->g_;
  }

  void SetBlue(T blue)
  {
    if (this->b_ == blue)
    {
      return;
    }
    this->b_ = blue;
    this->OnUpdateColor();
  }

  inline T GetBlue() const
  {
    return this->b_;
  }

  void SetAlpha(T alpha)
  {
    if (this->a_ == alpha)
    {
      return;
    }
    this->a_ = alpha;
    this->OnUpdateColor();
  }

  inline T GetAlpha() const
  {
    return this->a_;
  }

  virtual T_PACKED_COLOR_UINT32 GetPackedColor() = 0;
  virtual T_PACKED_COLOR_UINT32 GetPackedColorWithoutUpdate() const = 0;

  // =================================================================
  // Data Member
  // =================================================================
protected:
  T r_, g_, b_, a_;
  bool color_dirty_;
  T_PACKED_COLOR_UINT32 packed_color_;
};


class Color4F;


class Color : public TColor<T_UINT8>
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const T_UINT8 GMIN;
  static const T_UINT8 GMAX;

  static const T_UINT32 PACKED_WHITE;

  static const Color WHITE;
  static const Color GRAY;
  static const Color BLACK;

  static const Color RED;
  static const Color GREEN;
  static const Color BLUE;
  static const Color YELLOW;
  static const Color LIGHT_BLUE;
  static const Color PINK;
  static const Color PURPLE;

public:
  Color::Color();
  Color::Color(T_UINT8 r, T_UINT8 g, T_UINT8 b);
  Color::Color(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a);

  // =================================================================
  // Operators
  // =================================================================
public:
  operator Color4F() const;

  const Color operator* (const Color& other) const
  {
    return Color(
      (T_UINT8)((T_FLOAT)(this->r_ * other.r_) / GMAX),
      (T_UINT8)((T_FLOAT)(this->g_ * other.g_) / GMAX),
      (T_UINT8)((T_FLOAT)(this->b_ * other.b_) / GMAX),
      (T_UINT8)((T_FLOAT)(this->a_ * other.a_) / GMAX)
    );
  }

  Color& operator*= (const Color& other)
  {
    this->r_ = (T_UINT8)((T_FLOAT)(this->r_ * other.r_) / GMAX);
    this->g_ = (T_UINT8)((T_FLOAT)(this->g_ * other.g_) / GMAX);
    this->b_ = (T_UINT8)((T_FLOAT)(this->b_ * other.b_) / GMAX);
    this->a_ = (T_UINT8)((T_FLOAT)(this->a_ * other.a_) / GMAX);
    return *this;
  }

  const Color operator/ (const Color& other) const
  {
    return Color(
      (T_UINT8)((T_FLOAT)(this->r_ * GMAX) / other.r_),
      (T_UINT8)((T_FLOAT)(this->g_ * GMAX) / other.g_),
      (T_UINT8)((T_FLOAT)(this->b_ * GMAX) / other.b_),
      (T_UINT8)((T_FLOAT)(this->a_ * GMAX) / other.a_)
    );
  }

  Color& operator/= (const Color& other)
  {
    this->r_ = (T_UINT8)((T_FLOAT)(this->r_ * GMAX) / other.r_);
    this->g_ = (T_UINT8)((T_FLOAT)(this->g_ * GMAX) / other.g_);
    this->b_ = (T_UINT8)((T_FLOAT)(this->b_ * GMAX) / other.b_);
    this->a_ = (T_UINT8)((T_FLOAT)(this->a_ * GMAX) / other.a_);
    return *this;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  void PackColor();
  virtual T_PACKED_COLOR_UINT32 GetPackedColor() override;
  virtual T_PACKED_COLOR_UINT32 GetPackedColorWithoutUpdate() const override
  {
    Color color = *this;
    return color.GetPackedColor();
  }

  inline const Color R(T_UINT8 r) const
  {
    return Color(r, this->g_, this->b_, this->a_);
  }

  inline const Color G(T_UINT8 g) const
  {
    return Color(this->r_, g, this->b_, this->a_);
  }

  inline const Color B(T_UINT8 b) const
  {
    return Color(this->r_, this->g_, b, this->a_);
  }

  inline const Color A(T_UINT8 a) const
  {
    return Color(this->r_, this->g_, this->b_, a);
  }

};

// =================================================================
// ê≥ãKâªÇ≥ÇÍÇΩColor
// =================================================================
class Color4F : public TColor<T_FLOAT>
{
  // =================================================================
  // Constants
  // =================================================================
public:
  static const T_FLOAT GMIN;
  static const T_FLOAT GMAX;

  static const T_UINT32 PACKED_WHITE;

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

public:
  Color4F::Color4F();
  Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b);
  Color4F::Color4F(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a);

  // =================================================================
  // Operators
  // =================================================================
public:
  operator Color () const
  {
    return Color(
      (T_UINT8)(this->r_ * Color::GMAX),
      (T_UINT8)(this->g_ * Color::GMAX),
      (T_UINT8)(this->b_ * Color::GMAX),
      (T_UINT8)(this->a_ * Color::GMAX)
    );
  }

  const Color4F operator* (const Color4F& other) const
  {
    return Color4F(
      (this->r_ * other.r_) / GMAX,
      (this->g_ * other.g_) / GMAX,
      (this->b_ * other.b_) / GMAX,
      (this->a_ * other.a_) / GMAX
    );
  }
  
  Color4F& operator*= (const Color4F& other)
  {
    this->r_ = (this->r_ * other.r_) / GMAX;
    this->g_ = (this->g_ * other.g_) / GMAX;
    this->b_ = (this->b_ * other.b_) / GMAX;
    this->a_ = (this->a_ * other.a_) / GMAX;
    return *this;
  }

  const Color4F operator/ (const Color4F& other) const
  {
    return Color4F(
      (this->r_ * GMAX) / other.r_,
      (this->g_ * GMAX) / other.g_,
      (this->b_ * GMAX) / other.b_,
      (this->a_ * GMAX) / other.a_
    );
  }

  Color4F& operator/= (const Color4F& other)
  {
    this->r_ = (this->r_ * GMAX) / other.r_;
    this->g_ = (this->g_ * GMAX) / other.g_;
    this->b_ = (this->b_ * GMAX) / other.b_;
    this->a_ = (this->a_ * GMAX) / other.a_;
    return *this;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  void PackColor();
  virtual T_PACKED_COLOR_UINT32 GetPackedColor() override;
  virtual T_PACKED_COLOR_UINT32 GetPackedColorWithoutUpdate() const override
  {
    Color4F color = *this;
    return color.GetPackedColor();
  }

  inline const Color4F R(T_FLOAT r) const
  {
    return Color4F(r, this->g_, this->b_, this->a_);
  }

  inline const Color4F G(T_FLOAT g) const
  {
    return Color4F(this->r_, g, this->b_, this->a_);
  }

  inline const Color4F B(T_FLOAT b) const
  {
    return Color4F(this->r_, this->g_, b, this->a_);
  }

  inline const Color4F A(T_FLOAT a) const
  {
    return Color4F(this->r_, this->g_, this->b_, a);
  }
};

#endif//HAL_ENGINE_STRUCTURE_COLOR_H_