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
GG_INIT_FUNC_IMPL_2(ViewerScene, const SharedRef<IViewerBehavior>& behavior, AssetConverterContext* context)
{
  this->current_context_ = context;
  this->current_behavior_ = behavior;
  this->move_speed_weight_ = 1.0f;
  this->move_speed_ = 0.5f;
  this->bg_color_ = TColor::BLACK;
  return Scene::Init();
}

// =================================================================
// Methods from Scene
// =================================================================
void ViewerScene::OnLoad()
{
  this->camera_3d_ = GameObject3D::Create();
  this->camera_3d_->AddComponent<Camera3D_LookAt>();
  this->camera_target_ = GameObject3D::Create();
  this->AddCamera(this->camera_3d_->GetComponent<Camera>());
}

void ViewerScene::OnUnload()
{
  this->RemoveCamera(this->camera_3d_->GetComponent<Camera>());
  this->camera_3d_ = nullptr;
}

void ViewerScene::OnShow()
{
  this->current_behavior_->Start(this, this->current_context_);
  this->current_behavior_->GetEntity()->GetMetaData()->GetConverterSetting()->GetCameraState(this->camera_target_->GetTransform());
}

void ViewerScene::OnHide()
{
  this->current_behavior_->GetEntity()->GetMetaData()->GetConverterSetting()->SetCameraState(this->camera_3d_->GetTransform());
  this->current_behavior_->End();
}

void ViewerScene::Update(const ActivityContext& context)
{
  this->current_behavior_->Update(this->current_context_);
  const InputState* input = context.Input(0);
  
  using namespace HalEngine;
  Transform3D* transform = this->camera_target_->GetTransform();

  const T_FLOAT move_speed = this->move_speed_weight_ * this->move_speed_;

  const T_FLOAT horizontal = input->GetAxis(GameInput::X_AXIS, 0.0f);
  const T_FLOAT vertical = input->GetAxis(GameInput::Y_AXIS, 0.0f);

  transform->MoveX(horizontal * move_speed);
  transform->MoveZ(vertical * move_speed);

  const bool mouse_click_L = input->GetButton(GameInput::MOUSE_CLICK_L);
  const bool mouse_click_C = input->GetButton(GameInput::MOUSE_CLICK_C);
  const bool mouse_click_R = input->GetButton(GameInput::MOUSE_CLICK_R);
  const T_FLOAT move_x = input->GetAxis(GameInput::MOUSE_MOVE_X, 0.0f);
  const T_FLOAT move_y = input->GetAxis(GameInput::MOUSE_MOVE_Y, 0.0f);
  const T_FLOAT move_z = input->GetAxis(GameInput::MOUSE_MOVE_Z, 0.0f);
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

  ImGui::Begin(u8"メニュー");
  ImGui::SliderFloat(u8"カメラ移動速度", &this->move_speed_, 0.0f, 1.0f);
  ImGui::SliderFloat(u8"カメラ移動速度倍率", &this->move_speed_weight_, 0.0f, 5.0f);

  ImGui::Combo(u8"カメラモード", &this->camera_state_, CAMERA_STATE_NAMES, CAMERA_STATE_MAX);
  
  if (ImGui::Button(u8"カメラを初期位置に戻す"))
  {
    this->camera_move_x_ = 0.0f;
    this->camera_move_y_ = 0.0f;
    transform->SetPosition(TVec3f(0.0f, 0.0f, -10.0f));
    transform->SetEularAngles(TVec3f::zero);
  }

  if (ImGui::ColorEdit3(u8"背景色", this->bg_color_.data))
  {
    this->camera_3d_->GetComponent<Camera>()->SetBgColor(this->bg_color_);
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  Transform3D* camera_transform = this->camera_3d_->GetTransform();
  camera_transform->SetPosition(Mathf::Lerp(camera_transform->GetPosition(), transform->GetPosition(), 0.05f));
  camera_transform->SetQuaternion(Quaternion::Lerp(camera_transform->GetQuaternion(), transform->GetQuaternion(), 0.05f));

  ImGui::End();
}
