#include "PerlinNoiseGenerator.h"
#include "Vector2.h"

PerlinNoiseGenerator::PerlinNoiseGenerator()
  : seed_(123456789)
{
}

PerlinNoiseGenerator::~PerlinNoiseGenerator()
{
}

void PerlinNoiseGenerator::Init(T_UINT32 seed)
{
  this->seed_ = seed;
}

T_FLOAT PerlinNoiseGenerator::Noise1D(T_FLOAT x)
{
  return Noise1D(x, this->frequency_);
}

T_FLOAT PerlinNoiseGenerator::Noise2D(T_FLOAT x, T_FLOAT y)
{
  return Noise2D(x, y, this->frequency_);
}

T_FLOAT PerlinNoiseGenerator::Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  return Noise3D(x, y, z, this->frequency_);
}

static T_UINT32 XorShift32(T_UINT32 v)
{
  v = v ^ (v << 13);
  v = v ^ (v >> 17);
  v = v ^ (v << 15);
  return v;
}

static T_UINT8 hash[512] = {
  151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
  140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
  247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
  57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
  74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
  60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
  65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
  200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
  52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
  207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
  119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
  129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
  218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
  81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
  184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
  222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180,

  151,160,137, 91, 90, 15,131, 13,201, 95, 96, 53,194,233,  7,225,
  140, 36,103, 30, 69,142,  8, 99, 37,240, 21, 10, 23,190,  6,148,
  247,120,234, 75,  0, 26,197, 62, 94,252,219,203,117, 35, 11, 32,
  57,177, 33, 88,237,149, 56, 87,174, 20,125,136,171,168, 68,175,
  74,165, 71,134,139, 48, 27,166, 77,146,158,231, 83,111,229,122,
  60,211,133,230,220,105, 92, 41, 55, 46,245, 40,244,102,143, 54,
  65, 25, 63,161,  1,216, 80, 73,209, 76,132,187,208, 89, 18,169,
  200,196,135,130,116,188,159, 86,164,100,109,198,173,186,  3, 64,
  52,217,226,250,124,123,  5,202, 38,147,118,126,255, 82, 85,212,
  207,206, 59,227, 47, 16, 58, 17,182,189, 28, 42,223,183,170,213,
  119,248,152,  2, 44,154,163, 70,221,153,101,155,167, 43,172,  9,
  129, 22, 39,253, 19, 98,108,110, 79,113,224,232,178,185,112,104,
  218,246, 97,228,251, 34,242,193,238,210,144, 12,191,179,162,241,
  81, 51,145,235,249, 14,239,107, 49,192,214, 31,181,199,106,157,
  184, 84,204,176,115,121, 50, 45,127,  4,150,254,138,236,205, 93,
  222,114, 67, 29, 24, 72,243,141,128,195, 78, 66,215, 61,156,180
};

static const T_UINT8 hashMask = 255;

static T_FLOAT Lerp(T_FLOAT a, T_FLOAT b, T_FLOAT t)
{
  return a + (b - a) * t;
}

static T_FLOAT Smooth(T_FLOAT t)
{
  return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

static T_FLOAT gradients1D[] = {
  1.0f, -1.0f
};
static const int gradientsMask1D = 1;

static TVec2f gradients2D[] = {
  {  1.0f,  0.0f },
  { -1.0f,  1.0f },
  {  0.0f,  1.0f },
  {  0.0f, -1.0f },
  TVec2f( 1.0f,  1.0f).Normalized(),
  TVec2f(-1.0f,  1.0f).Normalized(),
  TVec2f( 1.0f, -1.0f).Normalized(),
  TVec2f(-1.0f, -1.0f).Normalized(),
};

static const int gradientsMask2D = 7;

static T_FLOAT Dot(const TVec2f& g, T_FLOAT x, T_FLOAT y)
{
  return g.x * x + g.y * y;
}

T_FLOAT PerlinNoiseGenerator::Noise1D(T_FLOAT x, T_FLOAT frequency)
{
  const T_INT32 v = XorShift32(this->seed_);
  x *= frequency;
  T_INT32 i0 = (T_INT32)floorf(x);
  const T_FLOAT t0 = x - i0;
  const T_FLOAT t1 = t0 - 1.0f;
  i0 = (i0 + v) & hashMask;
  const T_INT32 i1 = i0 + 1;

  const T_FLOAT g0 = gradients1D[hash[i0] & gradientsMask1D];
  const T_FLOAT g1 = gradients1D[hash[i1] & gradientsMask1D];

  const T_FLOAT v0 = g0 * t0;
  const T_FLOAT v1 = g1 * t1;

  const T_FLOAT t = Smooth(t0);

  return Lerp(t0, v1, t) * 2.0f;
}

T_FLOAT PerlinNoiseGenerator::Noise2D(T_FLOAT x, T_FLOAT y, T_FLOAT frequency)
{
  const T_INT32 v = XorShift32(this->seed_);

  x *= frequency;
  T_INT32 ix0 = (T_INT32)floorf(x);
  const T_FLOAT tx0 = x - ix0;
  const T_FLOAT tx1 = tx0 - 1.0f;
  ix0 = (ix0 + v) & hashMask;
  const T_INT32 ix1 = ix0 + 1;

  y *= frequency;
  T_INT32 iy0 = (T_INT32)floorf(y);
  const T_FLOAT ty0 = y - iy0;
  const T_FLOAT ty1 = ty0 - 1.0f;
  iy0 = (iy0 + v) & hashMask;
  const T_INT32 iy1 = iy0 + 1;

  const T_INT32 h0 = hash[ix0];
  const T_INT32 h1 = hash[ix1];
  const TVec2f g00 = gradients2D[hash[h0 + iy0] & gradientsMask2D];
  const TVec2f g10 = gradients2D[hash[h1 + iy0] & gradientsMask2D];
  const TVec2f g01 = gradients2D[hash[h0 + iy1] & gradientsMask2D];
  const TVec2f g11 = gradients2D[hash[h1 + iy1] & gradientsMask2D];

  const T_FLOAT v00 = Dot(g00, tx0, ty0);
  const T_FLOAT v10 = Dot(g10, tx1, ty0);
  const T_FLOAT v01 = Dot(g01, tx0, ty1);
  const T_FLOAT v11 = Dot(g11, tx1, ty1);

  const T_FLOAT tx = Smooth(tx0);
  const T_FLOAT ty = Smooth(ty0);

  return Lerp(
    Lerp(v00, v10, tx),
    Lerp(v01, v11, tx),
    ty) * sqrtf(2.0f);
}

T_FLOAT PerlinNoiseGenerator::Noise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z, T_FLOAT frequency)
{
  return T_FLOAT();
}

T_FLOAT PerlinNoiseGenerator::FractalNoise1D(T_FLOAT x)
{
  T_FLOAT sum = Noise1D(x);
  T_FLOAT frequency = this->frequency_;
  T_FLOAT amplitude = 1.0f;
  T_FLOAT range = 1.0f;
  for (T_UINT32 o = 1; o < this->octaves_; o++)
  {
    frequency *= this->lacunarity_;
    amplitude *= this->persistence_;
    range += amplitude;
    sum += Noise1D(x, frequency) * amplitude;
  }
  return sum * (1.0f / range);
}

T_FLOAT PerlinNoiseGenerator::FractalNoise2D(T_FLOAT x, T_FLOAT y)
{
  T_FLOAT sum = Noise2D(x, y);
  T_FLOAT frequency = this->frequency_;
  T_FLOAT amplitude = 1.0f;
  T_FLOAT range = 1.0f;
  for (T_UINT32 o = 1; o < this->octaves_; o++)
  {
    frequency *= this->lacunarity_;
    amplitude *= this->persistence_;
    range += amplitude;
    sum += Noise2D(x, y, frequency) * amplitude;
  }
  return sum * (1.0f / range);
}

T_FLOAT PerlinNoiseGenerator::FractalNoise3D(T_FLOAT x, T_FLOAT y, T_FLOAT z)
{
  T_FLOAT sum = Noise3D(x, y, z);
  T_FLOAT frequency = this->frequency_;
  T_FLOAT amplitude = 1.0f;
  T_FLOAT range = 1.0f;
  for (T_UINT32 o = 1; o < this->octaves_; o++)
  {
    frequency *= this->lacunarity_;
    amplitude *= this->persistence_;
    range += amplitude;
    sum += Noise3D(x, y, z, frequency) * amplitude;
  }
  return sum * (1.0f / range);
}
