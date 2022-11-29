//======================================
//
//モデル表示処理
//Author:日野澤匠泉	[model.cpp]
//
//=====================================
#include"main.h"
#include"model.h"
#include"input.h"
#include"shadow.h"

//マクロ定義
#define MOVE	(0.8f)		//移動量
#define MAX_TEX	(32)		//テクスチャ最大数
#define TIMING	(20)		//弾発射の速度
#define BULLETSPEED	(10.0f)	//弾の速度
#define MAX_MODEL	(2)		//モデルの最大数

//グローバル変数宣言
Model g_aModel[MAX_MODEL];	//モデルの情報

//=========================================================================
//モデルの初期化処理
//=========================================================================
void InitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//各種変数初期化
		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向きを初期化する(Z値を使用する)
		g_aModel[nCnt].nIdxShadow = -1;							//対象の影のインデックス(番号)初期化
		g_aModel[nCnt].Mesh = {};			//メッシュ(頂点情報)へのポインタ
		g_aModel[nCnt].BuffMat = {};		//マテリアルのポインタ
		g_aModel[nCnt].dwNumMat = 0;		//マテリアルの数
	}

	//-------------------------
	// SetModel
	//-------------------------
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 100.0f), 1);
}

//===================================
//モデルの終了処理
//===================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//メッシュの破棄
		if (g_aModel[nCnt].Mesh != NULL)
		{
			g_aModel[nCnt].Mesh->Release();
			g_aModel[nCnt].Mesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModel[nCnt].BuffMat != NULL)
		{
			g_aModel[nCnt].BuffMat->Release();
			g_aModel[nCnt].BuffMat = NULL;
		}
	}
}

//===================================
//モデルの更新処理
//===================================
void UpdateModel(void)
{

}

//====================================
//モデルの描画処理
//====================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;					//計算用
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータへのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{//使用されていない時
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			//現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			//マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
			{
				//マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_aModel[nCnt].apTexture[nCntMat]);

				//モデル(パーツ)の描画
				g_aModel[nCnt].Mesh->DrawSubset(nCntMat);
			}
			//保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================
//モデルの設定処理
//====================================
Model *GetModel(void)
{
	return &g_aModel[0];
}

//====================================
//モデルの配置処理
//====================================
void SetModel(D3DXVECTOR3 pos, int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスのポインタ
	D3DXMATERIAL *pMat;			//マテリアルデータへのポインタ
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファのポインタ

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{//使用されていない時
			nType = g_aModel[nCnt].nType;

			switch (g_aModel[nCnt].nType)
			{
			case 0:
				//Xファイルの読み込み
				D3DXLoadMeshFromX("data\\MODEL\\switch.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_aModel[nCnt].BuffMat,
					NULL,
					&g_aModel[nCnt].dwNumMat,
					&g_aModel[nCnt].Mesh);

				//頂点数を取得
				nNumVtx = g_aModel[nCnt].Mesh->GetNumVertices();

				//頂点フォーマットのサイズを取得
				dwSizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].Mesh->GetFVF());

				//頂点バッファをロック
				g_aModel[nCnt].Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);		//頂点座標の代入

				//マテリアル情報に対するポインタを取得
				pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{//テクスチャファイルが存在する

					 //テクスチャの読み込み
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_aModel[nCntMat].apTexture[nCntMat]);
					}
				}

				//影を設定
				g_aModel[nCnt].nIdxShadow = SetShadow();

			case 1:
				//Xファイルの読み込み
				D3DXLoadMeshFromX("data\\MODEL\\switch.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_aModel[nCnt].BuffMat,
					NULL,
					&g_aModel[nCnt].dwNumMat,
					&g_aModel[nCnt].Mesh);

				//頂点数を取得
				nNumVtx = g_aModel[nCnt].Mesh->GetNumVertices();

				//頂点フォーマットのサイズを取得
				dwSizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].Mesh->GetFVF());

				//頂点バッファをロック
				g_aModel[nCnt].Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);		//頂点座標の代入

				//マテリアル情報に対するポインタを取得
				pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{//テクスチャファイルが存在する

						//テクスチャの読み込み
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_aModel[nCnt].apTexture[nCntMat]);
					}
				}
				//影を設定
				g_aModel[nCnt].nIdxShadow = SetShadow();
			}
		}
	}
}

