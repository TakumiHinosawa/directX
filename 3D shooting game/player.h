//======================================
//
//プレイヤー処理
//Author:日野澤匠泉	[player.h]
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;				//位置
	D3DXVECTOR3 rot;				//向き
	D3DXVECTOR3 move;				//移動量
	D3DXMATRIX g_mtxWorld;			//ワールドマトリックス
	int nIdxShadow;				//対象の影のインデックス(番号)
}Player;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
#endif

