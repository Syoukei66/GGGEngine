#pragma once

#include <Setting/Setting.h>
#include <Converter/AssetConverterContext.h>
#include <Converter/AssetConverterManager.h>

class AssetConverterDirector
{
  // =================================================================
  // GGG Editor
  // =================================================================
  GG_SINGLETON(AssetConverterDirector);

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init();
  static void Uninit();
  static void Import();
  static void Export();
  static void CreateProgram();

private:
  static void CreateDefaultAssets();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE UniqueIdTable* GetUniqueIdTable()
  {
    return Self().unique_id_table_;
  }
  
  static GG_INLINE AssetConverterContext* GetContext()
  {
    return Self().context_;
  }

  static GG_INLINE AssetConverterManager* GetConverterManager()
  {
    return Self().converter_manager_;
  }

  static GG_INLINE bool IsUniqueIdTableLoadFailed()
  {
    return Self().unique_id_table_load_failed_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  Setting* setting_;
  UniqueIdTable* unique_id_table_;
  AssetConverterContext* context_;
  AssetConverterManager* converter_manager_;

  bool unique_id_table_load_failed_;

};