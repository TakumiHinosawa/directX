//======================================
//
//���͏���
//Author:�����V����
//
//=====================================
#include"input.h"
#include <Xinput.h>
#include"main.h"
#include <stdio.h>

//�}�N����`
#define NUM_KEY_MAX	(256)		//�L�[�̍ő吔
#define NUM_MOUSE_MAX (4)		//�}�E�X�̍ő吔

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
DIMOUSESTATE g_MouseState;
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
XINPUT_STATE state;

//�L�[�{�[�h�̏�����
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();
	return S_OK;

}

//================================================
//�L�[�{�[�h�̏I������
//================================================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//================================================
//�L�[�{�[�h�̍X�V����
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//�L�[�{�[�h�̓��͏��
	int nCntKey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//�L�[�{�[�h�̃v���X����ۑ�
		}
	}

	else
	{
		g_pDevKeyboard->Acquire();		//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//================================================
//�L�[�{�[�h�̃v���X�����擾
//================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//*****************************************
//�}�E�X������
//*****************************************
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(mouse)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;

	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevMouse->Acquire();
	return S_OK;
}

//*****************************************
//�}�E�X�I������
//*****************************************
void UninitMouse(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevMouse->Unacquire();		//�L�[�{�[�h�ւ̃A�N�Z�X����j��
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//*****************************************
//�}�E�X�̍X�V����
//*****************************************
void UpdateMouse(void)
{
	DIMOUSESTATE nMouseState;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(nMouseState), &nMouseState)))
	{
		for (int nCntKey = 0; nCntKey < NUM_MOUSE_MAX; nCntKey++)
		{

		}

		//�}�E�X�̃v���X����ۑ�
		g_MouseState = nMouseState;
	}
	else
	{
		//�}�E�X�ւ̃A�N�Z�X�����l��
		g_pDevMouse->Acquire();
	}
}

////*****************************************
////�}�E�X�̃v���X�����擾
////*****************************************
//bool GetMousePress(int nKey)
//{
//	return(g_aMouseState &) ? true : false;
//}

//*****************************************
//�}�E�X�f�o�b�O����
//*****************************************
void GetMouseDB(void)
{
	//char aStra[4];
	//LPD3DXFONT pFont = GetFont();						//�t�H���g�ւ̃|�C���^

	//for (int nCnt = 0; nCnt < NUM_MOUSE_MAX; nCnt++)
	//{
	//	RECT rect = { 0,nCnt * 20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//	if (nCnt < NUM_MOUSE_MAX)
	//	{
	//		wsprintf(&aStra[0],"MouseState:%d\n",&g_MouseState.rgbButtons[nCnt]);
	//	}

	//	//�e�L�X�g�̕`��
	//	pFont->DrawText(NULL, &aStra[0], -1, &rect, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//}

}
