#include "GameObjectRenderQueue.h"
#include <ppl.h>

#include "GameObjectRenderState.h"

void GameObjectRenderQueue::AddByDistance(const Renderer* renderer, const Camera* camera)
{
  TVec3f distance = renderer->GetEntity()->GetWorldMatrix().GetPosition3d();
  distance -= camera->GetEntity()->GetWorldMatrix().GetPosition3d();

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
    state->SetWorldMatrix(param.renderer->GetEntity()->GetWorldMatrix());
    param.renderer->Draw(state);
  }

  this->queue_.clear();
}

void GameObjectRenderQueue::DrawWithZSorted(GameObjectRenderState* state)
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
    if (param.renderer->GetMaterial()->IsBillboard())
    {
      Matrix4x4 inv_rotation_matrix = param.renderer->GetEntity()->GetRotationMatrix().Inverse();
      state->SetWorldMatrix(param.renderer->GetEntity()->GetWorldMatrix());
      state->PushWorldMatrix(inv_rotation_matrix);
      state->PushWorldMatrix(((const Camera3D*)camera)->GetBillboardingMatrix());
      state->PushWorldMatrix(param.renderer->GetEntity()->GetRotationMatrix());
      param.renderer->Draw(state);
    }
    else
    {
      state->SetWorldMatrix(param.renderer->GetEntity()->GetWorldMatrix());
      param.renderer->Draw(state);
    }
  }

  this->queue_.clear();
}
