#pragma once

#include "GGRefSFINAE.h"

/*!
 * @brief GGGEngineで使用する全てのオブジェクトの基底クラス
 * リファレンスカウンタを持っており、ガーベッジコレクタで自動解放される。
 * リファレンスカウンタをObject自身が持っているのは、
 * Refに持たせた場合だとコピーコストが発生する為。
 */
class GGObject
{
  GG_NO_COPYABLE(GGObject);

  friend class GGObjectManager;
  template <class Obj_, GGIsObject<Obj_>>
  friend class GGRef;
  template <class Obj_>
  friend class SharedRef;
  template <class Obj_>
  friend class UniqueRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  GGObject() = default;
  virtual ~GGObject() = default;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief ObjectManagerに管理されているかのフラグを立てる
   * 二重登録の防止などに使用する
   */
  GG_INLINE void Managed() const
  {
    const_cast<GGObject*>(this)->managed_ = true;
  }

  /*!
   * @brief ObjectManagerに管理されているか
   */
  GG_INLINE bool IsManaged() const
  {
    return this->managed_;
  }

  /*!
   * @brief リファレンスカウンタの増加
   */
  GG_INLINE void Retain() const
  {
    ++const_cast<GGObject*>(this)->reference_count_;
  }

  /*!
   * @brief リファレンスカウンタの減少
   */
  GG_INLINE void Release() const
  {
    GG_ASSERT(this->reference_count_ > 0, "リファレンスカウンタが0の時にReleaseしました");
    --const_cast<GGObject*>(this)->reference_count_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:

  /*!
   * @brief デバッグ時やログ上で表示されるオブジェクト名。
   * 定義する際はGG_OBJ_NAMEマクロを使用する事を推奨
   */
  virtual const char* GetObjectName() const = 0;

  /*!
   * @brief デバッグ時やログ上で表示される使用メモリサイズ。
   * 派生クラス側でoverrideしないとメモリサイズ参照時エラーログが表示される。
   */
  virtual size_t GetMemorySize() const;

  /*!
   * @brief デバッグ時やログ上で表示される使用ビデオメモリサイズ。
   * 派生クラス側でoverrideしないとビデオメモリサイズ参照時エラーログが表示される。
   */
  virtual size_t GetVideoMemorySize() const;

  GG_INLINE T_UINT32 GetReferenceCount() const
  {
    return this->reference_count_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  bool managed_;
  T_UINT32 reference_count_;

};