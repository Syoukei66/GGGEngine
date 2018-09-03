#pragma once

#include <vector>
#include <unordered_map>
#include "../Core/NativeType.h"

class rcCustomMaterial;
class Renderer;
class Camera;
class GameObjectRenderState;

class GameObjectRenderQueue
{
private:
  struct DrawParam
  {
    const Renderer* renderer;
    T_FLOAT distance;
    DrawParam(const Renderer* renderer, T_FLOAT distance)
      : renderer(renderer)
      , distance(distance)
    {}
  };

public:
  inline void Add(const Renderer* renderer)
  {
    this->queue_.emplace_back(renderer, 0.0f);
  }
  void AddByDistance(const Renderer* renderer, const Camera* camera);
  void Draw(GameObjectRenderState* state);
  void DrawWithZSorted(GameObjectRenderState* state);

private:
  std::vector<DrawParam> queue_;

};