#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/ApplicationOption.h>
#include <Core/Application/Event/UpdateEventState.h>

class Scene;

/*!
 * @brief �A�v���P�[�V�����̓�����`����N���X
 */
class IApplicationBehavior
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief �A�v���P�[�V�����ݒ�̃J�X�^�}�C�Y
   */
  virtual void SetupApplicationOption(ApplicationOption& option) = 0;

  /*!
   * @brief ���C���A�N�e�B�r�e�B�ݒ�̃J�X�^�}�C�Y
   */
  virtual void SetupMainActivityOption(ActivityOption& option) = 0;

  /*!
   * @brief �A�v���P�[�V�����쐬���ɌĂ΂��C�x���g
   */
  virtual void OnApplicationBegin() {}

  /*!
   * @brief �A�v���P�[�V�����I�����ɌĂ΂��C�x���g
   */
  virtual void OnApplicationEnd() {}

  /*!
   * @brief �A�v���P�[�V�����̊J�n����
   */
  virtual void Init() = 0;

  /*!
   * @brief �A�v���P�[�V�����̏I������
   */
  virtual void Uninit() = 0;

};
