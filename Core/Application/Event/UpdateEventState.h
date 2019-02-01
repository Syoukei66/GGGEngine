#pragma once

#include <chrono>
#include <Core/Application/Platform/API/_Resource/ConstantBuffer.h>

class UpdateEventState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  UpdateEventState();

  // =================================================================
  // Methods
  // =================================================================
public:
  void Update();

  GG_INLINE void SetConstantBuffer() const
  {
    this->builtin_variable_buffer_->SetBuffer();
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE T_FLOAT GetDeltaTime() const
  {
    return this->delta_time_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::chrono::time_point<std::chrono::system_clock> time_;
  T_FLOAT delta_time_;
  mutable struct ShaderBuiltinData
  {
    TVec4f time;
    TVec4f sin_time;
    TVec4f cos_time;
    TVec4f delta_time;
  } builtin_variable_;
  SharedRef<rcConstantBuffer> builtin_variable_buffer_;

};