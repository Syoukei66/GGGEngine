#include "EasingFunction.h"
#include <stdlib.h>
#include <math.h>

namespace EasingFunction
{
// =================================================================
// Method
// =================================================================
void EasingFunction::Load(T_UINT32 sampling_count)
{
  this->table_in_ = new T_FLOAT[sampling_count + 1]();
  this->table_out_ = new T_FLOAT[sampling_count + 1]();
  this->table_in_out_ = new T_FLOAT[sampling_count + 1]();
  const T_FLOAT d = 1.0f / sampling_count;
  for (int i = 0; i < sampling_count; ++i)
  {
    const T_FLOAT val = d * (sampling_count - i - 1);
    this->table_in_[i] = 1.0f - this->CalcIn(val);
    this->table_out_[i] = 1.0f - this->CalcOut(val);
    this->table_in_out_[i] = 1.0f - this->CalcInOut(val);
  }
  this->sampling_count_ = sampling_count;
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
  this->sampling_count_ = 0;
}

T_FLOAT EasingFunction::In(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->sampling_count_;
  const T_UINT32 now = (T_UINT32)(val * this->sampling_count_);
  const T_UINT32 next = now < this->sampling_count_ - 1 ? now + 1 : now;
  return this->table_in_[now] + (this->table_in_[next] - this->table_in_[now]) * (val - now * d) / d;
}

T_FLOAT EasingFunction::Out(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->sampling_count_;
  const T_UINT32 now = (T_UINT32)(val * this->sampling_count_);
  const T_UINT32 next = now < this->sampling_count_ - 1 ? now + 1 : now;
  return this->table_out_[now] + (this->table_out_[next] - this->table_out_[now]) * (val - now * d) / d;
}

T_FLOAT EasingFunction::InOut(T_FLOAT val) const
{
  const T_FLOAT d = 1.0f / this->sampling_count_;
  const T_UINT32 now = (T_UINT32)(val * this->sampling_count_);
  const T_UINT32 next = now < this->sampling_count_ - 1 ? now + 1 : now;
  return this->table_in_out_[now] + (this->table_in_out_[next] - this->table_in_out_[now]) * (val - now * d) / d;
}

} //  namespace EasingFunction
