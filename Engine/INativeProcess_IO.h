#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_

#include <string>

class INativeProcess_IO
{
  // =================================================================
  // Method
  // =================================================================
public:
  virtual const std::string TextFile_Read(const char* path) = 0;
  virtual void TextFile_Write(const char* path, const std::string& str) = 0;
};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_