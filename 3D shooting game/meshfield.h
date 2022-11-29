//======================================
//
//メッシュフィールド処理
//Author:日野澤匠泉	[meshfield.h]
//
//=====================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXMATRIX g_mtxWorld;			//ワールドマトリックス
	int nIdxShadow;				//対象の影のインデックス(番号)
}MeshField;

//プロトタイプ宣言
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
