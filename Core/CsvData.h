#pragma once

#include <vector>
#include "CSVTokenizer.h"
#include "Resource.h"

class rcCsvData : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static rcCsvData* CreateFromFile(const char* path);

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
  inline T_UINT16 GetTokenizerCount() const
  {
    return (T_UINT16)this->tokenizers_.size();
  }
  inline CsvTokenizer GetTokenizer(T_UINT16 line) const
  {
    return *this->tokenizers_[line];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<CsvTokenizer*> tokenizers_;

};