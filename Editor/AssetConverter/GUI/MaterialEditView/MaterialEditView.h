#pragma once

#include <GUI/TextureSelectScene/TextureSelectScene.h>
#include <Converter/AssetConverterContext.h>

class AssetViewerBehavior;

/*!
 * @brief �}�e���A����ҏW����ׂ�ImGui�E�B���h�E
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
   * @brief �ҏW���̃f�[�^��D�惂�[�h���ǂ������ׂ�
   * @return �D�惂�[�h�Ȃ�true
   */
  inline bool IsMaster() const
  {
    return this->is_master_;
  }

  /*!
   * @brief �ҏW���̃f�[�^���擾����
   * @return �ҏW���̃f�[�^
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
   * @brief �ҏW���̃}�e���A��
   */
  SharedRef<rcMaterial> material_;

  /*!
   * @brief �ŐV�̃f�[�^�������Ă��邩
   */
  bool is_master_;

  /*!
   * @brief �f�[�^���X�V���ꂽ��
   */
  bool is_updated_;

  /*!
   * @brief �ҏW���̃f�[�^���V�F�[�_�[�̎�ނ��؂�ւ���Ă��f�[�^��ێ��ł���悤�ɑޔ�������}�b�v
   */
  std::unordered_map<std::string, MaterialData> edit_data_map_;

  /*!
   * @brief �ҏW���̃f�[�^
   */
  MaterialData edit_data_;

  /*!
   * @brief �e�N�X�`���I��p��Scene
   */
  SharedRef<TextureSelectScene> texture_select_scene_;

  /*!
   * @brief �ҏW�v���p�e�B�f�[�^�̈ꗗ�B
   * �v���p�e�B�錾�ł̏�������ɐ��񂵂Ă���
   */
  std::map<T_UINT8, MaterialPropertyData*> edit_property_datas_;

  /*!
   * @brief �V�F�[�_�[�ꗗ
   */
  std::map<std::string, SharedRef<AssetEntity>> shader_entities_;

  /*!
   * @brief ImGui�Ŏg�p����ׂ̃V�F�[�_�[���ꗗ
   */
  std::vector<char> shader_names_;
};