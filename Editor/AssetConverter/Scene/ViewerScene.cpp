#include "ViewerScene.h"
#include <Engine/Utils.h>
#include <Engine/Component/Camera/Camera3D_LookAt.h>
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>
#include "GameInput.h"

static const char* CAMERA_STATE_NAMES[ViewerScene::CAMERA_STATE_MAX] =
{
  "3D Scene",
  "3D AnchorCenter",
  "2D",
};

// =================================================================
// GGG Statement
// =================================================================
GG_INIT_FUNC_IMPL(ViewerScene)
{
  this->move_speed_weight_ = 1.0f;
  this->move_speed_ = 0.5f;
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void ViewerScene::OnLoad()
{
  this->camera_3d_ = GameObject3D::Create();
  this->camera_3d_->AddComponent<Camera3D_LookAt>();
  this->camera_3d_->GetTransform()->SetZ(-20.0f);
  this->AddCamera(this->camera_3d_->GetComponent<Camera>());
}

void ViewerScene::OnUnload()
{
  this->RemoveCamera(this->camera_3d_->GetComponent<Camera>());
  this->camera_3d_ = nullptr;
}

void ViewerScene::OnShow()
{
  this->current_behavior_->Start(this);
}

void ViewerScene::OnHide()
{
  this->current_behavior_->End();
}

void ViewerScene::Update()
{
  this->current_behavior_->Update();

  using namespace HalEngine;
  Transform3D* transform = this->camera_3d_->GetTransform();

  const T_FLOAT move_speed = this->move_speed_weight_ * this->move_speed_;

  const T_FLOAT horizontal = Input(0)->GetAxis(GameInput::X_AXIS, 0.0f);
  const T_FLOAT vertical = Input(0)->GetAxis(GameInput::Y_AXIS, 0.0f);

  transform->MoveX(horizontal * move_speed);
  transform->MoveZ(vertical * move_speed);

  const bool mouse_click_L = Input(0)->GetButton(GameInput::MOUSE_CLICK_L);
  const bool mouse_click_C = Input(0)->GetButton(GameInput::MOUSE_CLICK_C);
  const bool mouse_click_R = Input(0)->GetButton(GameInput::MOUSE_CLICK_R);
  const T_FLOAT move_x = Input(0)->GetAxis(GameInput::MOUSE_MOVE_X, 0.0f);
  const T_FLOAT move_y = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Y, 0.0f);
  const T_FLOAT move_z = Input(0)->GetAxis(GameInput::MOUSE_MOVE_Z, 0.0f);
  if (mouse_click_C)
  {
    transform->MoveX(-move_x * move_speed);
    transform->MoveY(move_y * move_speed);
  }
  if (mouse_click_R)
  {
    this->camera_move_x_ -= move_x * 0.05f;
    this->camera_move_y_ += move_y * 0.05f;
  }

  if (this->camera_state_ == CAMERA_2D)
  {
    transform->SetX(this->camera_move_x_);
    transform->SetY(this->camera_move_y_);
    transform->SetEularAngles(TVec3f::zero);
  }
  else if (this->camera_state_ == CAMERA_3D)
  {
    TVec3f pos = TVec3f::zero;
    const T_FLOAT rad = this->camera_move_x_ * Mathf::PI + Mathf::PI_1_2;
    pos.x = cosf(rad);
    pos.z = sinf(rad);
    pos += transform->GetPosition();

    transform->LookAt(pos, TVec3f::up);
    transform->RotateX(this->camera_move_y_ * Mathf::PI);
  }
  else if (this->camera_state_ == CAMERA_3D_ANCHOR_CENTER)
  {

  }

  if (fabs(move_z) != 0.0f)
  {
    transform->MoveZ(move_z * move_speed * 2.0f);
  }

  ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_Once);
  ImGui::SetNextWindowSize(ImVec2(200.0f, 200.0f), ImGuiCond_Once);

  ImGui::Begin(u8"���j���[");
  ImGui::SliderFloat(u8"�J�����ړ����x", &this->move_speed_, 0.0f, 1.0f);
  ImGui::SliderFloat(u8"�J�����ړ����x�{��", &this->move_speed_weight_, 0.0f, 5.0f);

  ImGui::Combo(u8"�J�������[�h", &this->camera_state_, CAMERA_STATE_NAMES, CAMERA_STATE_MAX);
  
  if (ImGui::Button(u8"�J�����������ʒu�ɖ߂�"))
  {
    this->camera_3d_->GetTransform()->SetPosition(TVec3f(0.0f, 0.0f, -20.0f));
    this->camera_3d_->GetTransform()->SetEularAngles(TVec3f::zero);
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  if (ImGui::Button(u8"�X�^�[�g���j���[�ɖ߂�"))
  {
    Director::PopScene(false);
  }

  ImGui::End();
}

void ViewerScene::Run(const SharedRef<IViewerBehavior>& behavior)
{
  this->current_behavior_ = behavior;
  Director::PushScene(SharedRef<ViewerScene>(this), false);
}
