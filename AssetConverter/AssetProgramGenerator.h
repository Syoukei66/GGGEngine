#pragma once

#include <vector>
#include "AssetManager.h"

namespace AssetProgram
{

class Generator
{
public:
  Generator();

public:
  void Generate(const AssetManager& asset_manager, std::string* header, std::string* cpp);
  
};

}
