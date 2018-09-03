#pragma once

#include <iostream>
#include <fstream>

#include "Cereal/cereal.hpp"
#include "Cereal/archives/json.hpp"
#include "Cereal/archives/binary.hpp"

namespace CerealIO
{

namespace Json
{

template <typename T>
T* Import(const char* path)
{
  using namespace std;
  ifstream ifs(path, ios::in);
  if (!ifs.is_open())
  {
    return nullptr;
  }
  ::cereal::JSONInputArchive i_archive(ifs);
  T* ret = new T();
  i_archive(cereal::make_nvp("root", *ret));
  return ret;
}

template <typename T>
T* SafeImport(const char* path)
{
  using namespace std;
  ifstream ifs(path, ios::in);
  if (!ifs.is_open())
  {
    return nullptr;
  }
  ::cereal::JSONInputArchive i_archive(ifs);
  T* ret = new T();
  try
  {
    i_archive(cereal::make_nvp("root", *ret));
    return ret;
  }
  catch (cereal::Exception e)
  {
    delete ret;
  }
  return nullptr;
}

template <typename T>
void Export(const char* path, const T* data)
{
  using namespace std;
  ofstream ofs(path, ios::out | ios::trunc);
  ::cereal::JSONOutputArchive o_archive(ofs);
  o_archive(cereal::make_nvp("root", *data));
}

template <typename T>
bool SafeExport(const char* path, const T* data)
{
  using namespace std;
  ofstream ofs(path, ios::out | ios::trunc);
  ::cereal::JSONOutputArchive o_archive(ofs);
  try
  {
    o_archive(cereal::make_nvp("root", *data));
    return true;
  }
  catch (cereal::Exception e)
  {
  }
  return false;
}

} // namespace Json

namespace Binary
{

template <typename T>
T* Import(const char* path)
{
  using namespace std;
  ifstream ifs(path, ios::in | ios::binary);
  if (!ifs.is_open())
  {
    return nullptr;
  }
  ::cereal::BinaryInputArchive i_archive(ifs);
  T* ret = new T();
  i_archive(*ret);
  return ret;
}

template <typename T>
T* SafeImport(const char* path)
{
  using namespace std;
  ifstream ifs(path, ios::in | ios::binary);
  if (!ifs.is_open())
  {
    return nullptr;
  }
  ::cereal::BinaryInputArchive i_archive(ifs);
  T* ret = new T();
  try
  {
    i_archive(*ret);
    return ret;
  }
  catch (cereal::Exception e)
  {
    delete ret;
  }
  return nullptr;
}

template <typename T>
void Export(const char* path, const T* data)
{
  using namespace std;
  ofstream ofs(path, ios::out | ios::binary | ios::trunc);
  ::cereal::BinaryOutputArchive o_archive(ofs);
  o_archive(*data);
}

template <typename T>
bool SafeExport(const char* path, const T* data)
{
  using namespace std;
  ofstream ofs(path, ios::out | ios::binary | ios::trunc);
  ::cereal::BinaryOutputArchive o_archive(ofs);
  try
  {
    o_archive(*data);
    return true;
  }
  catch (cereal::Exception e)
  {
  }
  return false;
}

} // namespace Binary

} // namespace Cereal