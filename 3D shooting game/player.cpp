//======================================
//
//プレイヤー処理
//Author:日野澤匠泉	[model.cpp]
//
//=====================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"wall.h"

//マクロ定義
#define MOVE	(0.8f)	//移動量
#define MAX_TEX	(32)	//テクスチャ最大数
#define TIMING	(20)	//弾発射の速度
#define BULLETSPEED	(10.0f)

//グローバル変数宣言
LPD3DXMESH g_pMeshPlayer = NULL;			//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//マテリアルのポインタ
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_TEX] = {};	//テクスチャへのポインタ
DWORD g_dwNumMatPlayer = 0;				//マテリアルの数
int g_nCounter;
Player g_Player;	//モデルの情報
bool b_camera;	//カメラ追従オンオフ

//=========================================================================
//プレイヤーの初期化処理
//=========================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	pDevice = GetDevice();
	D3DXMATERIAL *pMat;			//マテリアルデータへのポインタ

	//各種変数初期化
	g_Player.pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//位置の初期化
	g_Player.rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//向きを初期化する(Z値を使用する)
	g_Player.nIdxShadow = -1;								//対象の影のインデックス(番号)初期化
	b_camera = false;

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\trueno.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//テクスチャファイルが存在する

			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}
	//影を設定
	g_Player.nIdxShadow = SetShadow();
}

//===================================
//プレイヤーの終了処理
//===================================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//===================================
//プレイヤーの更新処理
//===================================
void UpdatePlayer(void)
{
	//カメラ情報取得
	Camera *pCamera = GetCamera();
	float fRotMove = g_Player.rot.y;	//現在の向き
	float fRotDest = g_Player.rot.y;	//行きたい方向
	float fRotDiff = g_Player.rot.y;	//目的の方向

	//-------------------------------------------------
	//キーボード操作
	//-------------------------------------------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//←が押されたとき
		if (GetKeyboardPress(DIK_UP) == true)
		{//↑
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.25f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//↓
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.75f);
		}
		else
		{//←
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.5f);
		}
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//→が押されたとき
		if (GetKeyboardPress(DIK_UP) == true)
		{//↑
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.25f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//↓
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.75f);
		}
		else
		{//→
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//上移動
		g_Player.move.x += sinf(pCamera->rot.y) * MOVE;
		g_Player.move.z += cosf(pCamera->rot.y) * MOVE;
		fRotDest = pCamera->rot.y;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//下移動
		g_Player.move.x -= sinf(pCamera->rot.y) * MOVE;
		g_Player.move.z -= cosf(pCamera->rot.y) * MOVE;
		fRotDest = pCamera->rot.y + D3DX_PI;
	}

	if (GetKeyboardPress(DIK_I) == true)
	{//上昇
		g_Player.move.y += MOVE;
	}
	if (GetKeyboardPress(DIK_K) == true)
	{//下降
		g_Player.move.y -= MOVE;
	}
	if (GetKeyboardPress(DIK_RETURN) == true)
	{//ポリゴン位置リセット
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置の初期化
	}
	if (GetKeyboardPress(DIK_SPACE) == true/* && g_nCounter >= TIMING*/)
	{//SPACEキーが押された
		SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y) * BULLETSPEED, 0.0f, cosf(g_Player.rot.y) * BULLETSPEED), 20, BULLETTYPE_PLAYER);
		g_nCounter = 0;
	}

	//移動量代入
	g_Player.pos += g_Player.move;

	//影の位置を設定
	SetPositionShadow(g_Player.nIdxShadow, g_Player.pos);

	//移動量を更新(減衰させる)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.12f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.12f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.12f;

	if (b_camera == false)
	{
		//移動量がゼロに近づいたとき
		if (g_Player.move.x <= 0.01f && g_Player.move.x >= -0.01f)
		{
			if (g_Player.move.z <= 0.01f && g_Player.move.z >= -0.01f)
			{
				RotCamera();
			}
		}
	}
	if (GetKeyboardPress(DIK_F1) == true)
	{//F1が押されたら追従終了
		b_camera = true;
	}
	else if (GetKeyboardPress(DIK_F2) == true)
	{//F2が押されたら追従開始
		b_camera = false;
	}

	//角度算出
	fRotDiff = fRotDest - fRotMove;		//目標の移動方向までの差分

	//移動方向の補正
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += -D3DX_PI * 2;
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2;
		}
	}

	g_Player.rot.y += fRotDiff * 0.1f;

	//移動方向の補正
	if (g_Player.rot.y > D3DX_PI || g_Player.rot.y < -D3DX_PI)
	{
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y += -D3DX_PI * 2;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2;
		}
	}
	g_nCounter++;

	//床の判定
	if (g_Player.pos.y <= 0.0f)
	{
		g_Player.pos.y = 0.0f;
	}

	//壁の判定
	if (g_Player.pos.z >= 2000.0f)
	{
		g_Player.pos.z = 2000.0f;
	}
	if (g_Player.pos.z <= -2000.0f)
	{
		g_Player.pos.z = -2000.0f;
	}
	if (g_Player.pos.x <= -2000.0f)
	{
		g_Player.pos.x = -2000.0f;
	}
	if (g_Player.pos.x >= 2000.0f)
	{
		g_Player.pos.x = 2000.0f;
	}
}

//====================================
//プレイヤーの描画処理
//====================================
void DrawPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//デバイスのポインタ
	D3DXMATRIX mtxRot, mtxTrans;					//計算用
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.g_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.g_mtxWorld, &g_Player.g_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.g_mtxWorld, &g_Player.g_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.g_mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}
	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//====================================
//プレイヤーの設定処理
//====================================
Player *GetPlayer(void)
{
	return &g_Player;
}
