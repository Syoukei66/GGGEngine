#include "UpdateEventState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
UpdateEventState::UpdateEventState()
  : delta_time_()
{
  this->time_ = std::chrono::system_clock::now();
  this->builtin_variable_buffer_ = rcConstantBuffer::Create(
    Shader::ConstantBufferId::kTimeBuiltin,
    sizeof(ShaderBuiltinData)
  );
}

// =================================================================
// Methods
// =================================================================
void UpdateEventState::Update()
{
  auto sys_time = std::chrono::system_clock::now();
  this->delta_time_ = std::chrono::duration_cast<std::chrono::microseconds>(sys_time - this->time_).count() * 0.001f * 0.001f;
  this->time_ = sys_time;

  const T_FLOAT time = this->builtin_variable_.time.y + this->delta_time_ ;
  this->builtin_variable_.time.x = time / 20.0f;
  this->builtin_variable_.time.y = time;
  this->builtin_variable_.time.z = time * 2;
  this->builtin_variable_.time.w = time * 3;

  this->builtin_variable_.sin_time.x = sinf(time / 8.0f);
  this->builtin_variable_.sin_time.y = sinf(time / 4.0f);
  this->builtin_variable_.sin_time.z = sinf(time / 2.0f);
  this->builtin_variable_.sin_time.w = sinf(time / 1.0f);

  this->builtin_variable_.cos_time.x = cosf(time / 8.0f);
  this->builtin_variable_.cos_time.y = cosf(time / 4.0f);
  this->builtin_variable_.cos_time.z = cosf(time / 2.0f);
  this->builtin_variable_.cos_time.w = cosf(time / 1.0f);

  this->builtin_variable_buffer_->CommitChanges(&this->builtin_variable_);
}
