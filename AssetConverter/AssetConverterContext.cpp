#include "AssetConverterContext.h"
#include "../Core/CerealIO.h"

// =================================================================
// Constructor / Destructor
// =================================================================
AssetConverterContext::AssetConverterContext(const Setting* setting, AssetConverterManager* converter_manager)
  : setting_(setting)
  , converter_manager_(converter_manager)
{
  this->unique_id_table_ = CerealIO::Binary::SafeImport<UniqueIdTable>(setting->unique_id_table_path.c_str());
  if (!this->unique_id_table_)
  {
    this->unique_id_table_ = new UniqueIdTable();
  }
}

AssetConverterContext::~AssetConverterContext()
{
  delete this->unique_id_table_;
}

// =================================================================
// Methods
// =================================================================
AssetInfo* AssetConverterContext::Reserve(const std::string& directory_path, const std::string& file_name, const std::string& extension)
{
  AssetInfo* info = this->converter_manager_->Find<AssetInfo>([&](IAssetConverter* converter)
  {
    //Info���������ꂽ��\�񐬌��A���[�v���甲����
    return converter->Reserve(directory_path, file_name, extension, this);
  });

  //�ΏۂɂȂ�Ȃ������ꍇ�̓X�L�b�v
  if (!info)
  {
    std::cout << "skip \"" << file_name << "\" " << std::endl;
  }
  return info;
}
