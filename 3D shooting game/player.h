//======================================
//
//�v���C���[����
//Author:�����V����	[player.h]
//
//=====================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXVECTOR3 move;				//�ړ���
	D3DXMATRIX g_mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxShadow;				//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
}Player;

//�v���g�^�C�v�錾
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
Player *GetPlayer(void);
#endif

