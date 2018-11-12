#pragma once

struct EngineOption;

/*!
 * @brief �G���W���̓�����`����N���X
 */
class IEngineBehavior 
{
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
   * @brief �G���W���ݒ�̃J�X�^�}�C�Y
   */
  virtual void SetupEngineOption(EngineOption& option) = 0;

  /*!
   * @brief �A�v���P�[�V�����쐬���ɌĂ΂��C�x���g
   */
  virtual void OnApplicationBegin() {}

  /*!
   * @brief �A�v���P�[�V�����I�����ɌĂ΂��C�x���g
   */
  virtual void OnApplicationEnd() {}

  /*!
   * @brief �Q�[���J�n���ɌĂ΂��C�x���g
   */
  virtual void OnGameBegin() {}

  /*!
   * @brief �Q�[���J�n���ɌĂ΂��C�x���g
   */
  virtual void OnGameEnd() {}

  /*!
   * @brief �ŏ��ɌĂяo�����Scene
   */
  virtual SharedRef<Scene> FirstScene() = 0;
};