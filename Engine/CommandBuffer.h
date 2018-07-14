#pragma once

#include <vector>
#include "RenderCommand.h"

#include "MeshRenderer.h"
#include "RenderCommand_DrawMesh.h"

class CommandBuffer
{
public:
  CommandBuffer();
  ~CommandBuffer();

public:
  RenderCommand* Add(RenderCommand* command);
  void Remove(RenderCommand* command);

public:
  inline RenderCommand* DrawMeshRenderer(MeshRenderer* renderer, T_UINT8 index)
  {
    return this->Add(new RenderCommand_DrawMesh(renderer, index));
  }

private:
  std::vector<RenderCommand*> commands_;

};