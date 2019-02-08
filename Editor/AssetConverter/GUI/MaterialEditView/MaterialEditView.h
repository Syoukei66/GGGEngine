#pragma once

class MaterialEditView
{
  // =================================================================
  // Methods
  // =================================================================
public:
  SharedRef<rcMaterial> CreateEditMaterial(const MaterialData& data);
  bool EditWithImGui();
  void Update();

private:
  template <typename Type_>
  void SetMaterialProperty(const std::string& name, T_UINT8 count, T_UINT32 offset, size_t size, const MaterialData* data)
  {
    for (T_UINT8 i = 0; i < count; ++i)
    {
      this->material_->GetProperty<Type_>(name, i) = *(Type_*)&data->data_[offset + size * i];
    }
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool IsMaster() const
  {
    return this->is_master_;
  }

  inline const MaterialData& GetEditData() const
  {
    return this->edit_data_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<rcMaterial> material_;

  /*!
   * @brief 最新のデータを持っているか
   */
  bool is_master_;

  /*!
   * @brief データが更新されたか
   */
  bool is_updated_;
  MaterialData edit_data_;

};