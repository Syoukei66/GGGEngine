#pragma once

#include "Setting.h"
#include "AssetConverterContext.h"
#include "AssetConverterManager.h"

class AssetConverterDirector
{
  // =================================================================
  // Singleton Constructor / Destructor
  // =================================================================
public:
  static AssetConverterDirector& GetInstance()
  {
    static AssetConverterDirector self;
    return self;
  }

public:
  AssetConverterDirector(const AssetConverterDirector&) = delete;
  AssetConverterDirector& operator=(const AssetConverterDirector&) = delete;
  AssetConverterDirector(AssetConverterDirector&&) = delete;
  AssetConverterDirector& operator=(AssetConverterDirector&&) = delete;

private:
  AssetConverterDirector() = default;
  ~AssetConverterDirector() = default;

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init();
  void Uninit();
  void Import();
  void Export();
  void CreateProgram();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:

  // =================================================================
  // Data Members
  // =================================================================
private:
  Setting* setting_;
  UniqueIdTable* unique_id_table_;
  AssetConverterContext* context_;
  AssetConverterManager* converter_manager_;

};