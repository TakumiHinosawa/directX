//======================================
//
//パーティクル処理
//Author:日野澤匠泉	[particle.h]
//
//=====================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include"main.h"

//プロトタイプ宣言
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, int nType);

#endif
