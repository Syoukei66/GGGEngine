#pragma once

#include "GameObject3D.h"
#include "FbxData.h"

class FbxModel : public GameObject3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  FbxModel(const FbxData& data);

};