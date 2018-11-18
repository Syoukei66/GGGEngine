#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
          
/*!
 * @brief �A�v���P�[�V�����𓮍삳����N���X
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
protected:
  /*!
   * @brief �Q�[�����������ǂ����̔���
   * @return false�Ȃ�Q�[���I��
   */
  virtual bool ContinueEnabled() = 0;

  /*!
   * @brief �t���[���������L�����ǂ����̔���
   * @return false�Ȃ�A�b�v�f�[�g�������s�킸�ҋ@����
   */
  virtual bool FrameEnabled() = 0;

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

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityOption option_;
  T_FLOAT elapsed_time_;

};
