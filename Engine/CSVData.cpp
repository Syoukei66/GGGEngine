#include "CSVData.h"
#include "NativeAssert.h"
#include <fstream>

// =================================================================
// Constructor / Destructor
// =================================================================
CSVData::CSVData(const char* path)
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
    this->tokenizers_.push_back(tokenizer);
  }
  NATIVE_ASSERT(this->tokenizers_.size() > 0, "CSVƒtƒ@ƒCƒ‹‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
}

CSVData::~CSVData()
{
  for (CSVTokenizer* tokenizer : this->tokenizers_)
  {
    delete tokenizer;
  }
}
