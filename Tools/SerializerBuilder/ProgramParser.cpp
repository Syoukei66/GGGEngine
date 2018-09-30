#include "ProgramParser.h"
#include "Parser.h"

#include "TypeParser.h"

// =================================================================
// Methods
// =================================================================
bool ProgramParser::Eat(const std::string& token, ParserContext* context)
{
  if (token == "class" || token == "struct")
  {
    context->PushParser(new TypeParser());
    return true;
  }
  return false;
}
