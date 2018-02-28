#include "DirectXNativeImplements.h"
#include <XInput.h>
#include <HalEngine.h>
#include <WinUser.h>

#include "DirectXInputDevice_Keyboard.h"
#include "DirectXInputDevice_XInput.h"
#include "DirectXInputDevice_Mouse.h"

#define KEY_CHECK(KEY,CODE) if (s == #KEY) return DIK_##CODE
#define K_(CODE) KEY_CHECK(CODE,CODE)
#define K2_(KEY,CODE) KEY_CHECK(KEY,CODE)

DWORD StringToKey(const std::string& s)
{
  K_(A); K_(B); K_(C); K_(D); K_(E);
  K_(F); K_(G); K_(H); K_(I); K_(J);
  K_(K); K_(L); K_(M); K_(N); K_(O);
  K_(P); K_(Q); K_(R); K_(S); K_(T);
  K_(U); K_(V); K_(W); K_(X); K_(Y);
  K_(Z);

  K_(LEFT); K_(RIGHT); K_(UP); K_(DOWN);
  K2_(←,LEFT); K2_(→,RIGHT); K2_(↑,UP); K2_(↓,DOWN);

  K_(SEMICOLON);  K2_(;, SEMICOLON);
  K_(SPACE);
  K_(LSHIFT);
  K_(RSHIFT);

  return 0;
}

#undef KEY_CHECK
#undef K_
#undef K2_

using namespace EngineInput;

enum { KEYBOARD_INPUT_MAX = 26 };

enum DirectXInputID
{
  DX_INPUT_A,
  DX_INPUT_B,
  DX_INPUT_X,
  DX_INPUT_Y,

  DX_INPUT_L1,
  DX_INPUT_L2,
  DX_INPUT_R1,
  DX_INPUT_R2,

  DX_INPUT_LEFT,
  DX_INPUT_RIGHT,
  DX_INPUT_UP,
  DX_INPUT_DOWN,

  DX_INPUT_L_X_AXIS_POSITIVE,
  DX_INPUT_L_X_AXIS_NEGATIVE,
  DX_INPUT_L_Y_AXIS_POSITIVE,
  DX_INPUT_L_Y_AXIS_NEGATIVE,
 
  DX_INPUT_R_X_AXIS_POSITIVE,
  DX_INPUT_R_X_AXIS_NEGATIVE,
  DX_INPUT_R_Y_AXIS_POSITIVE,
  DX_INPUT_R_Y_AXIS_NEGATIVE,

  DX_INPUT_START,
  DX_INPUT_BACK,

  DX_INPUT_DATANUM,
};

static DirectXInputDevice_KeyBoard::KeyboardInput KEYBOARD_INPUTS[DX_INPUT_DATANUM + 4] =
{
  { Digital::ID_A, 0 },
  { Digital::ID_B, 0 },
  { Digital::ID_X, 0 },
  { Digital::ID_Y, 0 },

  { Digital::ID_L1, 0 },
  { Digital::ID_L2, 0 },

  { Digital::ID_R1, 0 },
  { Digital::ID_R2, 0 },

  { Digital::ID_LEFT, 0 },
  { Digital::ID_RIGHT, 0 },
  { Digital::ID_DOWN, 0 },
  { Digital::ID_UP, 0 },

  { Digital::ID_LEFT2, 0 },
  { Digital::ID_RIGHT2, 0 },
  { Digital::ID_DOWN2, 0 },
  { Digital::ID_UP2, 0 },

  { Digital::ID_LEFT3, 0 },
  { Digital::ID_RIGHT3, 0 },
  { Digital::ID_DOWN3, 0 },
  { Digital::ID_UP3, 0 },

  { Digital::ID_S0, 0 },
  { Digital::ID_S1, 0 },

  { Digital::ID_F1, DIK_1 },
  { Digital::ID_F2, DIK_2 },
  { Digital::ID_F3, DIK_3 },
  { Digital::ID_F4, DIK_4 },
};

enum { XINPUT_INPUT_MAX = 14 };

static const DirectXInputDevice_XInput::XInputInput XINPUT_INPUTS[XINPUT_INPUT_MAX] =
{
  { Digital::ID_A, XINPUT_GAMEPAD_A },
  { Digital::ID_B, XINPUT_GAMEPAD_B },
  { Digital::ID_X, XINPUT_GAMEPAD_X },
  { Digital::ID_Y, XINPUT_GAMEPAD_Y },

  { Digital::ID_R1, XINPUT_GAMEPAD_RIGHT_SHOULDER },
  { Digital::ID_L1, XINPUT_GAMEPAD_LEFT_SHOULDER },

  { Digital::ID_LEFT,   XINPUT_GAMEPAD_DPAD_LEFT },
  { Digital::ID_RIGHT,  XINPUT_GAMEPAD_DPAD_RIGHT },
  { Digital::ID_UP,     XINPUT_GAMEPAD_DPAD_UP },
  { Digital::ID_DOWN,   XINPUT_GAMEPAD_DPAD_DOWN },

  { Digital::ID_S0, XINPUT_GAMEPAD_START },
  { Digital::ID_S1, XINPUT_GAMEPAD_BACK },
};

enum { MOUSE_INPUT_MAX = 1 };
static const DirectXInputDevice_Mouse::MouseInput MOUSE_INPUTS[MOUSE_INPUT_MAX] =
{
  { Digital::ID_S5, DirectXInputDevice_Mouse::MOUSE_RGB_BUTTON_LEFT }
};

void DirectXNativeImplements::SetupInputDevices(DirectXInputDeviceManager* manager)
{
  CSVData csv = CSVData("keyconfig_DX9.txt");
  for (T_UINT8 i = 0; i < DX_INPUT_DATANUM; ++i)
  {
    CSVTokenizer tokenizer = csv.GetTokenizer(i);
    if (!tokenizer.HasNextToken())
    {
      continue;
    }
    tokenizer.NextToken();
    if (!tokenizer.HasNextToken())
    {
      continue;
    }
    KEYBOARD_INPUTS[i].input = StringToKey(tokenizer.NextToken().ToString());
  }

  //キーボードは1Pに対応
  manager->LoadDevice(new DirectXInputDevice_KeyBoard(0, KEYBOARD_INPUTS, KEYBOARD_INPUT_MAX));
  
  //マウスはデバッグ用のみ
  manager->LoadDevice(new DirectXInputDevice_Mouse(0, MOUSE_INPUTS, MOUSE_INPUT_MAX, Analog::ID_SCREEN_1_XY, Analog::ID_SCREEN_0_XY));

  //ジョイスティックは(1P～4P)
  manager->LoadDevice(new DirectXInputDevice_XInput(0, 0, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(1, 1, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(2, 2, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
  manager->LoadDevice(new DirectXInputDevice_XInput(3, 3, XINPUT_INPUTS, XINPUT_INPUT_MAX, Analog::ID_L_0_XY, Analog::ID_R_0_XY, Analog::ID_C_0_XY));
}