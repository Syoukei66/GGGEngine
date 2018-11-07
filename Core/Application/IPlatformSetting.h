#pragma once

#include <Core/Application/Activity/ActivityOption.h>

class GraphicsAPI;
class AudioAPI;
class InputAPI;
class Activity;

/*!
 * @brief �Q�[���̃G���g���|�C���g����Ăяo����鏈�����`����N���X
 */

class IPlatformSetting
{
  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief �A�N�e�B�r�e�B�̍쐬
   */
  virtual UniqueRef<Activity> CreateActivity(const ActivityOption& option) const = 0;

  /*!
   * @brief �O���t�B�b�N�XAPI�̍쐬
   */
  virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI() const = 0;

  /*!
   * @brief �I�[�f�B�IAPI�̍쐬
   */
  virtual UniqueRef<AudioAPI> CreateAudioAPI() const = 0;

  /*!
   * @brief �n�[�h�E�F�A����API�̍쐬
   */
  virtual UniqueRef<InputAPI> CreateInputAPI(const InputSetting& setting) const = 0;

};