#ifndef HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUT_H_
#define HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUT_H_

namespace EngineInput
{

enum Action
{
  ACTION_DOWN,
  ACTION_HOLD,
  ACTION_UP,

  ACTION_DATANUM,
};

// =================================================================
// Analog
// =================================================================

//アナログ入力は0~1の間で表現される。
namespace Analog
{
  //3次元以上の入力デバイスの為
  enum Demension
  {
    DIMENSION_X,
    DIMENSION_Y,

    DIMENSION_DATANUM,
  };

  //末端の英文字の連続は入力の次元がそれぞれ何に対応してるかを示している
  enum ID
  {
    ID_SCREEN_0_XY, //0
    ID_SCREEN_1_XY, //1

    ID_L_0_XY,  //2
    ID_L_1_XY,  //3

    ID_C_0_XY,  //4
    ID_C_1_XY,  //5

    ID_R_0_XY,  //6
    ID_R_1_XY,  //7

    ID_ANALOG_MAX  //8
  };
}

// =================================================================
// Digital
// =================================================================

//デジタル入力はアクションで状態を判別する
namespace Digital
{
  enum ID
  {
    ID_A, //0
    ID_B, //1
    ID_X, //2
    ID_Y, //3

    ID_C, //4
    ID_Z, //5

    ID_L1,  //6
    ID_L2,  //7
    ID_R1,  //8
    ID_R2,  //9

    ID_UP,    //10
    ID_LEFT,  //11
    ID_DOWN,  //12
    ID_RIGHT, //13

    ID_UP2,    //14
    ID_LEFT2,  //15
    ID_DOWN2,  //16
    ID_RIGHT2, //17

    ID_UP3,    //18
    ID_LEFT3,  //19
    ID_DOWN3,  //20
    ID_RIGHT3, //21

    //wiiリモコンの1,2,+,-ボタンや、HOMEボタンなど、
    //ハード毎の特殊なボタン用
    ID_S0,  //22
    ID_S1,  //23
    ID_S2,  //24
    ID_S3,  //25
    ID_S4,  //26
    ID_S5,  //27

    //デバッグ用のボタン
    ID_F1,  //28
    ID_F2,  //29
    ID_F3,  //30
    ID_F4,  //31

    ID_DIGITAL_MAX, //32
  };
}

}

#endif//HAL_ENGINE_SCENE_EVENT_ENGINEINPUT_ENGINEINPUT_H_
