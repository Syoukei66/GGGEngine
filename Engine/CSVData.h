#pragma once

#include <vector>
#include "CSVTokenizer.h"

class CSVData
{
public:
  CSVData(const char* path);
  ~CSVData();

public:
  inline T_UINT16 GetTokenizerCount() const
  {
    return (T_UINT16)this->tokenizers_.size();
  }
  inline CSVTokenizer GetTokenizer(T_UINT16 line) const
  {
    return *this->tokenizers_[line];
  }

private:
  std::vector<CSVTokenizer*> tokenizers_;

};