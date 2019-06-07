#include "CSVData.h"
#include <fstream>

// =================================================================
// Factory Method
// =================================================================
UniqueRef<rcCsvData> rcCsvData::CreateFromFile(const char* path)
{
  return UniqueRef<rcCsvData>(new rcCsvData(path));
}

// =================================================================
// Constructor / Destructor
// =================================================================
rcCsvData::rcCsvData(const char* path)
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
    CsvTokenizer* tokenizer = new CsvTokenizer(str);
    if (tokenizer->GetSize() == 0)
    {
      delete tokenizer;
      continue;
    }
    this->tokenizers_.emplace_back(tokenizer);
  }
  GG_ASSERT(this->tokenizers_.size() > 0, "CSV�t�@�C���̓ǂݍ��݂Ɏ��s���܂���");
}

rcCsvData::~rcCsvData()
{
  for (CsvTokenizer* tokenizer : this->tokenizers_)
  {
    delete tokenizer;
  }
}
