//======================================
//
//入力処理
//Author:日野澤匠泉
//
//=====================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//マウスボタン構造体定義
typedef struct
{

}MOUSE_BUTTON;

//プロトタイプ宣言
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);
void UninitMouse(void);
void UpdateMouse(void);
//bool GetMousePress(int nKey);
void GetMouseDB(void);

#endif
