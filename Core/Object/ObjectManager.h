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
  static void Init();
  static void Uninit();
  static void Update();

  static GG_INLINE void Manage(GGObject* obj)
  {
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