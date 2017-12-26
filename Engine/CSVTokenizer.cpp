#include "CSVTokenizer.h"
#include <stdlib.h>
#include <string.h>

// =================================================================
// CSVToken
// =================================================================

// =================================================================
// Constructor / Destructor
// =================================================================
CSVToken::CSVToken(T_UINT32 line_index, T_UINT16 token_index, const char* str, T_UINT8 len)
  : line_index_(line_index)
  , token_index_(token_index)
  , exception_(NULL)
{
  const T_UINT8 strlen = len + 1;
  this->str_ = new char[strlen];
  for (T_UINT8 i = 0; i < len; ++i)
  {
    this->str_[i] = str[i];
  }
  this->str_[len] = '\0';

  if (this->str_[0] == '\"')
  {
    this->trimed_str_ = new char[strlen - 2];
    strncpy_s(this->trimed_str_, sizeof(char) * (strlen - 2), this->str_ + 1, strlen - 2);
  }
  else
  {
    this->trimed_str_ = new char[strlen];
    strncpy_s(this->trimed_str_, sizeof(char) * strlen, this->str_, strlen);
  }
}

CSVToken::~CSVToken()
{
  delete[] this->str_;
  delete[] this->trimed_str_;
}

// =================================================================
// Method
// =================================================================
void CSVToken::ThrowException(const char* message)
{
  if (!this->exception_)
  {
    return;
  }
  this->exception_(this, message);
}

// =================================================================
// Setter / Getter
// =================================================================
T_INT32 CSVToken::GetInt32()
{
  size_t len = strlen(this->str_);
  if (len == 0)
  {
    this->ThrowException("int32Œ^‚É‹ó‚Ì•¶Žš—ñ‚ª“n‚³‚ê‚Ü‚µ‚½");
    return 0;
  }
  char* e;
  T_INT32 ret = strtol(this->str_, &e, 0);
  if ((*e) != '\0')
  {
    this->ThrowException("ƒg[ƒNƒ“‚ðint32Œ^‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ");
    return 0;
  }
  return ret;
}

T_INT64 CSVToken::GetInt64()
{
  size_t len = strlen(this->str_);
  if (len == 0)
  {
    this->ThrowException("int64Œ^‚É‹ó‚Ì•¶Žš—ñ‚ª“n‚³‚ê‚Ü‚µ‚½");
    return 0;
  }
  char* e;
  T_INT64 ret = strtol(this->str_, &e, 0);
  if ((*e) != '\0')
  {
    this->ThrowException("ƒg[ƒNƒ“‚ðint64Œ^‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ");
    return 0;
  }
  return ret;
}

T_FLOAT CSVToken::GetFloat()
{
  size_t len = strlen(this->str_);
  if (len == 0)
  {
    this->ThrowException("floatŒ^‚É‹ó‚Ì•¶Žš—ñ‚ª“n‚³‚ê‚Ü‚µ‚½");
    return 0.0f;
  }
  char* e;
  T_FLOAT ret = strtof(this->str_, &e);
  if ((*e) != '\0')
  {
    this->ThrowException("ƒg[ƒNƒ“‚ðfloatŒ^‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ");
    return 0.0f;
  }
  return ret;
}

T_DOUBLE CSVToken::GetDouble()
{
  size_t len = strlen(this->str_);
  if (len == 0)
  {
    this->ThrowException("doubleŒ^‚É‹ó‚Ì•¶Žš—ñ‚ª“n‚³‚ê‚Ü‚µ‚½");
    return 0.0;
  }
  char* e;
  T_DOUBLE ret = strtod(this->str_, &e);
  if ((*e) != '\0')
  {
    this->ThrowException("ƒg[ƒNƒ“‚ðdoubleŒ^‚É•ÏŠ·‚Å‚«‚Ü‚¹‚ñ");
    return 0.0;
  }
  return ret;
}

const char* CSVToken::GetString()
{
  return this->trimed_str_;
}

void CSVToken::SetException(void(*exception)(CSVToken*, const char *message))
{
  this->exception_ = exception;
}

// =================================================================
// CSVTokenizer
// =================================================================

// =================================================================
// Method
// =================================================================
void CSVTokenizer::Prepare(T_UINT32 line_index, const char* txt)
{
  T_UINT8 cnt = 0;
  T_UINT8 len = 0;
  char strbuf[256] = {};
  do
  {
    if (txt[cnt] == ',' || txt[cnt] == '\0' || txt[cnt] == '\n')
    {
      CSVToken* token = new CSVToken(line_index, (T_UINT16)this->tokens_.size(), strbuf, len);
      token->SetException(this->exception_);
      this->tokens_.push_back(token);
      len = 0;
    }
    else
    {
      strbuf[len] = txt[cnt];
      ++len;
    }
    ++cnt;
  } while (txt[cnt-1] != '\0' && txt[cnt-1] != '\n');
  this->now_token_index_ = 0;
}

bool CSVTokenizer::HasNextToken()
{
  return this->now_token_index_ < this->tokens_.size();
}

CSVToken* CSVTokenizer::NextToken()
{
  CSVToken* ret = this->tokens_[this->now_token_index_];
  ++this->now_token_index_;
  return ret;
}
