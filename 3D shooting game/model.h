//======================================
//
//モデル処理
//Author:日野澤匠泉	[model.h]
//
//=====================================
#ifndef _MODEL_H_
#define _MODEL_H_

//モデル構造体
typedef struct
{
	D3DXVECTOR3 pos;								//位置
	D3DXVECTOR3 rot;								//向き
	D3DXVECTOR3 move;								//移動量
	D3DXVECTOR3 vtxMax;								//モデルの最大値
	D3DXVECTOR3 vtxMIN;								//モデルの最小値
	D3DXMATRIX mtxWorld;							//ワールドマトリックス
	LPD3DXMESH Mesh;								//メッシュ(頂点情報)へのポインタ
	LPD3DXBUFFER BuffMat;							//マテリアルのポインタ
	LPDIRECT3DTEXTURE9 apTexture[20] = {};		//テクスチャへのポインタ
	DWORD dwNumMat;									//マテリアルの数
	int nIdxShadow;									//対象の影のインデックス(番号)
	bool bUse;										//使用しているかどうか
	int nType;										//モデルのタイプ
}Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
#endif
