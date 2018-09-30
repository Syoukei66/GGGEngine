#pragma once

#include <vector>
#include <functional>

#include <Core/UniqueIdTable.h>

#include "Setting.h"
#include "AssetConverterContext.h"
#include "AssetConverterManager.h"

class Director
{
  // =================================================================
  // Singleton Constructor / Destructor
  // =================================================================
public:
  static Director& GetInstance()
  {
    static Director self;
    return self;
  }

public:
  Director(const Director&) = delete;
  Director& operator=(const Director&) = delete;
  Director(Director&&) = delete;
  Director& operator=(Director&&) = delete;

private:
  Director() = default;
  ~Director() = default;

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