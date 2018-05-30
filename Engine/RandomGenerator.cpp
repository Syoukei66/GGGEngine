#include "RandomGenerator.h"
#include <math.h>

RondomGenerator::RondomGenerator()
  : seed_(123456789)
{
  this->current_ = this->seed_;
}

RondomGenerator::~RondomGenerator()
{
}

void RondomGenerator::Init()
{
  this->current_ = this->seed_;
}

void RondomGenerator::Init(T_UINT32 seed)
{
  this->seed_ = seed;
  this->current_ = this->seed_;
}

T_UINT32 RondomGenerator::Value()
{
  this->current_ ^= (this->current_ << 13);
  this->current_ ^= (this->current_ >> 17);
  this->current_ ^= (this->current_ << 15);
  return this->current_;
}

T_UINT32 RondomGenerator::Range(T_UINT32 radius)
{
  return this->Value() % radius;
}

T_UINT32 RondomGenerator::Range(T_UINT32 min, T_UINT32 max)
{
  return min + (this->Value() % (max  - min));
}

T_INT32 RondomGenerator::Range(T_INT32 radius)
{
  return this->Value() % radius;
}

T_INT32 RondomGenerator::Range(T_INT32 min, T_INT32 max)
{
  return min + (this->Value() % (max - min));
}

T_FLOAT RondomGenerator::Range(T_FLOAT radius)
{
  return fmod(this->Value(), radius);
}

T_FLOAT RondomGenerator::Range(T_FLOAT min, T_FLOAT max)
{
  return min + fmod(this->Value(), max - min);
}
