//======================================
//
//���b�V���V�����_�[����
//Author:�����V����	[meshsylinder.h]
//
//=====================================
#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX g_mtxWorld;			//���[���h�}�g���b�N�X
}MeshCylinder;

//�v���g�^�C�v�錾
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);

#endif
