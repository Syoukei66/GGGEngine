#pragma once

//マクロがあるのでヘッダー側でインクルードを行わないこと
//他のArchiveファイルにも言える

#define SAFE_NEW(var, value) if (!var)\
{\
  var = new value();\
}
