#include "CSVTokenizer.h"

// =================================================================
// CSVToken
// =================================================================
CSVToken CSVToken::Create(const std::string& str)
{
  if (str[0] == '\"')
  {
    std::string ret = std::string();
    ret.append(str, 1, str.length() - 2);
    return CSVToken(ret);
  }
  return CSVToken(str);
}

// =================================================================
// Constructor / Destructor
// =================================================================
CSVToken::CSVToken(const std::string& str)
  : str_(str)
{
}

// =================================================================
// Setter / Getter
// =================================================================
T_INT32 CSVToken::ToInt32() const
{
  return std::stoi(this->str_);
}

T_INT64 CSVToken::ToInt64() const
{
  return std::stol(this->str_);
}

T_FLOAT CSVToken::ToFloat() const
{
  return std::stof(this->str_);
}

T_DOUBLE CSVToken::ToDouble() const
{
  return std::stod(this->str_);
}

const std::string& CSVToken::ToString() const
{
  return this->str_;
}

// =================================================================
// CSVTokenizer
// =================================================================

// =================================================================
// Method
// =================================================================
CSVTokenizer::CSVTokenizer(const std::string& str)
{
  std::string strbuf = std::string();
  const char* p = str.c_str();
  while(*p != '\0' || *p == '\n')
  {
    if (*p == ',')
    {
      this->tokens_.push_back(CSVToken::Create(strbuf));
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
    this->tokens_.push_back(CSVToken::Create(strbuf));
  }
  this->now_token_index_ = 0;
}

CSVTokenizer::CSVTokenizer(const CSVTokenizer& other)
  : tokens_(other.tokens_)
  , now_token_index_(0)
{
}

CSVTokenizer::~CSVTokenizer()
{
}

void CSVTokenizer::Reset()
{
  this->now_token_index_ = 0;
}

bool CSVTokenizer::HasNextToken()
{
  return this->now_token_index_ < this->tokens_.size();
}

const CSVToken& CSVTokenizer::NextToken()
{
  const CSVToken& ret = this->tokens_[this->now_token_index_];
  ++this->now_token_index_;
  return ret;
}
