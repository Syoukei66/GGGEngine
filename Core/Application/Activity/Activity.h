#pragma once

#include <Core/Application/Activity/ActivityOption.h>
#include <Core/Application/Event/UpdateEventState.h>
#include <Core/Application/Platform/Platform.h>
#include "ActivityContext.h"

/*!
 * @brief �E�B���h�E�ȂǁA�P�̃A�v���P�[�V�������s�C���X�^���X�̃N���X
 */
class Activity : public GGObject
{
  friend class Application;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief �A�N�e�B�r�e�B����������
   */
  void Start(const ActivityOption& ao, const InputSetting& setting, ActivityContext* context);

  /*!
   * @brief �A�N�e�B�r�e�B�I������
   */
  void EndActivity();

  /*!
   * @brief �R���e�L�X�g�I������
   */
  void EndContext();

  /*!
   * @brief �A�N�e�B�r�e�B�̃A�b�v�f�[�g����
   * @return false�Ȃ�A�N�e�B�r�e�B�I��
   */
  bool Update(const SharedRef<Platform>& platform);

protected:
  /*!
   * @brief �h����Œ�`����A�N�e�B�r�e�B����������
   */
  virtual void OnStart() {}

  /*!
   * @brief �h����Œ�`����A�N�e�B�r�e�B�I������
   */
  virtual void OnEnd() {}

  /*!
   * @brief �h����Œ�`����A�N�e�B�r�e�B�X�V����
   */
  virtual void OnUpdate() {}

  /*!
   * @brief �h����Œ�`����A�N�e�B�r�e�B�`�揈��
   */
  virtual void OnDraw(const SharedRef<Platform>& platform) {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE ActivityContext& GetContext()
  {
    return *this->context_;
  }

  GG_INLINE const ActivityContext& GetContext() const
  {
    return *this->context_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityContext* context_;

};
