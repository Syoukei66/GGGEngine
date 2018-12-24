#include "ShaderLexer.h"

TokenType ShaderLexer::GetTokenType(const char c)
{
  if (c == '\0')
  {
    return TokenType::kEOF;
  }
  if (c == ' ' || c == '\t')
  {
    return TokenType::kSpace;
  }
  if (c == '\n')
  {
    return TokenType::kEnter;
  }
  if (c == '{')
  {
    return TokenType::kBlockBegin;
  }
  if (c == '}')
  {
    return TokenType::kBlockEnd;
  }
  if (c == '(')
  {
    return TokenType::kParenBegin;
  }
  if (c == ')')
  {
    return TokenType::kParenEnd;
  }
  if (c == '\"')
  {
    return TokenType::kTextParen;
  }
  if (c == ',')
  {
    return TokenType::kComma;
  }
  if (c == '=')
  {
    return TokenType::kEqual;
  }
  if (c == '_')
  {
    return TokenType::kUnderBar;
  }
  if (c == '.')
  {
    return TokenType::kDot;
  }
  if (c == '+')
  {
    return TokenType::kPlus;
  }
  if (c == '-')
  {
    return TokenType::kMinus;
  }
  if ('0' <= c && c <= '9')
  {
    return TokenType::kNumber;
  }
  if (
    ('a' <= c && c <= 'z') ||
    ('A' <= c && c <= 'Z')
    )
  {
    return TokenType::kAlphabet;
  }
  return TokenType::kNoExcepted;
}
