#define _CRT_SECURE_NO_WARNINGS
#include "EngineOption.h"

void AssetPath::GetTexturePath(const char* path, char* dest) const
{
  if (strlen(this->root) > 0)
  {
    strcat(dest, this->root);
  }
  
  if (strlen(this->texture) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, this->texture);
  }

  if (strlen(path) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, path);
  }
}

void AssetPath::GetParticlePath(const char* path, char* dest) const
{
  if (strlen(this->root) > 0)
  {
    strcat(dest, this->root);
  }

  if (strlen(this->particle) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, this->particle);
  }

  if (strlen(path) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, path);
  }
}

void AssetPath::GetSpinePath(const char* path, char* dest) const
{
  if (strlen(this->root) > 0)
  {
    strcat(dest, this->root);
  }

  if (strlen(this->spine) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, this->spine);
  }

  if (strlen(path) > 0)
  {
    if (strlen(dest) > 0)
    {
      strcat(dest, "/");
    }
    strcat(dest, path);
  }
}
