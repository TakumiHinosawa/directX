//======================================
//
//壁表示処理
//Author:日野澤匠泉	[wall.cpp]
//
//=====================================
#include"main.h"
#include"wall.h"
#include"input.h"
#include"model.h"
#include"player.h"

//マクロ定義
#define WALL_SIZE	(2000.0f)	//壁のサイズ
#define NUM_WALL	(4)			//壁の個数

//グローバル変数宣言
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffWall = NULL;	//頂点のバッファ
WALL g_aWall[NUM_WALL];

//=========================================================================
//壁の初期化処理
//=========================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);
	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを初期化する(Z値を使用する)
		g_aWall[nCntWall].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = (-WALL_SIZE);
		pVtx[1].pos.x = (+WALL_SIZE * 2);
		pVtx[2].pos.x = (-WALL_SIZE);
		pVtx[3].pos.x = (+WALL_SIZE * 2);

		pVtx[0].pos.y = (+WALL_SIZE * 2);
		pVtx[1].pos.y = (+WALL_SIZE * 2);
		pVtx[2].pos.y = (+0.0f);
		pVtx[3].pos.y = (+0.0f);

		pVtx[0].pos.z = (0.0f);
		pVtx[1].pos.z = (0.0f);
		pVtx[2].pos.z = (0.0f);
		pVtx[3].pos.z = (0.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);

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
	g_pVtxBuffWall->Unlock();

	//--------------------------------------
	//壁の設置
	//--------------------------------------
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), 0);		//前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), 1);		//後ろ
	SetWall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), 2);		//左
	SetWall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), 3);		//右
}

//===================================
//壁の終了処理
//===================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの処理
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//===================================
//壁の更新処理
//===================================
void UpdateWall(void)
{
	VERTEX_3D *pVtx;
	Player *pPlayer = GetPlayer();

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			switch (g_aWall[nCntWall].nType)
			{
			case 0://前
				//頂点座標の設定
				pVtx[0].pos.x = (-WALL_SIZE);
				pVtx[1].pos.x = (+WALL_SIZE);
				pVtx[2].pos.x = (-WALL_SIZE);
				pVtx[3].pos.x = (+WALL_SIZE);

				pVtx[0].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[1].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+0.0f);
				pVtx[3].pos.y = (+0.0f);

				pVtx[0].pos.z = (+0.0f);
				pVtx[1].pos.z = (+0.0f);
				pVtx[2].pos.z = (+0.0f);
				pVtx[3].pos.z = (+0.0f);
				break;

			case 1://後ろ
				//頂点座標の設定
				pVtx[0].pos.x = (-WALL_SIZE);
				pVtx[1].pos.x = (+WALL_SIZE);
				pVtx[2].pos.x = (-WALL_SIZE);
				pVtx[3].pos.x = (+WALL_SIZE);

				pVtx[0].pos.y = (+0.0f);
				pVtx[1].pos.y = (+0.0f);
				pVtx[2].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[3].pos.y = (+WALL_SIZE * 0.5f);

				pVtx[0].pos.z = (+0.0f);
				pVtx[1].pos.z = (+0.0f);
				pVtx[2].pos.z = (+0.0f);
				pVtx[3].pos.z = (+0.0f);
				break;

			case 2://左
				//頂点座標の設定
				pVtx[0].pos.x = (-0.0f);
				pVtx[1].pos.x = (+0.0f);
				pVtx[2].pos.x = (-0.0f);
				pVtx[3].pos.x = (+0.0f);

				pVtx[0].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[1].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+0.0f);
				pVtx[3].pos.y = (+0.0f);

				pVtx[0].pos.z = (-WALL_SIZE);
				pVtx[1].pos.z = (+WALL_SIZE);
				pVtx[2].pos.z = (-WALL_SIZE);
				pVtx[3].pos.z = (+WALL_SIZE);
				break;

			case 3://右
				//頂点座標の設定
				pVtx[0].pos.x = (-0.0f);
				pVtx[1].pos.x = (+0.0f);
				pVtx[2].pos.x = (-0.0f);
				pVtx[3].pos.x = (+0.0f);

				pVtx[0].pos.y = (+0.0f);
				pVtx[1].pos.y = (+0.0f);
				pVtx[3].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+WALL_SIZE * 0.5f);

				pVtx[0].pos.z = (-WALL_SIZE);
				pVtx[1].pos.z = (+WALL_SIZE);
				pVtx[2].pos.z = (-WALL_SIZE);
				pVtx[3].pos.z = (+WALL_SIZE);
				break;
			}
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//====================================
//壁の描画処理
//====================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;					//計算用マトリックス
	int nCntWall;

	for (nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aWall[nCntWall].g_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorld, &g_aWall[nCntWall].g_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorld, &g_aWall[nCntWall].g_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].g_mtxWorld);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//壁の描画処理
		pDevice->SetTexture(0, g_pTextureWall);

		//壁の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * NUM_WALL, 2);		//プリミティブの種類
	}
}

//====================================
//壁の設定処理
//====================================
void SetWall(D3DXVECTOR3 pos,int nType)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{//敵が使用されない
			g_aWall [nCntWall].pos = pos;
			g_aWall[nCntWall].nType = nType;
			g_aWall[nCntWall].bUse = true;

			//頂点座標の設定
			pVtx[0].pos.x = (-WALL_SIZE);
			pVtx[1].pos.x = (+WALL_SIZE * 2);
			pVtx[2].pos.x = (-WALL_SIZE);
			pVtx[3].pos.x = (+WALL_SIZE * 2);

			pVtx[0].pos.y = (+WALL_SIZE * 2);
			pVtx[1].pos.y = (+WALL_SIZE * 2);
			pVtx[2].pos.y = (+0.0f);
			pVtx[3].pos.y = (+0.0f);

			pVtx[0].pos.z = (0);
			pVtx[1].pos.z = (0);
			pVtx[2].pos.z = (0);
			pVtx[3].pos.z = (0);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
}

//====================================
//壁の取得処理
//====================================
WALL *GetWall(void)
{
	return &g_aWall[NUM_WALL];
}

