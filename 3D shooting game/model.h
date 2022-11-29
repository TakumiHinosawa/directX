//======================================
//
//���f������
//Author:�����V����	[model.h]
//
//=====================================
#ifndef _MODEL_H_
#define _MODEL_H_

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;								//�ʒu
	D3DXVECTOR3 rot;								//����
	D3DXVECTOR3 move;								//�ړ���
	D3DXVECTOR3 vtxMax;								//���f���̍ő�l
	D3DXVECTOR3 vtxMIN;								//���f���̍ŏ��l
	D3DXMATRIX mtxWorld;							//���[���h�}�g���b�N�X
	LPD3DXMESH Mesh;								//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER BuffMat;							//�}�e���A���̃|�C���^
	LPDIRECT3DTEXTURE9 apTexture[20] = {};		//�e�N�X�`���ւ̃|�C���^
	DWORD dwNumMat;									//�}�e���A���̐�
	int nIdxShadow;									//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	bool bUse;										//�g�p���Ă��邩�ǂ���
	int nType;										//���f���̃^�C�v
}Model;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);
void SetModel(D3DXVECTOR3 pos, int nType);
#endif
