#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class Platform;

/*!
 * @brief �A�N�e�B�r�e�B�̏�Ԃ���Ȃ�
 * �v���b�g�t�H�[�����̏��⏈�����󂯎���
 */
class ActivityContext
{
  friend class Activity;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief �A�N�e�B�r�e�B����������
   */
  void Start(const ActivityOption& ao, const InputSetting& input_setting);

  /*!
   * @brief �A�N�e�B�r�e�B�I������
   */
  void End();

  /*!
   * @brief �t���[���̍ŏ��ɌĂяo������
   */
  void NewFrame(const SharedRef<Activity>& activity, const SharedRef<Platform>& platform);

  /*!
   * @brief �t���[���̍Ō�ɌĂяo������
   */
  void EndFrame();

  /*!
   * @brief �`�揈�����L�����ǂ����̔���
   * @param �o�ߎ���(�b)
   * @return false�Ȃ��ʂ̃A�b�v�f�[�g���s��Ȃ�
   */
  bool DrawEnabled();

protected:
  /*!
   * @brief �h����(�v���b�g�t�H�[��)�Œ�`����ActivityContext����������
   */
  virtual void OnStart(const ActivityOption& ao) = 0;

  /*!
   * @brief �h����(�v���b�g�t�H�[��)�Œ�`����ActivityContext�I������
   */
  virtual void OnEnd() = 0;

  /*!
   * @brief �h����(�v���b�g�t�H�[��)�Œ�`����t���[���̍ŏ��ɌĂяo������
   */
  virtual void OnNewFrame() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  /*!
   * @brief �A�N�e�B�r�e�B���A�N�e�B�u��Ԃ��m���߂�
   * @return false�Ȃ�A�N�e�B�u��Ԃł͂Ȃ�
   */
  virtual bool IsActive() const = 0;

  /*!
   * @brief �A�N�e�B�r�e�B���\����Ԃ��m���߂�
   * @return false�Ȃ�\����Ԃł͂Ȃ�
   */
  virtual bool IsVisible() const = 0;

  /*!
   * @brief �A�N�e�B�r�e�B��������Ԃ��m���߂�
   * @return false�Ȃ琶����Ԃł͂Ȃ�
   */
  virtual bool IsEnabled() const = 0;

  /*!
   * @brief �A�N�e�B�r�e�B����ӂɔF���ł���ID���擾����B
   * HWND�ȂǁA�v���b�g�t�H�[���ŗL�̒l������΂�����g�p����
   * @return ID
   */
  virtual T_UINT64 GetActivityID() const = 0;

  GG_INLINE const ActivityOption& GetOption() const
  {
    return this->option_;
  }

  GG_INLINE const TVec2f& GetScreenSize() const
  {
    return this->option_.window_size;
  }

  GG_INLINE T_FLOAT GetScreenWidth() const
  {
    return this->option_.window_size.width;
  }

  GG_INLINE T_FLOAT GetScreenHeight() const
  {
    return this->option_.window_size.height;
  }

  GG_INLINE const std::unique_ptr<ImGuiContext>& GetImGuiContext() const
  {
    return this->imgui_context_;
  }

  GG_INLINE const InputState* Input(T_UINT8 id) const
  {
    return this->input_context_->GetState(id);
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityOption option_;
  std::unique_ptr<ImGuiContext> imgui_context_;
  InputContext* input_context_;
  T_FLOAT elapsed_time_;

};
