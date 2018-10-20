#include <stdio.h>

#include "LoggerBuilder.h"

int main()
{
  LoggerBuilder b;

  //https://qiita.com/nanasess/items/350e59b29cceb2f122b3
  b.Add("Fatal", DoLevel::ON_ANYTIME, true);
  b.Add("Error", DoLevel::ON_ANYTIME, true);
  b.Add("Warn",  DoLevel::ON_ANYTIME, false);
  b.Add("Info",  DoLevel::ON_ANYTIME, false);
  b.Add("Debug", DoLevel::ON_DEBUG, false);
  b.Add("Trace", DoLevel::ON_DEBUG, false);

  b.CreateHeader();

  getchar();
}