//======================================
//
//�Ǖ\������
//Author:�����V����	[wall.h]
//
//=====================================

#ifndef _WALL_H_	//���̒�`������Ă��Ȃ�������
#define _WALL_H_	//��d�C���N���[�h�h�~�̃}�N����`������

//�ǂ̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos;			//���݂̈ʒu
	D3DXVECTOR3 rot;			//����
	D3DXMATRIX g_mtxWorld;		//���[���h�}�g���b�N�X
	bool bUse;					//�g�p���Ă��邩�ǂ���
	int nType;					//�ǂ̎��
}WALL;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos,int nType);
WALL *GetWall(void);

#endif
