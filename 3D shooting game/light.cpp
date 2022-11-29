//======================================
//
//ライト処理
//Author:日野澤匠泉	[light.cpp]
//
//=====================================
#include"light.h"

//マクロ定義
#define MAX_LIGHT	(3)		//ライトの数

//グローバル変数宣言
D3DLIGHT9 g_light[MAX_LIGHT];

//================================================
//ライトの初期化処理
//================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;		//設定方向ベクトル

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//ライトの情報をクリアする
		ZeroMemory(&g_light[nCnt], sizeof(D3DLIGHT9));

		//ライトの種類を設定
		g_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCnt)
		{
		case 0:
			//ライトの拡散光を設定
			g_light[nCnt].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.22f, -0.85f, 0.45f);
			break;

		case 1:
			//ライトの拡散光を設定
			g_light[nCnt].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.89f, -0.15f, 0.15f);
			break;

		case 2:
			//ライトの拡散光を設定
			g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//ライトの方向を設定
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);		//ベクトルを正規化する
		g_light[nCnt].Direction = vecDir;
		
		//ライトを設定する
		pDevice->SetLight(nCnt, &g_light[nCnt]);

		//ライトを有効にする
		pDevice->LightEnable(nCnt, TRUE);
	}
}
//================================================
//ライトの終了処理
//================================================
void UninitLight(void)
{

}

//================================================
//ライトの更新処理
//================================================
void UpdateLight(void)
{

}
