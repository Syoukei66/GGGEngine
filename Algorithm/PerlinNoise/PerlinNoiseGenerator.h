#pragma once

#include "NativeType.h"

class PerlinNoiseGenerator
{
public:
  PerlinNoiseGenerator();
  ~PerlinNoiseGenerator();

public:
  void Init(T_UINT32 seed);
  T_FLOAT Noise1D(T_FLOAT x);
  T_FLOAT Noise2D(T_FLOAT x, T_FLOAT y);
  T_FLOAT Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z);
  T_FLOAT Noise1D(T_FLOAT x, T_FLOAT frequency);
  T_FLOAT Noise2D(T_FLOAT x, T_FLOAT y, T_FLOAT frequency);
  T_FLOAT Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT frequency);
  T_FLOAT FractalNoise1D(T_FLOAT x);
  T_FLOAT FractalNoise2D(T_FLOAT x, T_FLOAT y);
  T_FLOAT FractalNoise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z);

public:
  GG_INLINE T_UINT32 GetOctaves() const
  {
    return this->octaves_;
  }
  GG_INLINE void SetOctaves(T_UINT32 octaves)
  {
    this->octaves_ = octaves;
  }

  GG_INLINE T_FLOAT GetLacunarity() const
  {
    return this->lacunarity_;
  }
  GG_INLINE void SetLacunarity(T_FLOAT lacunarity)
  {
    this->lacunarity_ = lacunarity;
  }

  GG_INLINE T_FLOAT GetPersistence() const
  {
    return this->persistence_;
  }
  GG_INLINE void SetPersistence(T_FLOAT persistence)
  {
    this->persistence_ = persistence;
  }

  GG_INLINE T_UINT32 GetResolution() const
  {
    return this->resolution_;
  }
  GG_INLINE void SetResolution(T_UINT32 resolution)
  {
    this->resolution_ = resolution;
  }

  GG_INLINE T_FLOAT GetFrequency() const
  {
    return this->frequency_;
  }
  GG_INLINE void SetFrequency(T_FLOAT frequency)
  {
    this->frequency_ = frequency;
  }

private:
  T_UINT32 seed_;
  T_UINT32 octaves_;
  T_FLOAT lacunarity_;
  T_FLOAT persistence_;
  T_UINT32 resolution_;
  T_FLOAT frequency_;

};