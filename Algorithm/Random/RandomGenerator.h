#pragma once

class RondomGenerator
{
public:
  RondomGenerator();
  ~RondomGenerator();

public:
  void Init();
  void Init(T_UINT32 seed);

  T_UINT32 Value();
  //0.0f ~ 1.0f
  T_FLOAT NormalizedValue();
  T_UINT32 Range(T_UINT32 radius);
  T_UINT32 Range(T_UINT32 min, T_UINT32 max);
  T_INT32 Range(T_INT32 radius);
  T_INT32 Range(T_INT32 min, T_INT32 max);
  T_FLOAT Range(T_FLOAT radius);
  T_FLOAT Range(T_FLOAT min, T_FLOAT max);

private:
  T_UINT32 seed_;
  T_UINT32 current_;

};