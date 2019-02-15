#include "GameObjectRenderQueue.h"
#include <ppl.h>
#include <Engine/Component/Renderer/Renderer.h>
#include <Engine/Component/Camera/Camera3D.h>

#include "GameObjectRenderState.h"

void GameObjectRenderQueue::AddByDistance(const Renderer* renderer, const Camera* camera)
{
  TVec3f distance = renderer->GetObject()->GetTransform()->GetWorldMatrix().GetPosition3d();
  distance -= camera->GetObject()->GetTransform()->GetWorldMatrix().GetPosition3d();

  this->queue_.emplace_back(renderer, TVec3f::Dot(distance, camera->GetDirection()));
}

void GameObjectRenderQueue::Draw(GameObjectRenderState* state)
{
  if (this->queue_.size() == 0)
  {
    return;
  }

  concurrency::parallel_sort(this->queue_.begin(), this->queue_.end(), [](const DrawParam& a, const DrawParam& b) {
    return a.distance < b.distance;
  });

  for (const DrawParam& param : this->queue_)
  {
    param.renderer->Draw(state);
  }

  this->queue_.clear();
}

void GameObjectRenderQueue::DrawTransparent(GameObjectRenderState* state)
{
  if (this->queue_.size() == 0)
  {
    return;
  }

  const Camera* camera = state->GetCamera();
  concurrency::parallel_sort(this->queue_.begin(), this->queue_.end(), [](const DrawParam& a, const DrawParam& b) {
    return a.distance > b.distance;
  });

  for (const DrawParam& param : this->queue_)
  {
    //if (param.renderer->GetMaterial()->IsBillboard())
    //{
    //  Matrix4x4 inv_rotation_matrix = param.renderer->GetObject()->GetTransform()->GetRotationMatrix().Inverse();
    //  state->SetWorldMatrix(param.renderer->GetObject()->GetTransform()->GetWorldMatrix());
    //  state->PushWorldMatrix(inv_rotation_matrix);
    //  state->PushWorldMatrix(((const Camera3D*)camera)->GetBillboardingMatrix());
    //  state->PushWorldMatrix(param.renderer->GetObject()->GetTransform()->GetRotationMatrix());
    //  param.renderer->Draw(state);
    //}
    //else
    //{
      param.renderer->Draw(state);
    //}
  }

  this->queue_.clear();
}

void GameObjectRenderQueue::DrawShadow(GameObjectRenderState* state)
{
  if (this->queue_.size() == 0)
  {
    return;
  }

  for (const DrawParam& param : this->queue_)
  {
    param.renderer->Draw(state);
  }

  this->queue_.clear();
}
