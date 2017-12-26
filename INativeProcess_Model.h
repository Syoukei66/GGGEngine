#pragma once

#include "NativeType.h"

class INativeProcess_Model
{
  // =================================================================
  // Method
  // =================================================================
public:
  //�ˊэH���̂��߃t���p�X�w��
  virtual LP_MODEL Model_Load(const char* full_path) = 0;
  virtual void Model_Unload(LP_MODEL model) = 0;
  virtual void Model_Draw(LP_MODEL model) = 0;

};