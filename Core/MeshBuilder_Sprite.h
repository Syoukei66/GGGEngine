#pragma once

#include "MeshBuilder.h"

class MeshBuilder_Sprite : public MeshBuilder
{
public:
  MeshBuilder_Sprite();

public:
  virtual rcMesh* CreateMesh(bool read_only) const override;

};