//======================================
//
//メッシュシリンダー処理
//Author:日野澤匠泉	[meshsylinder.h]
//
//=====================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX g_mtxWorld;			//ワールドマトリックス
}MeshCylinder;

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif
