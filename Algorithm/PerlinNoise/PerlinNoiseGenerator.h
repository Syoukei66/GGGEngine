#pragma once

class PerlinNoiseGenerator
{
public:
  struct NoiseSetting
  {
    T_UINT32 seed_;
    T_UINT32 octaves_;
    T_FLOAT lacunarity_;
    T_FLOAT persistence_;
    T_FLOAT frequency_;
  };

  // =================================================================
  // Methods
  // =================================================================
public:
  void Init(const NoiseSetting& setting);
  T_FLOAT Noise1D(T_FLOAT x) const;
  T_FLOAT Noise2D(T_FLOAT x, T_FLOAT y) const;
  T_FLOAT Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z) const;
  GG_INLINE T_FLOAT Noise1D(T_FLOAT x, T_FLOAT frequency) const
  {
    return Noise1D(x * frequency);
  }
  GG_INLINE T_FLOAT Noise2D(T_FLOAT x, T_FLOAT y, T_FLOAT frequency) const
  {
    return Noise2D(x * frequency, y * frequency);
  }
  GG_INLINE T_FLOAT Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT frequency) const
  {
    return Noise3D(x * frequency, y * frequency, z * frequency);
  }
  T_FLOAT FractalNoise1D(T_FLOAT x) const;
  T_FLOAT FractalNoise2D(T_FLOAT x, T_FLOAT y) const;
  T_FLOAT FractalNoise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z) const;

  // =================================================================
  // Data Member
  // =================================================================
private:
  NoiseSetting setting_;
};