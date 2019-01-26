#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Engine/Scene/SceneManager.h>

struct ImGuiContext;

/*!
 * @brief �E�B���h�E�ȂǁA�P�̃A�v���P�[�V�������s�C���X�^���X�̃N���X
 */
class Activity : public GGObject
{
  friend class Application;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(Activity, const ActivityOption& option);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief �A�N�e�B�r�e�B����������
   */
  void Start();

  /*!
   * @brief �A�N�e�B�r�e�B�I������
   */
  void End();

  /*!
   * @brief �A�N�e�B�r�e�B�̃A�b�v�f�[�g����
   * @return false�Ȃ�A�N�e�B�r�e�B�I��
   */
  bool Update(const SharedRef<GraphicsAPI>& graphics_api, const SharedRef<InputAPI>& input_api);

protected:
  /*!
   * @brief �v���b�g�t�H�[�����̃A�N�e�B�r�e�B����������
   */
  virtual void OnStart() = 0;

  /*!
   * @brief �v���b�g�t�H�[�����̃A�N�e�B�r�e�B�I������
   */
  virtual void OnEnd() = 0;

  /*!
   * @brief �A�N�e�B�r�e�B���A�N�e�B�u��Ԃ��m���߂�
   */
  virtual bool IsActive() = 0;

  /*!
   * @brief �`�揈�����L�����ǂ����̔���
   * @param �o�ߎ���(�b)
   * @return false�Ȃ��ʂ̃A�b�v�f�[�g���s��Ȃ�
   */
  bool DrawEnabled(T_FLOAT delta_time);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const ActivityOption& GetOption() const
  {
    return this->option_;
  }

  GG_INLINE const TVec2f& GetScreenSize()
  {
    return this->option_.window_size;
  }

  GG_INLINE T_FLOAT GetScreenWidth()
  {
    return this->option_.window_size.width;
  }

  GG_INLINE T_FLOAT GetScreenHeight()
  {
    return this->option_.window_size.height;
  }

  GG_INLINE void PushScene(const SharedRef<Scene>& next, bool load = true)
  {
    this->scene_manager_->PushScene(next, load);
  }

  GG_INLINE void PopScene(bool unload = true)
  {
    this->scene_manager_->PopScene(unload);
  }

  GG_INLINE void ChangeScene(const SharedRef<Scene>& next)
  {
    this->scene_manager_->ChangeScene(next);
  }

  GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return this->scene_manager_->GetNowScene();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SceneManager* scene_manager_;
  UpdateEventState update_event_state_;
  ActivityOption option_;
  T_FLOAT elapsed_time_;
  ImGuiContext* imgui_context_;

};
