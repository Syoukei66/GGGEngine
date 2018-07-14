#pragma once

#include <vector>

#include "Renderer.h"
#include "RenderCommand.h"

class RenderQueue
{
public:
  RenderQueue();
  ~RenderQueue();

public:
  void Add(Renderer* renderer);
  void Remove(Renderer* renderer);
  void Clear();

private:
  std::vector<RenderCommand*> commands_;

};