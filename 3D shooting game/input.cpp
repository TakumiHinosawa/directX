//======================================
//
//入力処理
//Author:日野澤匠泉
//
//=====================================
#include"input.h"
#include <Xinput.h>
#include"main.h"
#include <stdio.h>

//マクロ定義
#define NUM_KEY_MAX	(256)		//キーの最大数
#define NUM_MOUSE_MAX (4)		//マウスの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[NUM_KEY_MAX];
DIMOUSESTATE g_MouseState;
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;
XINPUT_STATE state;

//キーボードの初期化
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;

}

//================================================
//キーボードの終了処理
//================================================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();		//キーボードへのアクセス権を破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//================================================
//キーボードの更新処理
//================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		//キーボードの入力情報
	int nCntKey;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];		//キーボードのプレス情報を保存
		}
	}

	else
	{
		g_pDevKeyboard->Acquire();		//キーボードへのアクセス権を獲得
	}
}

//================================================
//キーボードのプレス情報を取得
//================================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}

//*****************************************
//マウス初期化
//*****************************************
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(mouse)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//協調モードを設定
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

	//キーボードへのアクセス権を獲得
	g_pDevMouse->Acquire();
	return S_OK;
}

//*****************************************
//マウス終了処理
//*****************************************
void UninitMouse(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevMouse->Unacquire();		//キーボードへのアクセス権を破棄
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//*****************************************
//マウスの更新処理
//*****************************************
void UpdateMouse(void)
{
	DIMOUSESTATE nMouseState;

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(nMouseState), &nMouseState)))
	{
		for (int nCntKey = 0; nCntKey < NUM_MOUSE_MAX; nCntKey++)
		{

		}

		//マウスのプレス情報を保存
		g_MouseState = nMouseState;
	}
	else
	{
		//マウスへのアクセス権を獲得
		g_pDevMouse->Acquire();
	}
}

////*****************************************
////マウスのプレス情報を取得
////*****************************************
//bool GetMousePress(int nKey)
//{
//	return(g_aMouseState &) ? true : false;
//}

//*****************************************
//マウスデバッグ処理
//*****************************************
void GetMouseDB(void)
{
	//char aStra[4];
	//LPD3DXFONT pFont = GetFont();						//フォントへのポインタ

	//for (int nCnt = 0; nCnt < NUM_MOUSE_MAX; nCnt++)
	//{
	//	RECT rect = { 0,nCnt * 20,SCREEN_WIDTH,SCREEN_HEIGHT };

	//	if (nCnt < NUM_MOUSE_MAX)
	//	{
	//		wsprintf(&aStra[0],"MouseState:%d\n",&g_MouseState.rgbButtons[nCnt]);
	//	}

	//	//テキストの描画
	//	pFont->DrawText(NULL, &aStra[0], -1, &rect, DT_RIGHT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//}

}
