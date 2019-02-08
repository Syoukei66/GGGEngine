#pragma once

#include <Setting/Setting.h>
#include <Converter/AssetConverterContext.h>
#include "IAssetConverterAddIn.h"

class AssetConverterDirector
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(AssetConverterDirector);

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Init(IAssetConverterAddIn* addin);
  static void Uninit();
  static void Fetch();
  static void Export();
  static void CreateProgram();
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  //static GG_INLINE UniqueIdTable* GetUniqueIdTable()
  //{
  //  return Self().unique_id_table_;
  //}
  //
  static GG_INLINE AssetConverterContext* GetContext()
  {
    return Self().context_;
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

  bool unique_id_table_load_failed_;

};