#pragma once

//GameInput
//ゲームの入力を定義する
namespace GameInput
{

//新しいボタン入力を定義したい時はこの列挙型に追加していく
//追加した場合、cppファイル側にボタンの詳細を定義していく
enum
{
  X_AXIS, //X軸入力
  Y_AXIS, //Y軸入力

  MOUSE_CLICK_L, //マウスボタン入力
  MOUSE_CLICK_C, //マウスボタン入力
  MOUSE_CLICK_R, //マウスボタン入力
  MOUSE_SCREEN_X, //マウス座標Ｘ
  MOUSE_SCREEN_Y, //マウス座標Ｙ
  MOUSE_MOVE_X, //マウス入力Ｘ
  MOUSE_MOVE_Y, //マウス入力Ｙ
  MOUSE_MOVE_Z, //マウスホイール

  GAME_INPUT_DATANUM, //ここは触らない
};

//ここは触らない
const InputEntity* GetInputEntities();

}