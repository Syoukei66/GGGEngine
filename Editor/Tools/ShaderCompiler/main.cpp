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
  printf("\n�I������ɂ͉����L�[�������Ă�������");
  getchar();
  return 0;
}
