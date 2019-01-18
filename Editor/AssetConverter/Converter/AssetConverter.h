#pragma once

#include <Entity/AssetEntity.h>

class AssetProgramGenerator;

class AssetConverter 
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  AssetConverter(
    const std::string& id,
    const std::string& class_name,
    const std::vector<std::string>& extensions,
    T_UINT32 skip_head, T_UINT32 skip_tail
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * URIが表すファイルがConverterに対応しているかチェックする
   * @param uri ファイルのURI
   * @return 対応していればtrue
   */
  bool IsTarget(const URI& uri) const;

  /*!
   * @brief メタデータからアセットをインポートし、中間データを戻り値で返す
   * @param meta_data メタデータ
   * @param context AssetConverterContext
   * @return 中間データ
   */
  IAssetDataContainer* ImportImmediately(AssetMetaData* meta_data, AssetConverterContext* context) const;

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
  virtual void RegisterAssetManager(const SharedRef<AssetEntity>& entity) const = 0;

  /*!
   * @brief AssetConverter固有の設定クラスを生成し、戻り値として返す。
   */
  virtual std::unique_ptr<ConverterSetting> CreateSetting() const = 0;

protected:
  /*!
   * @brief アセットのインポート実処理
   * 派生クラス側で実際のインポート処理を記述する。
   */
  virtual IAssetDataContainer* ImportProcess(AssetMetaData* meta, AssetConverterContext* context) const = 0;

  /*!
   * @brief アセットのインポート実処理
   * 派生クラス側で実際のエクスポート処理を記述する。
   */
  virtual void ExportProcess(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const = 0;

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
  std::vector<std::string> target_extensions_;
  AssetProgramGenerator* program_generator_;

};
