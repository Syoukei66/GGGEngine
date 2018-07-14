#include "RendererManager.h"
#include "RenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
RendererManager::RendererManager(Scene* scene)
{
}

RendererManager::~RendererManager()
{
}

void RendererManager::Update()
{
}

// =================================================================
// Method
// =================================================================
void RendererManager::Draw()
{
  for (RenderState* state : this->render_states_)
  {
    state->Draw();
  }
}

void RendererManager::AddRenderer(Renderer* renderer)
{
  this->renderers_.emplace_back(renderer);
  for (RenderState* state : this->render_states_)
  {
    state->AddQueue(renderer);
  }
}

void RendererManager::RemoveRenderer(Renderer* renderer)
{
  auto end = this->renderers_.end();
  auto new_end = std::remove(this->renderers_.begin(), this->renderers_.end(), renderer);
  this->renderers_.erase(new_end, end);
  for (RenderState* state : this->render_states_)
  {
    state->RemoveQueue(renderer);
  }
}

void RendererManager::AddRenderState(RenderState* state)
{
  state->aDd
}

void RendererManager::RemoveRenderState(RenderState* state)
{
  auto end = this->render_states_.end();
  auto new_end = std::remove(this->render_states_.begin(), this->render_states_.end(), state);
  this->render_states_.erase(new_end, end);
}

void RendererManager::ClearRenderState()
{
  this->render_states_.clear();
}
