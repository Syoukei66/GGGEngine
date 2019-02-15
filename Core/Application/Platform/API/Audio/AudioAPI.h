#pragma once

#include <Core/Application/Platform/API/APIObject.h>

#include <Core/Application/Platform/API/_Asset/AudioClip/AudioClip.h>

class AudioAPI : public GGAPIObject
{
public:
  virtual UniqueRef<rcAudioClip> LoadSound(const char* path) = 0;

};