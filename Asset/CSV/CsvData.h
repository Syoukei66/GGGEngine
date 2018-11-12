#pragma once

#include "CSVTokenizer.h"

class rcCsvData : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcCsvData);

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