#pragma once

class GGObject;

/*!
* @brief GGRefで参照を管理されているGGObjectの管理クラス
* GCなどの機能を提供する。
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