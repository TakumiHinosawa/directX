//======================================
//
//影表示処理
//Author:日野澤匠泉	[shadow.cpp]
//
//=====================================
#include"main.h"
#include"shadow.h"
#include"input.h"

//マクロ定義
#define SHADOW_SIZE	(30.0f)			//影のサイズ
#define SHADOW_MAX	(128)			//影の最大数

//グローバル変数宣言
LPDIRECT3DTEXTURE9	g_pTextureShadow = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffShadow = NULL;	//頂点のバッファ
Shadow g_aShadow[SHADOW_MAX];	//影の情報

//=========================================================================
//影の初期化処理
//=========================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	pDevice = GetDevice();
	
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		//各種変数初期化
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを初期化する(Z値を使用する)
		g_aShadow[nCnt].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * SHADOW_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = (-SHADOW_SIZE);
		pVtx[1].pos.x = (+SHADOW_SIZE);
		pVtx[2].pos.x = (-SHADOW_SIZE);
		pVtx[3].pos.x = (+SHADOW_SIZE);

		pVtx[0].pos.y = (+0.0f);
		pVtx[1].pos.y = (+0.0f);
		pVtx[2].pos.y = (+0.0f);
		pVtx[3].pos.y = (+0.0f);

		pVtx[0].pos.z = (+SHADOW_SIZE);
		pVtx[1].pos.z = (+SHADOW_SIZE);
		pVtx[2].pos.z = (-SHADOW_SIZE);
		pVtx[3].pos.z = (-SHADOW_SIZE);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();

}

//===================================
//影の終了処理
//===================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの処理
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//===================================
//影の更新処理
//===================================
void UpdateShadow(void)
{

}

//====================================
//影の描画処理
//====================================
void DrawShadow(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aShadow[nCnt].g_mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x,  g_aShadow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].g_mtxWorld, &g_aShadow[nCnt].g_mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].g_mtxWorld, &g_aShadow[nCnt].g_mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCnt].g_mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画処理
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);		//プリミティブの種類
		}
	}

	//通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================
//影の設定処理
//====================================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == false)
		{//使われていなかったとき
			nCntShadow = nCnt;
			g_aShadow[nCnt].bUse = true;
			break;
		}
	}

	return nCntShadow;
}

//====================================
//影の設定処理
//====================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos.x = pos.x;
	g_aShadow[nIdxShadow].pos.z = pos.z;
}

//====================================
//影の削除処理
//====================================
void TrushShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}
