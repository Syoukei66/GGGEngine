#pragma once

//マクロがあるのでヘッダー側でインクルードを行わないこと
//他のArchiveファイルにも言える

#define SAFE_NEW(var, value) if (!var)\
{\
  var = new value();\
}

#define ARRAY_ARCHIVE(var, value, size) SAFE_NEW(var, value[size])\
archive(cereal::binary_data(var, sizeof(value) * (size)));

#define SEREALIZERS(type) type* type##::Deserialize(const std::string & path)\
{\
  return CerealIO::Binary::Import<type>(path.c_str());\
}\
\
void type##::Serialize(const std::string& path, bool test)\
{\
  CerealIO::Binary::Export<type>(path.c_str(), this);\
  if (test)\
  {\
    type##SerializerTester tester;\
    type* data = Deserialize(path);\
    tester.Compare(*this, *data);\
    delete data;\
  }\
}
