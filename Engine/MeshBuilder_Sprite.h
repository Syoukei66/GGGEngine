#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Sprite : public MeshBuilder
{
public:
  MeshBuilder_Sprite();

public:
  virtual Mesh* Create() const override;

};