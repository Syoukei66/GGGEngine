#pragma once

#include <Entity/AssetEntity.h>
#include <Scene/AssetViewer/AssetViewerBehavior.h>

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
    T_UINT32 skip_head, T_UINT32 skip_tail,
    const SharedRef<AssetViewerBehavior>& viewer
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
   * @param entity AssetEntity
   * @param context AssetConverterContext
   * @return 中間データ
   */
  IAssetDataContainer* ImportImmediately(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const;

  /*!
   * @brief アセットをエクスポートする。
   * @param entity AssetEntity
   * @param context AssetConverterContext
   */
  void ExportImmediately(const SharedRef<AssetEntity>& entity, const AssetConverterContext* context) const;

  /*!
   * @brief .hプログラムを出力する
   * @param entities AssetEntity一覧
   * @param dest プログラム書き込み先
   */
  void CreateHeaderProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest) const;

  /*!
   * @brief .cppプログラムを出力する
   * @param entities AssetEntity一覧
   * @param dest プログラム書き込み先
   */
  void CreateCppProgram(const std::vector<SharedRef<AssetEntity>>& entities, std::string* dest) const;

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
   * @return nullptrや、現在のDataContainerと同じDataContainerを返してもいい
   */
  virtual IAssetDataContainer* ImportProcess(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const = 0;

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

  inline const SharedRef<AssetViewerBehavior>& GetViewerBehavior()
  {
    return this->viewer_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string id_;
  std::vector<std::string> target_extensions_;
  AssetProgramGenerator* program_generator_;
  SharedRef<AssetViewerBehavior> viewer_;

};
