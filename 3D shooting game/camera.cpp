//======================================
//
//カメラ処理
//Author:日野澤匠泉	[camera.cpp]
//
//=====================================
#include"camera.h"
#include"main.h"
#include"input.h"
#include"model.h"
#include"player.h"

//マクロ定義
#define MOVE	(0.25f)		//移動量
#define MOVES	(0.01f)		//角度移動量
#define DIS		(300.0f)	//距離

//グローバル変数宣言
Camera g_camera;

//================================================
//カメラの初期化処理
//================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 80.0f,-300.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//================================================
//カメラの終了処理
//================================================
void UninitCamera(void)
{

}

//================================================
//カメラの更新処理
//================================================
void UpdateCamera(void)
{
	//-----------------------------------
	//キーボード操作
	//-----------------------------------
	if (GetKeyboardPress(DIK_A) == true)
	{//左移動
		g_camera.move.x += sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * MOVE;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//右移動
		g_camera.move.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * MOVE;
	}
	if (GetKeyboardPress(DIK_W) == true)
	{//上移動
		g_camera.move.x += sinf(g_camera.rot.y) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y) * MOVE;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//下移動
		g_camera.move.x -= sinf(g_camera.rot.y) * MOVE;
		g_camera.move.z -= cosf(g_camera.rot.y) * MOVE;
	}

	if (GetKeyboardPress(DIK_X) == true)
	{//Y座標上
		g_camera.move.y += MOVE;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{//Y座標下
		g_camera.move.y -= MOVE;
	}

	//-----------------------------------
	//			     視点
	//-----------------------------------
	if (GetKeyboardPress(DIK_E) == true)
	{//右回転
		g_camera.rot.y += MOVES;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{//左回転
		g_camera.rot.y -= MOVES;
	}
	//カメラ回転
	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * DIS;		//視点から見てrotの方向にどれだけ離れているか
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * DIS;

	if (GetKeyboardPress(DIK_1) == true)
	{//視点回転
		g_camera.rot.y += MOVES;
	}
	if (GetKeyboardPress(DIK_3) == true)
	{//視点回転
		g_camera.rot.y -= MOVES;
	}
	//カメラ回転
	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -DIS;	//注視点から見てrotの方向にどれだけ離れているか
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -DIS;

	if (GetKeyboardPress(DIK_T) == true)
	{//上を向く
		g_camera.posR.y += MOVE;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//下を向く
		g_camera.posR.y -= MOVE;
	}

	//移動量代入
	g_camera.posV += g_camera.move;
	g_camera.posR += g_camera.move;

	//プレイヤー情報取得
	Player *pPlayer = GetPlayer();

	//モデルの移動量を更新(減衰させる)
	g_camera.move.x += (0.0f - g_camera.move.x) * 0.12f;
	g_camera.move.y += (0.0f - g_camera.move.y) * 0.12f;
	g_camera.move.z += (0.0f - g_camera.move.z) * 0.12f;

	//慣性
	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * -DIS;	//目的の視点にモデルの位置を代入(相対座標)
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * -DIS;	//目的の視点にモデルの位置を代入(相対座標)
	(g_camera.posVDest - g_camera.posV) * 0.1f;

	//カメラ追従処理
	g_camera.posR = pPlayer->pos;		//注視点にモデルの位置を代入	
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;	//視点にモデルの位置を代入(相対座標)
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;	//視点にモデルの位置を代入(相対座標)
}

//================================================
//カメラの設定処理
//================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスのポインタ
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),	//視野角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//アスペクト比
		10.0f,		//Z値の最小値
		5000.0f);	//Z値の最大値

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,	//視点
		&g_camera.posR,	//注視点
		&g_camera.posU);//上方向ベクトル

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//================================================
//カメラ回転処理
//================================================
void RotCamera(void)
{
	//目標の角度
	D3DXVECTOR3 RotDiff;

	//モデルの情報取得
	Player *pPlayer = GetPlayer();

	//プレイヤーの角度を設定
	g_camera.rotDest = pPlayer->rot;
	RotDiff = g_camera.rotDest - g_camera.rot;

	//移動方向の補正
	if (RotDiff.y > D3DX_PI || RotDiff.y < -D3DX_PI)
	{
		if (RotDiff.y > D3DX_PI)
		{
			RotDiff.y += -D3DX_PI * 2;
		}
		else if (RotDiff.y < -D3DX_PI)
		{
			RotDiff.y += D3DX_PI * 2;
		}
	}

	g_camera.rot.y += RotDiff.y * 0.03f;

	//移動方向の補正
	if (g_camera.rot.y > D3DX_PI || g_camera.rot.y < -D3DX_PI)
	{
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y += -D3DX_PI * 2;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}
	}

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -DIS;	//注視点から見てrotの方向にどれだけ離れているか
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -DIS;

}


//================================================
//カメラ情報の取得
//================================================
Camera *GetCamera(void)
{
	return &g_camera;
}


