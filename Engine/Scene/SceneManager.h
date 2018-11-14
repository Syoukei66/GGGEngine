#pragma once

#include "Scene.h"

class UpdateEventState;

class SceneManager
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���݂�Scene��Scene�X�^�b�N�ɉ�����Scene��؂�ւ���
   * Scene�̃��[�h/�A�����[�h�͎����I�ɍs���Ȃ�
   */
  void PushScene(const SharedRef<Scene>& next, bool load_current = true);

  /*!
   * @brief ���݂�Scene��Scene�X�^�b�N�ɉ�����Scene��؂�ւ���
   * Scene�̃��[�h/�A�����[�h�͎����I�ɍs���Ȃ�
   */
  void PopScene(bool unload_current = true);

  void ChangeScene(const SharedRef<Scene>& next);
  void ClearScene();

  void Update(const UpdateEventState& state);
  void Draw();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<Scene> GetNowScene()
  {
    return this->now_scene_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<Scene> now_scene_;
  std::deque<SharedRef<Scene>> scene_stack_;
};
