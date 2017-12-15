#pragma once

#include "../../Engine/INativeProcess_IO.h"

class NativeProcess_IO : public INativeProcess_IO
{
public:
  virtual const std::string TextFile_Read(const char* path) override;

};