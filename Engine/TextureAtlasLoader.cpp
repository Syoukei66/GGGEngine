#define _CRT_SECURE_NO_WARNINGS
#include "TextureAtlasLoader.h"
#include <string>
#include <string.h>
#include "NativeMethod.h"
#include "Director.h"
#include "Moniker.h"

static bool IsSpace(char c)
{
  return c == ' ' || c == '\t';
}

static bool IsEnter(char c)
{
  return c == '\n';
}

static bool IsComma(char c)
{
  return c == ',';
}

static bool IsDataSeparator(char c)
{
  return c == ':';
}

static bool EndOfFile(char c)
{
  return c == '\0';
}

TextureAtlas* TextureAtlasLoader::Load(const char* directory_path, const char* atlas_file_name)
{
  std::string atlas_file_path = std::string();
  if (strlen(directory_path) > 0)
  {
    atlas_file_path.append(directory_path);
    atlas_file_path.append("/");
  }
  atlas_file_path.append(atlas_file_name);

  std::string str = NativeMethod::IO().TextFile_Read(atlas_file_path.c_str());
  T_UINT32 length = (T_UINT32)str.length();
  char* p_head = new char[str.size() + 1];
  char* p = p_head;
  strcpy(p, str.c_str());
  std::string texture_file_name = this->TexturePath(&p);
  TSize texture_size = this->TextureSize(&p);
  std::string texture_format = this->TextureFormat(&p);
  std::string texture_filter = this->TextureFilter(&p);
  std::string texture_repeat = this->TextureRepeat(&p);

  std::string texture_path = std::string();
  if (strlen(directory_path) > 0)
  {
    texture_path.append(directory_path);
    texture_path.append("/");
  }
  texture_path.append(texture_file_name);

  TextureResource* texture = new TextureResource(texture_path.c_str());
  texture->Load();
  TextureAtlas* ret = new TextureAtlas(texture->GetContents());
  while (!EndOfFile(*p))
  {
    if (IsSpace(*p) || IsEnter(*p))
    {
      ++p;
      continue;
    }
    AtlasRegion region = AtlasRegion();
    std::string key = this->GetText(&p);
    std::string rotate = this->GetDataText(&p);
    std::string xy = this->GetDataText(&p);
    std::string size = this->GetDataText(&p);
    std::string orig = this->GetDataText(&p);
    std::string offset = this->GetDataText(&p);
    std::string index = this->GetDataText(&p);
    region.area.pos = this->StrToTVec2(xy);
    region.area.size = this->StrToTSize(size);
    ret->Register(key, region);
  }
  delete[] p_head;
  return ret;
}

const std::string TextureAtlasLoader::GetText(char ** p)
{
  std::string ret;
  ret.clear();
  while (!IsEnter(**p))
  {
    if (IsSpace(**p))
    {
      ++(*p);
      continue;
    }
    ret.append(*p, 1);
    ++(*p);
  }
  ++(*p);
  return ret;
}

const std::string TextureAtlasLoader::GetDataText(char ** p)
{
  std::string ret;
  ret.clear();
  bool declarated = false;
  while (!IsEnter(**p))
  {
    if (IsSpace(**p))
    {
      ++(*p);
      continue;
    }
    if (IsDataSeparator(**p))
    {
      declarated = true;
      ++(*p);
      continue;
    }
    if (declarated)
    {
      ret.append(*p, 1);
    }
    ++(*p);
  }
  ret.append(*p, 1);
  ++(*p);
  return ret;
}

const std::string TextureAtlasLoader::TexturePath(char** p)
{
  return this->GetText(p);
}

const TSize TextureAtlasLoader::TextureSize(char** p)
{
  std::string data_text = this->GetDataText(p);
  return this->StrToTSize(data_text);
}

const std::string TextureAtlasLoader::TextureFormat(char** p)
{
  std::string data_text = this->GetDataText(p);
  return data_text;
}

const std::string TextureAtlasLoader::TextureFilter(char** p)
{
  std::string data_text = this->GetDataText(p);
  return data_text;
}

const std::string TextureAtlasLoader::TextureRepeat(char** p)
{
  std::string data_text = this->GetDataText(p);
  return data_text;
}

const TSize TextureAtlasLoader::StrToTSize(const std::string& str)
{
  TSize ret = TSize();
  std::string buf;
  buf.clear();
  char* p_head = new char[str.size() + 1];
  char* p = p_head;
  strcpy(p, str.c_str());
  while (!IsEnter(*p))
  {
    if (IsSpace(*p))
    {
      ++p;
      continue;
    }
    if (IsComma(*p))
    {
      ++p;
      ret.width = std::stoi(buf);
      buf.clear();
      continue;
    }
    buf.append(p, 1);
    ++p;
  }
  ret.height = std::stoi(buf);
  delete[] p_head;
  return ret;
}

const TVec2 TextureAtlasLoader::StrToTVec2(const std::string& str)
{
  TVec2 ret = TVec2();
  std::string buf;
  buf.clear();
  char* p_head = new char[str.size() + 1];
  char* p = p_head;
  strcpy(p, str.c_str());
  while (!IsEnter(*p))
  {
    if (IsSpace(*p))
    {
      ++p;
      continue;
    }
    if (IsComma(*p))
    {
      ++p;
      ret.x = std::stoi(buf);
      buf.clear();
      continue;
    }
    buf.append(p, 1);
    ++p;
  }
  ret.y = std::stoi(buf);
  delete[] p_head;
  return ret;
}
