#pragma once

#include <Entity/AssetImporter.h>
#include <Entity/AssetExporter.h>
#include <ProgramGenerator/AssetProgramGenerator.h>

class AssetConverter 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverter(
    const std::string& id,
    AssetImporter* importer,
    AssetExporter* exporter,
    AssetProgramGenerator* program_generator
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief メタデータからアセットをインポートし、中間データを戻り値で返す
   * @param meta_data メタデータ
   * @param context AssetConverterContext
   * @return 中間データ
   */
  void* ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context);

  /*!
   * @brief アセットをエクスポートする。
   * @param entity AssetEntity
   * @param context AssetConverterContext
   */
  void ExportImmediately(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const;

  /*!
   * @brief プログラムを出力する
   * @param entities AssetEntity一覧
   * @param header headerファイルプログラム書き込み先
   * @param cpp cppファイルプログラム書き込み先
   */
  void CreateProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* header, std::string* cpp) const;

  /*!
   * @brief AssetManagerにアセットを登録する
   * @param entity AssetEntity
   */
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline const std::string& GetId() const
  {
    return this->id_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string id_;
  AssetImporter* importer_;
  AssetExporter* exporter_;
  AssetProgramGenerator* program_generator_;

};
