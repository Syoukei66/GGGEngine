#pragma once

#include <vector>
#include "CSVTokenizer.h"
#include "Resource.h"

class rcCsvData : public GGAssetObject
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcCsvData> CreateFromFile(const char* path);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  rcCsvData(const char* path);
  ~rcCsvData();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE virtual const char* GetResourceName() override
  {
    return "CsvData";
  }

  GG_INLINE T_UINT16 GetTokenizerCount() const
  {
    return (T_UINT16)this->tokenizers_.size();
  }
  GG_INLINE CsvTokenizer GetTokenizer(T_UINT16 line) const
  {
    return *this->tokenizers_[line];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<CsvTokenizer*> tokenizers_;

};