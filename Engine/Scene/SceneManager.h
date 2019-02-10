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
   */
  void PushScene(const SharedRef<Scene>& next);

  /*!
   * @brief ���݂�Scene��Scene�X�^�b�N�ɉ�����Scene��؂�ւ���
   */
  void PopScene();

  void ChangeScene(const SharedRef<Scene>& next);
  void ClearScene(const ActivityContext& context);

  void Update(const ActivityContext& context);
  void Draw(const ActivityContext& context);

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

  std::deque<SharedRef<Scene>> scene_stack_;
};
