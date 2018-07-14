#pragma once

#include <vector>

#include "Renderer.h"
#include "RenderCommand.h"
#include "CommandBuffer.h"

class Scene;
class RenderState;

//Renderer‚©‚çCommandBuffer‚ðì¬‚µ‚½•û‚ª‚¢‚¢‚Ì‚©‚à
class RendererManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RendererManager(Scene* scene);
  ~RendererManager();

  // =================================================================
  // Method
  // =================================================================
public:
  void Update();
  void Draw();

  void AddRenderer(Renderer* renderer);
  void RemoveRenderer(Renderer* renderer);

  void AddRenderState(RenderState* state);
  void RemoveRenderState(RenderState* state);
  void ClearRenderState();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline CommandBuffer* GetCommandBuffer()
  {
    return this->command_buffer_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Scene* scene_;
  std::vector<Renderer*> renderers_;
  CommandBuffer* command_buffer_;

  std::vector<RenderState*> render_states_;
};