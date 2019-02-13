#pragma once

#include <GUI/TextureSelectScene/TextureSelectScene.h>
#include <Converter/AssetConverterContext.h>

class AssetViewerBehavior;

/*!
 * @brief マテリアルを編集する為のImGuiウィンドウ
 */
class MaterialEditView
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  MaterialEditView();
  ~MaterialEditView();

  // =================================================================
  // Methods
  // =================================================================
public:
  SharedRef<rcMaterial> CreateEditMaterial(const MaterialData& data);
  bool EditWithImGui(AssetConverterContext* context);
  void Update();
  void Reload(AssetViewerBehavior* behavior, AssetConverterContext* context);

private:
  template <typename Type_>
  void SetMaterialProperty(const std::string& name, T_UINT8 count, T_UINT32 offset, size_t size, const MaterialData* data)
  {
    for (T_UINT8 i = 0; i < count; ++i)
    {
      this->material_->SetProperty<Type_>(name, i, *(Type_*)&data->data_[offset + size * i]);
    }
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  /*!
   * @brief 編集中のデータを優先モードかどうか調べる
   * @return 優先モードならtrue
   */
  inline bool IsMaster() const
  {
    return this->is_master_;
  }

  /*!
   * @brief 編集中のデータを取得する
   * @return 編集中のデータ
   */
  inline const MaterialData& GetEditData() const
  {
    return this->edit_data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  /*!
   * @brief 編集中のマテリアル
   */
  SharedRef<rcMaterial> material_;

  /*!
   * @brief 最新のデータを持っているか
   */
  bool is_master_;

  /*!
   * @brief データが更新されたか
   */
  bool is_updated_;

  /*!
   * @brief 編集中のデータをシェーダーの種類が切り替わってもデータを保持できるように退避させるマップ
   */
  std::unordered_map<std::string, MaterialData> edit_data_map_;

  /*!
   * @brief 編集中のデータ
   */
  MaterialData edit_data_;

  /*!
   * @brief テクスチャ選択用のScene
   */
  SharedRef<TextureSelectScene> texture_select_scene_;

  /*!
   * @brief 編集プロパティデータの一覧。
   * プロパティ宣言での順序を基に整列している
   */
  std::map<T_UINT8, MaterialPropertyData*> edit_property_datas_;

  /*!
   * @brief シェーダー一覧
   */
  std::map<std::string, SharedRef<AssetEntity>> shader_entities_;

  /*!
   * @brief ImGuiで使用する為のシェーダー名一覧
   */
  std::vector<char> shader_names_;
};