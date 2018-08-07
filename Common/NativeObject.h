#pragma once

//TODO:リファレンスカウンタ付けた方がいいのでは
template<typename T>
class NativeObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  NativeObject(T* native_instance)
    : instance_(native_instance)
  {}

  NativeObject() {}

  virtual ~NativeObject() {}

private:
  NativeObject(const NativeObject& obj) {}
  NativeObject& operator = (const NativeObject& obj) { return *this; }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  template<typename T2>
  inline T2* GetNativeInstance() const
  {
    return (T2*)this->instance_;
  }

  inline T* GetNativeInstance() const
  {
    return this->instance_;
  }

protected:
  template<typename T2>
  inline void SetNativeInstance(T2* instance)
  {
    this->instance_ = (T*)instance;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T* instance_;
};