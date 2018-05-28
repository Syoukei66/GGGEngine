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

//�����l�擾.
unsigned int GetHash(int x, int y)
{
  x %= HASH_CODE_MAX;
  y %= HASH_CODE_MAX;
  return g_HashCode[x + g_HashCode[y]];
}

//������0.0f~1.0f�ɐ��K���������̂��擾����.
float GetValue(int x, int y)
{
  return (float)GetHash(x, y) / (float)(HASH_CODE_MAX - 1);
}

//�܎���Ԋ֐�.
float Fade(float t)
{
  //Ken Perlin��(�p�[�����m�C�Y��������l)���l����������Ԋ֐�.
  //6x^5 - 15x^4 + 10x^3.
  return (6 * powf(t, 5) - 15 * powf(t, 4) + 10 * powf(t, 3));
}

//���`���.
float Lerp(float a, float b, float t)
{
  return (a + (b - a) * t);
}

//�o�����[�m�C�Y�擾.
float ValueNoise(float x, float y)
{
  //�������Ə������ɕ�����.
  int xi = (int)floorf(x);
  int yi = (int)floorf(y);
  float xf = x - xi;
  float yf = y - yi;

  //�i�q�_�����o��.
  float a00 = GetValue(xi, yi);
  float a10 = GetValue(xi + 1, yi);
  float a01 = GetValue(xi, yi + 1);
  float a11 = GetValue(xi + 1, yi + 1);

  //�����������g���Ă��̂܂ܐ��`��Ԃ��Ă��܂��Ɛ܂���O���t�ɂȂ��Ă��܂��̂�.
  //���`��Ԃ���O�ɏ����������܎���Ԋ֐��Řc�߂��Ⴄ.
  xf = Fade(xf);
  yf = Fade(yf);

  //�ʒu����ɁC�e�i�q�_����̉e�����l�������l���Z�o����.
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
