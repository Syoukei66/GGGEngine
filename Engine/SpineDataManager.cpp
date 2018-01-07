#define _CRT_SECURE_NO_WARNINGS
#include "SpineDataManager.h"
#include <string.h>
#include "Director.h"

SpineDataManager::SpineDataManager()
  : is_already_loaded_(false)
  , size_(0)
  , paths_(nullptr)
  , datas_(nullptr)
{}

SpineDataManager::~SpineDataManager()
{}

void SpineDataManager::Init(T_UINT8 size)
{
  this->is_already_loaded_ = false;
  this->size_ = size;
  this->paths_ = new char*[size]();
  this->datas_ = new SpineData*[size]();
  for (T_UINT8 i = 0; i < size; ++i)
  {
    this->paths_[i] = nullptr;
    this->datas_[i] = nullptr;
  }
}

void SpineDataManager::Register(T_UINT8 id, const char* path)
{
  this->paths_[id] = new char[strlen(path) + 1]();
  strcpy(this->paths_[id], path);
}

void SpineDataManager::Uninit()
{
  for (T_UINT8 i = 0; i < this->size_; ++i)
  {
    if (this->datas_[i])
    {
      delete this->datas_[i];
    }
    if (this->paths_[i])
    {
      delete[] this->paths_[i];
    }
  }
  delete[] this->datas_;
  delete[] this->paths_;
  this->size_ = 0;
  this->datas_ = nullptr;
  this->paths_ = nullptr;
}

void SpineDataManager::Load()
{
  if (this->is_already_loaded_)
  {
    return;
  }
  this->is_already_loaded_ = true;

  for (T_UINT8 i = 0; i < this->size_; ++i)
  {
    this->datas_[i] = SpineData::CreateFromFile(this->paths_[i]);
  }
}

void SpineDataManager::Unload()
{
  if (!this->is_already_loaded_)
  {
    return;
  }
  for (T_UINT8 i = 0; i < this->size_; ++i)
  {
    delete this->datas_[i];
    this->datas_[i] = nullptr;
  }
  this->is_already_loaded_ = false;
}
