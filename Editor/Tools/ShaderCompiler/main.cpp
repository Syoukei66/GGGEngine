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
    Log::Info(ShaderTest::ToString(data).c_str());
  }
  catch (ParseException e)
  {
    Log::Info(e.message.c_str());
  }
  printf("\nI—¹‚·‚é‚É‚Í‰½‚©ƒL[‚ğ‰Ÿ‚µ‚Ä‚­‚¾‚³‚¢");
  getchar();
  return 0;
}
