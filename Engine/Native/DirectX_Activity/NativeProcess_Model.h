#pragma once

#include <INativeProcess_Model.h>

class NativeProcess_Model : public INativeProcess_Model
{
public:
  virtual LP_MODEL Model_Load(const char* full_path) override;
  virtual void Model_Unload(LP_MODEL model) override;
  virtual void Model_Draw(LP_MODEL model) override;
};