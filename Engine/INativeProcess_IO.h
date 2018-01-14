#ifndef HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_
#define HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_

#include <string>
#include <iostream>

class INativeProcess_IO
{
  // =================================================================
  // Method
  // =================================================================
public:
  //TODO: –{“–‚É•K—v‚¾‚ë‚¤‚©
  virtual const std::string TextFile_Read(const char* path) = 0;
};

#endif//HAL_ENGINE_NATIVE_NATIVEPROCESS_IO_H_