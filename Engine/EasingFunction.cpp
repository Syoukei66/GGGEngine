#include "EasingFunction.h"
#include <stdlib.h>
#include <math.h>

namespace EasingFunction
{

// =================================================================
// Constructor / Destructor
// =================================================================
EasingFunction::EasingFunction()
  : render_cycle_(0)
  , table_in_(NULL)
  , table_out_(NULL)
  , table_in_out_(NULL)
{}

// =================================================================
// Method
// =================================================================
void EasingFunction::Load(T_UINT8 render_cycle)
{
  this->table_in_ = new T_FLOAT[render_cycle + 1]();
  this->table_out_ = new T_FLOAT[render_cycle + 1]();
  this->table_in_out_ = new T_FLOAT[render_cycle + 1]();
  const T_FLOAT d = 1.0f / (render_cycle);
  for (int i = 0; i < render_cycle + 1; ++i)
  {
    //Œë·‚ð•ªŽU‚³‚¹‚é
    //if (i == 0 || (i != render_cycle && i % 2 == 0))
    //{
    //  const T_FLOAT val = d * i;
    //  this->table_in_[i] = this->CalcIn(val);
    //  this->table_out_[i] = this->CalcOut(val);
    //  this->table_in_out_[i] = this->CalcInOut(val);
    //}
    //else
    //{
      const T_FLOAT val = d * (render_cycle - i);
      this->table_in_[i] = 1.0f - this->CalcIn(val);
      this->table_out_[i] = 1.0f - this->CalcOut(val);
      this->table_in_out_[i] = 1.0f - this->CalcInOut(val);
    //}
  }
  this->render_cycle_ = render_cycle;
}

void EasingFunction::Unload()
{
  if (this->table_in_)
  {
    delete[] this->table_in_;
  }
  if (this->table_out_)
  {
    delete[] this->table_out_;
  }
  if (this->table_in_out_)
  {
    delete[] this->table_in_out_;
  }
  this->render_cycle_ = 0;
}

T_FLOAT EasingFunction::In(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->render_cycle_;
  const T_UINT8 now = (T_UINT8)(val * this->render_cycle_);
  const T_UINT8 next = now < this->render_cycle_ ? now + 1 : now;
  return this->table_in_[now] + (this->table_in_[next] - this->table_in_[now]) * (val - now * d) / d;
}

T_FLOAT EasingFunction::Out(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->render_cycle_;
  const T_UINT8 now = (T_UINT8)(val * this->render_cycle_);
  const T_UINT8 next = now < this->render_cycle_ ? now + 1 : now;
  return this->table_out_[now] + (this->table_out_[next] - this->table_out_[now]) * (val - now * d) / d;
}

T_FLOAT EasingFunction::InOut(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->render_cycle_;
  const T_UINT8 now = (T_UINT8)(val * this->render_cycle_);
  const T_UINT8 next = now < this->render_cycle_ ? now + 1 : now;
  return this->table_in_out_[now] + (this->table_in_out_[next] - this->table_in_out_[now]) * (val - now * d) / d;
}

} //  namespace EasingFunction
