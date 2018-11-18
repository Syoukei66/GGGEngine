#pragma once

#include <Entity/AssetMetaData.h>

class IdentifierGenerator
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  IdentifierGenerator(T_UINT32 skip_head, T_UINT32 skip_tail);

  // =================================================================
  // Methods
  // =================================================================
public:
  std::string CreateIdentifier(const AssetMetaData* meta) const;

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_UINT32 skip_head_;
  T_UINT32 skip_tail_;

  std::unordered_map<const AssetMetaData*, std::string> cache_;

};

