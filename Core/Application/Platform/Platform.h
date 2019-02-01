#pragma once

#include <Core/Application/Activity/ActivityContext.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/IApplicationBehavior.h>

class Platform : public GGObject
{
  friend class Application;

  // =================================================================
  // Methods
  // =================================================================
protected:
  /*!
   * @brief �v���b�g�t�H�[���̏���������
   * @returns false�Ȃ玸�s
   */
  bool Init(const ApplicationOption& option);

  /*!
   * @brief �v���b�g�t�H�[���̏I������
   * @returns false�Ȃ玸�s
   */
  bool Uninit();

  /*!
   * @brief �v���b�g�t�H�[���̃A�b�v�f�[�g���������ǂ����̔���
   * @return false�Ȃ�I��
   */
  virtual bool ContinueEnabled() = 0;

  /*!
   * @brief �t���[���������L�����ǂ����̔���
   * @return false�Ȃ�A�b�v�f�[�g�������s�킸�ҋ@����
   */
  virtual bool FrameEnabled() = 0;

  virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<AudioAPI> CreateAudioAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<InputAPI> CreateInputAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<ActivityContext> CreateMainActivityContext() const = 0;
  virtual UniqueRef<ActivityContext> CreateActivityContext() const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<GraphicsAPI> GetGraphicsAPI()
  {
    return this->graphics_api_;
  }

  GG_INLINE SharedRef<AudioAPI> GetAudioAPI()
  {
    return this->audio_api_;
  }

  GG_INLINE SharedRef<InputAPI> GetInputAPI()
  {
    return this->input_api_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GraphicsAPI> graphics_api_;
  SharedRef<AudioAPI> audio_api_;
  SharedRef<InputAPI> input_api_;

};