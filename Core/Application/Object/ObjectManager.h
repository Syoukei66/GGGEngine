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
  /*!
   * @brief 現在リファレンスカウンタが0となっているオブジェクトを全て解放する
   */
  static void GC();

  /*!
   * @brief 現在管理されているオブジェクト全て検査し、ログに出力する
   * プログラムの終了時等、全てのオブジェクトが解放されていなければならない
   * タイミングで使用する
   * @return trueなら未開放リソースあり
   */
  static bool CheckLeak();

  /*!
   * @brief リファレンスカウンタが0となっているオブジェクトを解放する
   * 解放する数はパフォーマンスと相談して決定する
   */
  static void Update();

  /*!
   * @brief インスタンスを管理するオブジェクトの追加。
   * Refクラスもしくはその派生クラスがコンストラクタで受け取った
   * 生ポインタに対してこの処理を呼び出してくれるので
   * 自動的に管理してくれる
   */
  static GG_INLINE void Manage(const GGObject* obj)
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
  std::list<const GGObject*> objects_;

};