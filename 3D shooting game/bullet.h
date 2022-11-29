//======================================
//
//玉の発射処理
//Author:日野澤匠泉	[bullet.h]
//
//=====================================

#ifndef _BULLET_H_
#define _BULLET_H_

#include"main.h"

//弾の種類の列挙型
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//プレイヤーの弾
	BULLETTYPE_ENEMY,
	BULLETTYPE_ENEMY_HOMING,
	BULLETTYPE_MAX
}BULLETTYPE;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type);

#endif