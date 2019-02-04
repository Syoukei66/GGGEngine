#pragma once

struct ImGuiContext;
class Platform;

/*!
 * @brief �A�N�e�B�r�e�B�̏�Ԃ���Ȃ�
 * �v���b�g�t�H�[�����̏��⏈�����󂯎���
 */
class ActivityContext : public GGObject
{
  friend class Activity;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief �A�N�e�B�r�e�B����������
   */
  void Start(const ActivityOption& ao);

  /*!
   * @brief �A�N�e�B�r�e�B�I������
   */
  void End();

  /*!
   * @brief �t���[���̍ŏ��ɌĂяo������
   */
  void NewFrame(const SharedRef<Platform>& platform);

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

  GG_INLINE const std::unique_ptr<ImGuiContext>& GetImGuiContext()
  {
    return this->imgui_context_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  ActivityOption option_;
  std::unique_ptr<ImGuiContext> imgui_context_;
  T_FLOAT elapsed_time_;

};
