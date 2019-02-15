#include "CSVTokenizer.h"

// =================================================================
// CsvToken
// =================================================================
CsvToken CsvToken::Create(const std::string& str)
{
  if (str[0] == '\"')
  {
    std::string ret = std::string();
    ret.append(str, 1, str.length() - 2);
    return CsvToken(ret);
  }
  return CsvToken(str);
}

// =================================================================
// Constructor / Destructor
// =================================================================
CsvToken::CsvToken(const std::string& str)
  : str_(str)
{
}

// =================================================================
// Setter / Getter
// =================================================================
T_INT32 CsvToken::ToInt32() const
{
  return std::stoi(this->str_);
}

T_INT64 CsvToken::ToInt64() const
{
  return std::stol(this->str_);
}

T_FLOAT CsvToken::ToFloat() const
{
  return std::stof(this->str_);
}

T_DOUBLE CsvToken::ToDouble() const
{
  return std::stod(this->str_);
}

const std::string& CsvToken::ToString() const
{
  return this->str_;
}

// =================================================================
// CsvTokenizer
// =================================================================

// =================================================================
// Method
// =================================================================
CsvTokenizer::CsvTokenizer(const std::string& str)
{
  std::string strbuf = std::string();
  const char* p = str.c_str();
  while(*p != '\0' || *p == '\n')
  {
    if (*p == ',')
    {
      this->tokens_.emplace_back(CsvToken::Create(strbuf));
      strbuf.clear();
    }
    else
    {
      strbuf.append(p, 1);
    }
    ++p;
  }
  if (strbuf.length() > 0)
  {
    this->tokens_.emplace_back(CsvToken::Create(strbuf));
  }
  this->now_token_index_ = 0;
}

CsvTokenizer::CsvTokenizer(const CsvTokenizer& other)
  : tokens_(other.tokens_)
  , now_token_index_(0)
{
}

CsvTokenizer::~CsvTokenizer()
{
}

void CsvTokenizer::Reset()
{
  this->now_token_index_ = 0;
}

bool CsvTokenizer::HasNextToken()
{
  return this->now_token_index_ < this->tokens_.size();
}

const CsvToken& CsvTokenizer::NextToken()
{
  const CsvToken& ret = this->tokens_[this->now_token_index_];
  ++this->now_token_index_;
  return ret;
}
