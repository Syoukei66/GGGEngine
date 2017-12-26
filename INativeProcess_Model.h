#pragma once

#include "NativeType.h"

class INativeProcess_Model
{
  // =================================================================
  // Method
  // =================================================================
public:
  //突貫工事のためフルパス指定
  virtual LP_MODEL Model_Load(const char* full_path) = 0;
  virtual void Model_Unload(LP_MODEL model) = 0;
  virtual void Model_Draw(LP_MODEL model) = 0;

};