//======================================
//
//�J��������
//Author:�����V����	[camera.h]
//
//=====================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"main.h"

//�J�����̍\���̒�`
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 posU;			//������x�N�g��
	D3DXVECTOR3 posVDest;		//�ړI�̎��_
	D3DXVECTOR3 posRDest;		//�ړI�̒����_
	D3DXVECTOR3 move;			//�ړ��l
	D3DXVECTOR3 rot;			//����
	D3DXVECTOR3 rotDest;		//�ڕW�̊p�x
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
}Camera;

//�v���g�^�C�v�錾
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void SetCamera(void);
void RotCamera(void);
Camera *GetCamera(void);

#endif
