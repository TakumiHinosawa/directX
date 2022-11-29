//======================================
//
//�e�\������
//Author:�����V����	[shadow.h]
//
//=====================================

#ifndef _SHADOW_H_	//���̒�`������Ă��Ȃ�������
#define _SHADOW_H_	//��d�C���N���[�h�h�~�̃}�N����`������

//�e�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	D3DXMATRIX g_mtxWorld;	//���[���h�}�g���b�N�X
	bool bUse;						//�g�p���Ă���ǂ���
}Shadow;


//�v���g�^�C�v�錾
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nIdxShadow,D3DXVECTOR3 pos);
void TrushShadow(int nIdxShadow);

#endif
