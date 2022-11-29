//======================================
//
//影表示処理
//Author:日野澤匠泉	[shadow.h]
//
//=====================================

#ifndef _SHADOW_H_	//この定義がされていなかったら
#define _SHADOW_H_	//二重インクルード防止のマクロ定義をする

//影の構造体定義
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX g_mtxWorld;	//ワールドマトリックス
	bool bUse;						//使用しているどうか
}Shadow;


//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nIdxShadow,D3DXVECTOR3 pos);
void TrushShadow(int nIdxShadow);

#endif
