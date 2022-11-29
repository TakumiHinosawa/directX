//======================================
//
//壁表示処理
//Author:日野澤匠泉	[wall.h]
//
//=====================================

#ifndef _WALL_H_	//この定義がされていなかったら
#define _WALL_H_	//二重インクルード防止のマクロ定義をする

//壁の構造体定義
typedef struct
{
	D3DXVECTOR3 pos;			//現在の位置
	D3DXVECTOR3 rot;			//向き
	D3DXMATRIX g_mtxWorld;		//ワールドマトリックス
	bool bUse;					//使用しているかどうか
	int nType;					//壁の種類
}WALL;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos,int nType);
WALL *GetWall(void);

#endif
