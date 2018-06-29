#include "GameObjectRenderState.h"

#include <ppl.h>
#include "GameObject.h"
#include "Director.h"
#include "NativeMethod.h"
#include "Renderer.h"
#include "Camera.h"
#include "Camera3D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
GameObjectRenderState::GameObjectRenderState(Camera* camera)
  : camera_(camera)
  , layer_state_(1)
  , view_proj_matrix_()
  , world_view_proj_matrix_()
//  , post_draw_map_()
{
  this->matrix_stack_ = INativeMatrixStack::Create();
}

GameObjectRenderState::~GameObjectRenderState()
{
  delete this->matrix_stack_;
}

// =================================================================
// Method
// =================================================================
void GameObjectRenderState::Init()
{
  this->render_object_ = Director::GetInstance()->GetDevice();
  this->view_proj_matrix_ = this->camera_->GetViewMatrix();
  this->view_proj_matrix_ *= this->camera_->GetProjectionMatrix();
}

void GameObjectRenderState::PushMatrix(const Matrix4x4& matrix)
{
  this->matrix_stack_->Push(matrix);
}

void GameObjectRenderState::PopMatrix()
{
  this->matrix_stack_->Pop();
}

void GameObjectRenderState::AddZCheckOrder(T_UINT8 level, Renderer* renderer)
{
  DrawParam param = DrawParam();
  param.renderer = renderer;

  if (level == 0)
  {
    this->draw_map_[renderer->GetMaterial()].push_back(param);
    return;
  }
  TVec3f distance = renderer->GetEntity()->GetWorldMatrix().GetPosition3d();
  distance -= this->camera_->GetEntity()->GetWorldMatrix().GetPosition3d();

  param.distance = TVec3f::InnerProduct(distance, this->camera_->GetDirection());
  this->post_draw_map_[level][renderer->GetMaterial()].push_back(param);
}

void GameObjectRenderState::DrawZOrderedGameObject()
{
  for (auto pair : this->post_draw_map_)
  {
    //concurrency::parallel_for_each(pair.second.begin(), pair.second.end(), [&](std::pair<Material*, std::vector<DrawParam>> &pair2)
    for (auto pair2 : pair.second)
    {
      concurrency::parallel_sort(pair2.second.begin(), pair2.second.end(), [](const DrawParam& a, const DrawParam& b) {
        return a.distance > b.distance;
      });
      for (DrawParam param : pair2.second)
      {
        if (param.renderer->GetMaterial()->IsBillboard())
        {
          Matrix4x4 inv_rotation_matrix = param.renderer->GetEntity()->GetRotationMatrix().Inverse();
          this->PushMatrix(param.renderer->GetEntity()->GetWorldMatrix());
          this->PushMatrix(inv_rotation_matrix);
          this->PushMatrix(((Camera3D*)this->camera_)->GetBillboardingMatrix());
          this->PushMatrix(param.renderer->GetEntity()->GetRotationMatrix());
          param.renderer->Draw(this);
          this->PopMatrix();
          this->PopMatrix();
          this->PopMatrix();
          this->PopMatrix();
        }
        else
        {
          this->PushMatrix(param.renderer->GetEntity()->GetWorldMatrix());
          param.renderer->Draw(this);
          this->PopMatrix();
        }
      }
    }
  }

  this->post_draw_map_.clear();
}

// =================================================================
// Setter / Getter
// =================================================================
const Matrix4x4& GameObjectRenderState::GetWorldViewProjToMaterial()
{
  //TODO:MatrixStack‚ðŽg‚í‚È‚­‚Ä‚àWorldMatrix‚ðŽg‚¦‚Î‚æ‚¢‚Ì‚Å‚Í
  this->world_view_proj_matrix_ = this->matrix_stack_->GetTop();
  this->world_view_proj_matrix_ *= this->view_proj_matrix_;
  return this->world_view_proj_matrix_;
}

