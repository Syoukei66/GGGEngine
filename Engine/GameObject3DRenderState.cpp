#include "GameObject3DRenderState.h"
#include <algorithm>

#include "NativeMethod.h"
#include "GameObject3D.h"
#include "Camera3D.h"

GameObject3DRenderState::GameObject3DRenderState(Camera3D* camera)
  : GameObjectRenderState(camera)
  , camera_(camera)
  , post_draw_map_()
{
  this->mat_ = INativeMatrix::Create();
}

GameObject3DRenderState::~GameObject3DRenderState()
{
  delete this->mat_;
}

void GameObject3DRenderState::AddZCheckOrder(T_UINT8 level, GameObject3D* object)
{
  TVec3f distance = object->GetTransform()->GetWorldPosition();
  distance -= this->camera_->GetTransform()->GetWorldPosition();

  PostDrawParam param = PostDrawParam();
  param.object = object;
  param.distance = TVec3f::InnerProduct(distance, this->camera_->GetDirection());
  this->post_draw_map_[level].push_back(param);
}

void GameObject3DRenderState::DrawZOrderedGameObject()
{
  for (auto pair : this->post_draw_map_)
  {
    std::sort(pair.second.begin(), pair.second.end(), [](const PostDrawParam& a, const PostDrawParam& b) {
      return a.distance > b.distance;
    });
    for (PostDrawParam param : pair.second)
    {
      if (param.object->GetMaterial()->IsBillboard())
      {
        param.object->GetTransform()->GetRotationMatrix().Inverse(this->mat_);
        this->PushMatrix(param.object->GetTransform()->GetWorldMatrix());
        this->PushMatrix(*this->mat_);
        this->PushMatrix(this->camera_->GetBillboardingMatrix());
        this->PushMatrix(param.object->GetTransform()->GetRotationMatrix());
        param.object->ManagedDraw(this);
        this->PopMatrix();
        this->PopMatrix();
        this->PopMatrix();
        this->PopMatrix();
      }
      else
      {
        this->PushMatrix(param.object->GetTransform()->GetWorldMatrix());
        param.object->ManagedDraw(this);
        this->PopMatrix();
      }
    }
  }

  this->post_draw_map_.clear();
}
