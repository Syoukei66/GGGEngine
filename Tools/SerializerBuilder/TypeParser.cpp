#include "TypeParser.h"
#include "Attributes.h"

// =================================================================
// Methods
// =================================================================
bool TypeParser::Eat(const std::string& token, ParserContext* context)
{
  //�ŏ��̃g�[�N���͖��O
  if (this->name_.size() == 0)
  {
    this->name_ = token;
    return true;
  }

  if (token == ATTR_SERIALIZABLE)
  {

  }

  return false;
}
