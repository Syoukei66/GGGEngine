#include "CSVData.h"
#include "../Core/NativeAssert.h"
#include <fstream>

// =================================================================
// Constructor / Destructor
// =================================================================
CsvData::CsvData(const char* path)
{
  std::ifstream ifs(path);
  std::string str;
  while (getline(ifs, str))
  {
    const char& head = str[0];
    if (head == '/' || head == '\n')
    {
      continue;
    }
    CSVTokenizer* tokenizer = new CSVTokenizer(str);
    if (tokenizer->GetSize() == 0)
    {
      delete tokenizer;
      continue;
    }
    this->tokenizers_.emplace_back(tokenizer);
  }
  NATIVE_ASSERT(this->tokenizers_.size() > 0, "CSVƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

CsvData::~CsvData()
{
  for (CSVTokenizer* tokenizer : this->tokenizers_)
  {
    delete tokenizer;
  }
}
