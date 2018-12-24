#include <stdio.h>

#include "Parser/ShaderCompiler.h"
#include "ShaderTest.h"

int main()
{
  std::string str = FileUtil::TextFile_Read("Test.shader");
  ShaderData data = ShaderData();
  try
  {
    ShaderCompiler(str, "").Compile(&data);
    printf(ShaderTest::ToString(data).c_str());
  }
  catch (ParseException e)
  {
    printf(e.message.c_str());
  }
  printf("\nI—¹‚·‚é‚É‚Í‰½‚©ƒL[‚ğ‰Ÿ‚µ‚Ä‚­‚¾‚³‚¢");
  getchar();
  return 0;
}
