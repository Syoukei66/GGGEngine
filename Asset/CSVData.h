#pragma once

#include <vector>
#include "CSVTokenizer.h"

class CsvData
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  CsvData(const char* path);
  ~CsvData();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_UINT16 GetTokenizerCount() const
  {
    return (T_UINT16)this->tokenizers_.size();
  }
  inline CSVTokenizer GetTokenizer(T_UINT16 line) const
  {
    return *this->tokenizers_[line];
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::vector<CSVTokenizer*> tokenizers_;

};