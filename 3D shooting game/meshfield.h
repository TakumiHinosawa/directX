//======================================
//
//���b�V���t�B�[���h����
//Author:�����V����	[meshfield.h]
//
//=====================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//���f���\����
typedef struct
{
	D3DXVECTOR3 pos;				//�ʒu
	D3DXVECTOR3 rot;				//����
	D3DXMATRIX g_mtxWorld;			//���[���h�}�g���b�N�X
	int nIdxShadow;				//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
}MeshField;

//�v���g�^�C�v�錾
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
