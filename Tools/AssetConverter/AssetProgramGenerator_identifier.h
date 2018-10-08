#pragma once

#include "AssetInfo.h"

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
  std::string CreateIdentifier(const AssetInfo* info) const;

  // =================================================================
  // Data Members
  // =================================================================
public:
  T_UINT32 skip_head_;
  T_UINT32 skip_tail_;

  std::unordered_map<const AssetInfo*, std::string> cache_;

};

