#pragma once

class GGObject;

/*!
* @brief GGRef�ŎQ�Ƃ��Ǘ�����Ă���GGObject�̊Ǘ��N���X
* GC�Ȃǂ̋@�\��񋟂���B
*/
class GGObjectManager
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(GGObjectManager);

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief ���݃��t�@�����X�J�E���^��0�ƂȂ��Ă���I�u�W�F�N�g��S�ĉ������
   */
  static void GC();

  /*!
   * @brief ���݊Ǘ�����Ă���I�u�W�F�N�g�S�Č������A���O�ɏo�͂���
   * �v���O�����̏I�������A�S�ẴI�u�W�F�N�g���������Ă��Ȃ���΂Ȃ�Ȃ�
   * �^�C�~���O�Ŏg�p����
   * @return true�Ȃ疢�J�����\�[�X����
   */
  static bool CheckLeak();

  /*!
   * @brief ���t�@�����X�J�E���^��0�ƂȂ��Ă���I�u�W�F�N�g���������
   * ������鐔�̓p�t�H�[�}���X�Ƒ��k���Č��肷��
   */
  static void Update();

  /*!
   * @brief �C���X�^���X���Ǘ�����I�u�W�F�N�g�̒ǉ��B
   * Ref�N���X�������͂��̔h���N���X���R���X�g���N�^�Ŏ󂯎����
   * ���|�C���^�ɑ΂��Ă��̏������Ăяo���Ă����̂�
   * �����I�ɊǗ����Ă����
   */
  static GG_INLINE void Manage(GGObject* obj)
  {
    if (obj->IsManaged())
    {
      return;
    }
    obj->Managed();
    Self().objects_.emplace_back(obj);
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static size_t GetMemorySize();
  static size_t GetVideoMemorySize();

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::list<GGObject*> objects_;

};