#ifndef HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTION_H_
#define HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTION_H_

#include <math.h>
#include "NativeType.h"
#include "MathConstants.h"

namespace EasingFunction
{

enum OperatorKind
{
  EASE_IN,
  EASE_OUT,
  EASE_IN_OUT,

  EASE_DATA_NUM,
};

enum FunctionKind
{
  FK_LINER,
  FK_QUADRATIC,
  FK_CUBIC,
  FK_QUARTIC,
  FK_QUINTIC,
  FK_SINUSOIDAL,
  FK_EXPONENTIAL,
  FK_CIRCULAR,

  FK_DATA_NUM,
};

class EasingFunction
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  EasingFunction();
  virtual ~EasingFunction() {}

  // =================================================================
  // Method
  // =================================================================
public:
  void Load(T_UINT8 render_cycle);
  void Unload();

  T_FLOAT In(T_FLOAT val) const;
  T_FLOAT Out(T_FLOAT val) const;
  T_FLOAT InOut(T_FLOAT val) const;

protected:
  virtual T_FLOAT CalcIn(T_FLOAT val) const = 0;
  virtual T_FLOAT CalcOut(T_FLOAT val) const = 0;
  virtual T_FLOAT CalcInOut(T_FLOAT val) const = 0;

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT8 render_cycle_;
  T_FLOAT *table_in_;
  T_FLOAT *table_out_;
  T_FLOAT *table_in_out_;
};

/*
t currentTime
b start value
c change in value
d duration

val = t/d;
next = c;
now = b;
*/

// =================================================================
// Liner
// =================================================================
class Liner : public EasingFunction
{
public:
  static Liner& GetInstance()
  {
    static Liner self = Liner();
    return self;
  }

private:
  Liner() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    return val;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    return val;
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    return val;
  }
};

// =================================================================
// Quadratic
// =================================================================
class Quadratic : public EasingFunction
{
public:
  static Quadratic& GetInstance()
  {
    static Quadratic self = Quadratic();
    return self;
  }

private:
  Quadratic() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * (val*val) + now
    return val * val;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //next * (-val*(val-2)) + now
    return -val * (val - 2);
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * 0.5f * (val * val) + now
      return val * val * 0.5f;
    }
    val -= 1.0f;
    //-next * 0.5f * (val * (val - 2) - 1) + now
    return -(val * (val - 2) - 1) * 0.5f;
  }
};

// =================================================================
// Cubic
// =================================================================
class Cubic : public EasingFunction
{
public:
  static Cubic& GetInstance()
  {
    static Cubic self = Cubic();
    return self;
  }

private:
  Cubic() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * (val * val * val) + now
    return val * val * val;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //val--;
    //next * (val * val * val + 1) + now
    val -= 1.0f;
    return val * val * val + 1;
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * 0.5f * (val * val * val) + now
      return val * val * val * 0.5f;
    }
    //val-=2
    //next * 0.5f * (val * val * val + 2) + now
    val -= 2.0f;
    return (val * val * val + 2) * 0.5f;
  }
};

// =================================================================
// Quartic
// =================================================================
class Quartic : public EasingFunction
{
public:
  static Quartic& GetInstance()
  {
    static Quartic self = Quartic();
    return self;
  }

private:
  Quartic() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * (val * val * val * val) + now
    return val * val * val * val;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //val--;
    //next * (val * val * val * val - 1) + now
    val -= 1.0f;
    return -(val * val * val * val - 1);
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * 0.5f * (val * val * val * val) + now
      return val * val * val * val * 0.5f;
    }
    //val-=2
    //next * 0.5f * (val * val * val * val - 2) + now
    val -= 2.0f;
    return (val * val * val * val - 2) * 0.5f;
  }
};

// =================================================================
// Quintic
// =================================================================
class Quintic : public EasingFunction
{
public:
  static Quintic& GetInstance()
  {
    static Quintic self = Quintic();
    return self;
  }

private:
  Quintic() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * (val * val * val * val * val) + now
    return val * val * val * val * val;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //val--;
    //next * (val * val * val * val * val + 1) + now
    val -= 1.0f;
    return val * val * val * val * val + 1;
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * 0.5f * (val * val * val * val * val) + now
      return val * val * val * val * val * 0.5f;
    }
    //val-=2
    //next * 0.5f * (val * val * val * val * val + 2) + now
    val -= 2.0f;
    return (val * val * val * val * val + 2) * 0.5f;
  }
};

// =================================================================
// Sinusoidal
// =================================================================
class Sinusoidal : public EasingFunction
{
public:
  static Sinusoidal& GetInstance()
  {
    static Sinusoidal self = Sinusoidal();
    return self;
  }

private:
  Sinusoidal() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * ( 1 - cos(val * PI * 0.5f)) + now
    return (T_FLOAT)(1.0f - cos(val * MathConstants::PI * 0.5f));
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //next * sin(val * PI * 0.5f) + now
    return (T_FLOAT)sin(val * MathConstants::PI * 0.5f);
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    //-next * 0.5f * (cos(PI*val)-1) + now
    return (T_FLOAT)(-0.5f * (cos(MathConstants::PI * val) - 1));
  }
};

// =================================================================
// Exponential
// =================================================================
class Exponential : public EasingFunction
{
public:
  static Exponential& GetInstance()
  {
    static Exponential self = Exponential();
    return self;
  }

private:
  Exponential() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * pow(2,10*(val-1)) + now
    return (T_FLOAT)pow(2, 10 * (val - 1));
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //next * (1 - pow(2,-10*val))) + now
    return (T_FLOAT)(1 - pow(2, -10 * val));
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * 0.5f * pow(2,10*(val-1)) + now
      return (T_FLOAT)(0.5f * pow(2, 10 * (val - 1)));
    }
    //val-=1
    //next * 0.5f * (2-pow(2,-10*val)) + now
    val -= 1.0f;
    return (T_FLOAT)(2 - pow(2, -10 * val)) * 0.5f;
  }
};

// =================================================================
// Circular
// =================================================================
class Circular : public EasingFunction
{
public:
  static Circular& GetInstance()
  {
    static Circular self = Circular();
    return self;
  }

private:
  Circular() {}
  inline virtual T_FLOAT CalcIn(T_FLOAT val) const override
  {
    //next * (sqrt(1 - val * val) - 1) + now
    return (T_FLOAT)sqrt(1 - val * val) - 1;
  }

  inline virtual T_FLOAT CalcOut(T_FLOAT val) const override
  {
    //val-=1;
    //next * sqrt(1 - val * val) + now
    val -= 1.0f;
    return (T_FLOAT)sqrt(1 - val * val);
  }

  inline virtual T_FLOAT CalcInOut(T_FLOAT val) const override
  {
    val *= 2.0f;
    if (val < 1.0f)
    {
      //next * -0.5f * (sqrt(1-val*val)-1) + now
      return (T_FLOAT)(-0.5f * (sqrt(1 - val * val) - 1));
    }
    //val-=2
    //next * 0.5f * (sqrt(1-val*val)+1) + now
    val -= 2.0f;
    return (T_FLOAT)(0.5f * (sqrt(1 - val * val) + 1));
  }
};

};

#endif//HAL_ENGINE_UTIL_EASINGFUNCTION_EASINGFUNCTION_H_
