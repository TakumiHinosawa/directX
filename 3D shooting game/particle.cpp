//======================================
//
//パーティクル処理
//Author:日野澤匠泉	[particle.cpp]
//
//=====================================
#include"particle.h"
#include"effect.h"

//マクロ定義
#define MAX_PARTICLE	(128)		//パーティクル最大数
#define SIZE			(20)		//パーティクルサイズ

//パーティクルの構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	int nLife;				//寿命
	int nType;				//種類
	bool bUse;				//使用しているかどうか
	D3DXMATRIX g_mtxWorld;	//ワールドマトリックス
}Particle;

//グローバル変数宣言
Particle g_aParticle[MAX_PARTICLE];
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//頂点バッファへのポインタ

//=========================================================================
//パーティクルの初期化処理
//=========================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureParticle);

	//パーティクルの情報の初期化
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt)
	{
		g_aParticle[MAX_PARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[MAX_PARTICLE].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[MAX_PARTICLE].nLife = 20;
		g_aParticle[MAX_PARTICLE].bUse = false;
		g_aParticle[MAX_PARTICLE].nType = 0;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_PARTICLE; nCntEffect++)
	{
		//頂点座標の設定
		pVtx[0].pos.x = (-SIZE);
		pVtx[1].pos.x = (+SIZE);
		pVtx[2].pos.x = (-SIZE);
		pVtx[3].pos.x = (+SIZE);

		pVtx[0].pos.y = (+SIZE);
		pVtx[1].pos.y = (+SIZE);
		pVtx[2].pos.y = (-SIZE);
		pVtx[3].pos.y = (-SIZE);

		pVtx[0].pos.z = (0);
		pVtx[1].pos.z = (0);
		pVtx[2].pos.z = (0);
		pVtx[3].pos.z = (0);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;		//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//=========================================================================
//パーティクルの終了処理
//=========================================================================
void UninitParticle(void)
{
	//テクスチャの破棄
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=========================================================================
//パーティクルの更新処理
//=========================================================================
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//パーティクルの作成
			for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
			{
				//頂点座標の設定
				pVtx[0].pos.x = (-SIZE);
				pVtx[1].pos.x = (+SIZE);
				pVtx[2].pos.x = (-SIZE);
				pVtx[3].pos.x = (+SIZE);

				pVtx[0].pos.y = (+SIZE);
				pVtx[1].pos.y = (+SIZE);
				pVtx[2].pos.y = (-SIZE);
				pVtx[3].pos.y = (-SIZE);

				pVtx[0].pos.z = (0);
				pVtx[1].pos.z = (0);
				pVtx[2].pos.z = (0);
				pVtx[3].pos.z = (0);

				//パーティクルの距離
				g_aParticle[nCnt].nLife--;

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

				SetEffect(g_aParticle[nCnt].pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),SIZE,g_aParticle[nCnt].nLife);
			}
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}

//=========================================================================
//パーティクルの描画処理
//=========================================================================
void DrawParticle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;
	D3DXMATRIX mtxTrans;		//計算用マトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス取得用
	int nCnt;

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//aブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aParticle[nCnt].g_mtxWorld);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_aParticle[nCnt].g_mtxWorld, NULL, &mtxView);		//逆行列を求める
			g_aParticle[nCnt].g_mtxWorld._41 = 0.0f;
			g_aParticle[nCnt].g_mtxWorld._42 = 0.0f;
			g_aParticle[nCnt].g_mtxWorld._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCnt].pos.x, g_aParticle[nCnt].pos.y, g_aParticle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aParticle[nCnt].g_mtxWorld, &g_aParticle[nCnt].g_mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCnt].g_mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//ポリゴンの描画処理
			pDevice->SetTexture(0, g_pTextureParticle);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);		//プリミティブの種類
		}
	}

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//aブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=========================================================================
//パーティクルの設定処理
//=========================================================================
void SetParticle(D3DXVECTOR3 pos,int nType)
{
	int nCnt;
	VERTEX_3D *pVtx = 0;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].nType = nType;
			g_aParticle[nCnt].bUse = true;

			//頂点座標の設定
			pVtx[0].pos.x = (-SIZE);
			pVtx[1].pos.x = (+SIZE);
			pVtx[2].pos.x = (-SIZE);
			pVtx[3].pos.x = (+SIZE);

			pVtx[0].pos.y = (+SIZE);
			pVtx[1].pos.y = (+SIZE);
			pVtx[2].pos.y = (-SIZE);
			pVtx[3].pos.y = (-SIZE);

			pVtx[0].pos.z = (0);
			pVtx[1].pos.z = (0);
			pVtx[2].pos.z = (0);
			pVtx[3].pos.z = (0);

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffParticle->Unlock();
}