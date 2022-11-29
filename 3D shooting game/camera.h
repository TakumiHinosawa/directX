//======================================
//
//カメラ処理
//Author:日野澤匠泉	[camera.h]
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

//カメラの構造体定義
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 posU;			//上方向ベクトル
	D3DXVECTOR3 posVDest;		//目的の視点
	D3DXVECTOR3 posRDest;		//目的の注視点
	D3DXVECTOR3 move;			//移動値
	D3DXVECTOR3 rot;			//向き
	D3DXVECTOR3 rotDest;		//目標の角度
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void RotCamera(void);
Camera *GetCamera(void);

#endif
