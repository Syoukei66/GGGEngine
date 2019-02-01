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

  void ChangeScene(const SharedRef<Scene>& next, bool need_unload = true);
  void ClearScene();

  void Update();
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

  /*!
   * @brief �V�[���J�ڂ��A�b�v�f�[�g�̃^�C�~���O�ōs���ׂ̃o�b�t�@
   */
  SharedRef<Scene> next_scene_;
  bool unload_now_scene_;

  std::deque<SharedRef<Scene>> scene_stack_;
};
