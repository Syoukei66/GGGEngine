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
  NATIVE_ASSERT(this->tokenizers_.size() > 0, "CSV�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
}

CsvData::~CsvData()
{
  for (CSVTokenizer* tokenizer : this->tokenizers_)
  {
    delete tokenizer;
  }
}
