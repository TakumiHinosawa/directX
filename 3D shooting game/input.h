//======================================
//
//���͏���
//Author:�����V����
//
//=====================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include"main.h"

//�}�E�X�{�^���\���̒�`
typedef struct
{

}MOUSE_BUTTON;

//�v���g�^�C�v�錾
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
