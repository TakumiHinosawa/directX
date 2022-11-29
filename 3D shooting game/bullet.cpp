//==========================================================================
//
//玉の発射処理
//Author:日野澤匠泉
//
//=========================================================================

#include"bullet.h"
#include"main.h"
#include"input.h"
#include"wall.h"
#include"explosion.h"
#include"shadow.h"
#include"effect.h"

//マクロ定義
#define MAX_BULLET		(128)		//弾の最大数
#define SIZE			(10)		//弾のサイズ
#define WALL_SIZE	(200.0f)	//壁のサイズ

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXMATRIX g_mtxWorldBullet;		//ワールドマトリックス
	BULLETTYPE type;
	int nIdxShadow = -1;				//対象の影のインデックス(番号)
	int nLife;
	bool bUse;

}Bullet;

//グローバル変数
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//頂点のバッファ
Bullet g_aBullet[MAX_BULLET];		//弾の情報

//============================================================================
//弾の初期化処理
//============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ball09_orange.png",
		&g_pTextureBullet);

	//弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 20;
		g_aBullet[nCntBullet].bUse = false;		//使用していない状態にする
		g_aBullet[nCntBullet].nIdxShadow = -1;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	//頂点バッファをロックし、頂点データへのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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

		pVtx[0].pos.z = (0.0f);
		pVtx[1].pos.z = (0.0f);
		pVtx[2].pos.z = (0.0f);
		pVtx[3].pos.z = (0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//=======================================================================
//弾の終了処理
//=======================================================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=======================================================================
//弾の更新処理
//=======================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用される

			//影の位置を設定
 			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//エフェクト更新
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 14, 8);

			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//寿命を減らす処理
			g_aBullet[nCntBullet].nLife--;

			//寿命のカウントダウン
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
 				SetExplosion(g_aBullet[nCntBullet].pos, D3DCOLOR_RGBA(255, 255, 255, 255));
				TrushShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].bUse = false;			//使用していない状態にする	
			}
			//頂点バッファをアンロックする
			g_pVtxBuffBullet->Unlock();
		}
		pVtx += 4;		//頂点データのポインタを4つ分進める
	}
}

//========================================================================
//弾の描画処理
//========================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスのポインタ
	D3DXMATRIX mtxTrans;		//計算用マトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス取得用
	int nCntBullet;

	//アルファテストを有効にする
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用された

		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].g_mtxWorldBullet);

		//ビューマトリックスを取得
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//ポリゴンをカメラに対して正面に向ける
		D3DXMatrixInverse(&g_aBullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);		//逆行列を求める
		g_aBullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
		g_aBullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
		g_aBullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].g_mtxWorldBullet, &g_aBullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].g_mtxWorldBullet);

		//頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//ポリゴンの描画処理
		pDevice->SetTexture(0, g_pTextureBullet);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);		//プリミティブの種類
		}
	}
	//アルファテストを無効にする
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//========================================================================
//弾の設定処理
//========================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使用されない
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 20;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			break;
		}
		pVtx += 4;		//頂点データのポインタを4つ分進める
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
