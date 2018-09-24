#pragma once

//マクロがあるのでヘッダー側でインクルードを行わないこと
//他のArchiveファイルにも言える

#define SAFE_NEW(var, value) if (!var)\
{\
  var = new value();\
}

#define ARRAY_ARCHIVE(var, value, size) SAFE_NEW(var, value[size])\
archive(cereal::binary_data(var, sizeof(value) * (size)));

#define SEREALIZERS(type) type* type##::Deserealize(const std::string & path)\
{\
  return CerealIO::Binary::Import<type>(path.c_str());\
}\
\
void type##::Serealize(const std::string& path, bool test)\
{\
  CerealIO::Binary::Export<type>(path.c_str(), this);\
  if (test)\
  {\
    type##SerealizerTester tester;\
    type* data = Deserealize(path);\
    tester.Compare(*this, *data);\
    delete data;\
  }\
}
