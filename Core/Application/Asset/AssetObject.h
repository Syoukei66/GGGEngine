#pragma once

template <class Asset_>
class AssetLoader;

/*!
 * @brief GGGEngine���Ǘ�����A�Z�b�g�̊��N���X
 */
class GGAssetObject : public GGObject
{
  template <class Asset_>
  friend class AssetLoader;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE T_UINT32 GetUniqueId() const
  {
    return this->unique_id_;
  }

private:
  GG_INLINE void SetUniqueId(T_UINT32 unique_id)
  {
    this->unique_id_ = unique_id;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 unique_id_;

};
