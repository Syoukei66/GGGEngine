#include "ShaderParser.h"

ShaderParser::ShaderParser(const std::string& str)
  : str_(str)
{
  this->p_ = str.c_str();
}

TokenType ShaderParser::GetTokenType()
{
  return this->lexer_.GetTokenType(*this->p_);
}

void ShaderParser::SkipSpace()
{
  TokenType separator;
  while ((separator = this->GetTokenType()) == TokenType::kSpace)
  {
    ++this->p_;
  }
}

TokenType ShaderParser::CheckNextToken(bool skip_space)
{
  if (skip_space)
  {
    this->SkipSpace();
  }
  return this->GetTokenType();
}

bool ShaderParser::GetToken(TokenType type, bool skip_space)
{
  if (skip_space)
  {
    this->SkipSpace();
  }
  if (this->GetTokenType() == type)
  {
    ++this->p_;
    return true;
  }
  return false;
}

bool ShaderParser::EatToken(bool skip_space)
{
  if (skip_space)
  {
    this->SkipSpace();
  }
  if (this->GetTokenType() == TokenType::kEOF)
  {
    return false;
  }
  ++this->p_;
  return true;
}

bool ShaderParser::ParseText(std::string* dest)
{
  (*dest).clear();
  if (!this->GetToken(TokenType::kTextParen))
  {
    return false;
  }
  while (this->CheckNextToken(false) != TokenType::kTextParen)
  {
    (*dest) += *this->p_;
    this->EatToken(false);
  }
  this->EatToken();
  return true;
}

bool ShaderParser::ParseIdentifier(std::string * dest)
{
  (*dest).clear();
  TokenType next_token = this->CheckNextToken();
  if (next_token != TokenType::kAlphabet && next_token != TokenType::kUnderBar)
  {
    return false;
  }
  do
  {
    (*dest) += *this->p_;
    this->EatToken(false);
    next_token = this->CheckNextToken(false);
  } while (next_token == TokenType::kAlphabet || next_token == TokenType::kUnderBar || next_token == TokenType::kNumber);
  return true;
}

bool ShaderParser::ParseSpecialIdentifier(std::string * dest)
{
  (*dest).clear();
  TokenType next_token = this->CheckNextToken();
  if (next_token != TokenType::kAlphabet && next_token != TokenType::kUnderBar && next_token != TokenType::kNumber)
  {
    return false;
  }
  do
  {
    (*dest) += *this->p_;
    this->EatToken();
    next_token = this->CheckNextToken();
  } while (next_token == TokenType::kAlphabet || next_token == TokenType::kUnderBar || next_token == TokenType::kNumber);
  return true;
}

bool ShaderParser::ParseInt(T_FLOAT * dest)
{
  bool minus = false;
  TokenType next_token = this->CheckNextToken();
  // •„†•”•ª‚Ìˆ—
  if (next_token == TokenType::kPlus)
  {
    this->EatToken();
    next_token = this->CheckNextToken();
  }
  else if (next_token == TokenType::kMinus)
  {
    minus = true;
    this->EatToken();
    next_token = this->CheckNextToken();
  }

  std::string str = minus ? "-" : "";
  if (next_token != TokenType::kNumber)
  {
    return false;
  }
  do
  {
    str += *this->p_;
    this->EatToken();
  } while ((next_token = this->CheckNextToken(false)) == TokenType::kNumber);
  (*dest) = (T_FLOAT)std::strtol(str.c_str(), NULL, 10);
  return true;
}

bool ShaderParser::ParseFloat(T_FLOAT * dest)
{
  bool minus = false;
  TokenType next_token = this->CheckNextToken();
  // •„†•”•ª‚Ìˆ—
  if (next_token == TokenType::kPlus)
  {
    this->EatToken();
    next_token = this->CheckNextToken();
  }
  else if (next_token == TokenType::kMinus)
  {
    minus = true;
    this->EatToken();
    next_token = this->CheckNextToken();
  }
  std::string sign = minus ? "-" : "";
  // ®”•”‚Ìˆ—
  std::string integer = "";
  if (next_token == TokenType::kNumber)
  {
    do
    {
      integer += *this->p_;
      this->EatToken();
      next_token = this->CheckNextToken();
    } while (next_token == TokenType::kNumber);
  }
  // ¬”•”‚Ìˆ—
  std::string fractional = "";
  if (next_token == TokenType::kDot)
  {
    this->EatToken();
    next_token = this->CheckNextToken();
    if (next_token == TokenType::kNumber)
    {
      do
      {
        fractional += *this->p_;
        this->EatToken();
        next_token = this->CheckNextToken();
      } while (next_token == TokenType::kNumber);
    }
  }
  (*dest) = std::strtof((sign + integer + "." + fractional).c_str(), NULL);
  return true;
}

bool ShaderParser::GetText(const std::string& end_simbol, std::string* dest)
{
  while ((*dest).find(end_simbol) == std::string::npos)
  {
    (*dest) += *this->p_;
    ++this->p_;
  }
  (*dest).replace((*dest).length() - end_simbol.length(), end_simbol.length(), "");
  return true;
}
