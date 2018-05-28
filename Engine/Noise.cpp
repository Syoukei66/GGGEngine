#include "Noise.h"
#define HASH_CODE_MAX       (256)
#define HASH_CODE_TABLE_NUM     (HASH_CODE_MAX*2)

T_INT32 g_HashCode[HASH_CODE_TABLE_NUM] = {};

void SettingHash(unsigned int seed)
{
  srand(seed);

  const T_INT32 TABLE_NUM = HASH_CODE_MAX;
  T_UINT32 randomTable[TABLE_NUM] = {};
  for (int i = 0; i < TABLE_NUM; ++i) {
    randomTable[i] = rand() % HASH_CODE_MAX;
  }

  for (int i = 0; i < TABLE_NUM; ++i) {
    g_HashCode[i] = randomTable[i % TABLE_NUM];
  }
}

//乱数値取得.
unsigned int GetHash(int x, int y)
{
  x %= HASH_CODE_MAX;
  y %= HASH_CODE_MAX;
  return g_HashCode[x + g_HashCode[y]];
}

//乱数を0.0f~1.0fに正規化したものを取得する.
float GetValue(int x, int y)
{
  return (float)GetHash(x, y) / (float)(HASH_CODE_MAX - 1);
}

//五次補間関数.
float Fade(float t)
{
  //Ken Perlin氏(パーリンノイズを作った人)が考えだした補間関数.
  //6x^5 - 15x^4 + 10x^3.
  return (6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3));
}

//線形補間.
float Lerp(float a, float b, float t)
{
  return (a + (b - a) * t);
}

//バリューノイズ取得.
float ValueNoise(float x, float y)
{
  //整数部と小数部に分ける.
  int xi = (int)floorf(x);
  int yi = (int)floorf(y);
  float xf = x - xi;
  float yf = y - yi;

  //格子点を取り出す.
  float a00 = GetValue(xi, yi);
  float a10 = GetValue(xi + 1, yi);
  float a01 = GetValue(xi, yi + 1);
  float a11 = GetValue(xi + 1, yi + 1);

  //小数部分を使ってそのまま線形補間してしまうと折れ線グラフになってしまうので.
  //線形補間する前に小数部分を五次補間関数で歪めちゃう.
  xf = Fade(xf);
  yf = Fade(yf);

  //位置を基準に，各格子点からの影響を考慮した値を算出する.
  return Lerp(Lerp(a00, a10, xf), Lerp(a01, a11, xf), yf);
}

T_FLOAT Noise::Perlin(T_FLOAT x, T_FLOAT y)
{
  static bool initialized = false;
  if (!initialized)
  {
    SettingHash(0);
    initialized = true;
  }
  return ValueNoise(x, y);
}
