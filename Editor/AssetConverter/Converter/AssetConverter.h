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
    T_UINT32 skip_head, T_UINT32 skip_tail
  );

  virtual ~AssetConverter();

  // =================================================================
  // Methods
  // =================================================================
public:
  /*!
   * @brief URIが表すファイルがConverterに対応しているかチェックする
   * @param uri ファイルのURI
   * @return 対応していればtrue
   */
  bool IsTarget(const URI& uri) const;

  /*!
   * @brief AssetConverter側で新しいインスタンスを作成する事が可能かチェックする
   * @return 可能ならtrue
   */
  virtual bool CanCreateNewInstance() const = 0;

  /*!
   * @brief メタデータからアセットをインポートし、中間データを戻り値で返す
   * @param entity AssetEntity
   * @param context AssetConverterContext
   * @return 中間データ
   */
  IAssetDataContainer* ImportImmediately(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const;

  /*!
   * @brief キャッシュからアセットをインポートし、中間データを戻り値で返す
   * @param entity AssetEntity
   * @param context AssetConverterContext
   * @return 中間データ
   */
  virtual IAssetDataContainer* ImportFromCache(const SharedRef<AssetEntity>& entity, AssetConverterContext* context) const = 0;

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
   * @brief 新しいインスタンスを作成し、保存する
   * @return 成功したらtrue
   */
  virtual bool CreateNewInstance(const URI& uri) const = 0;

  /*!
   * @brief AssetConverter固有の設定クラスを生成し、戻り値として返す。
   */
  virtual std::unique_ptr<ConverterSetting> CreateSetting() const = 0;

  /*!
   * @brief 使用するAssetViewerBehaviorを作成する
   * @return 
   */
  virtual SharedRef<AssetViewerBehavior> CreateViewerBehavior() const = 0;

  /*!
   * @brief 引数で指定したAssetクラス名のアセットに変換するConverterなのかを確かめる
   * @param asset_name Assetクラス名
   * @return 変換後Assetクラス名と一致していればtrue
   */
  virtual bool IsTargetAsset(const std::string& asset_name) const = 0;

  /*!
   * @brief テンプレート引数で指定したAssetクラスに変換するConverterなのかを確かめる
   * @return 変換後Assetクラスと一致していればtrue
   */
  template <class Asset_>
  bool IsTargetAsset() const
  {
    return this->IsTargetAsset(Asset_::ObjectName());
  }

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

  inline const std::vector<std::string>& GetTargetExtensions() const
  {
    return this->target_extensions_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  std::string id_;
  std::vector<std::string> target_extensions_;
  AssetProgramGenerator* program_generator_;

};
