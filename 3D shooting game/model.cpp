//======================================
//
//���f���\������
//Author:�����V����	[model.cpp]
//
//=====================================
#include"main.h"
#include"model.h"
#include"input.h"
#include"shadow.h"

//�}�N����`
#define MOVE	(0.8f)		//�ړ���
#define MAX_TEX	(32)		//�e�N�X�`���ő吔
#define TIMING	(20)		//�e���˂̑��x
#define BULLETSPEED	(10.0f)	//�e�̑��x
#define MAX_MODEL	(2)		//���f���̍ő吔

//�O���[�o���ϐ��錾
Model g_aModel[MAX_MODEL];	//���f���̏��

//=========================================================================
//���f���̏���������
//=========================================================================
void InitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//�e��ϐ�������
		g_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aModel[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����������������(Z�l���g�p����)
		g_aModel[nCnt].nIdxShadow = -1;							//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)������
		g_aModel[nCnt].Mesh = {};			//���b�V��(���_���)�ւ̃|�C���^
		g_aModel[nCnt].BuffMat = {};		//�}�e���A���̃|�C���^
		g_aModel[nCnt].dwNumMat = 0;		//�}�e���A���̐�
	}

	//-------------------------
	// SetModel
	//-------------------------
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 0.0f), 0);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 100.0f), 1);
}

//===================================
//���f���̏I������
//===================================
void UninitModel(void)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		//���b�V���̔j��
		if (g_aModel[nCnt].Mesh != NULL)
		{
			g_aModel[nCnt].Mesh->Release();
			g_aModel[nCnt].Mesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aModel[nCnt].BuffMat != NULL)
		{
			g_aModel[nCnt].BuffMat->Release();
			g_aModel[nCnt].BuffMat = NULL;
		}
	}
}

//===================================
//���f���̍X�V����
//===================================
void UpdateModel(void)
{

}

//====================================
//���f���̕`�揈��
//====================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{//�g�p����Ă��Ȃ���
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aModel[nCnt].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aModel[nCnt].rot.y, g_aModel[nCnt].rot.x, g_aModel[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aModel[nCnt].pos.x, g_aModel[nCnt].pos.y, g_aModel[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aModel[nCnt].mtxWorld, &g_aModel[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aModel[nCnt].mtxWorld);

			//���݂̃}�e���A�����擾
			pDevice->GetMaterial(&matDef);

			//�}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
			{
				//�}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_aModel[nCnt].apTexture[nCntMat]);

				//���f��(�p�[�c)�̕`��
				g_aModel[nCnt].Mesh->DrawSubset(nCntMat);
			}
			//�ۑ����Ă����}�e���A����߂�
			pDevice->SetMaterial(&matDef);
		}
	}
}

//====================================
//���f���̐ݒ菈��
//====================================
Model *GetModel(void)
{
	return &g_aModel[0];
}

//====================================
//���f���̔z�u����
//====================================
void SetModel(D3DXVECTOR3 pos, int nType)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�ւ̃|�C���^
	int nNumVtx;				//���_��
	DWORD dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�̃|�C���^

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (g_aModel[nCnt].bUse == false)
		{//�g�p����Ă��Ȃ���
			nType = g_aModel[nCnt].nType;

			switch (g_aModel[nCnt].nType)
			{
			case 0:
				//X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX("data\\MODEL\\switch.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_aModel[nCnt].BuffMat,
					NULL,
					&g_aModel[nCnt].dwNumMat,
					&g_aModel[nCnt].Mesh);

				//���_�����擾
				nNumVtx = g_aModel[nCnt].Mesh->GetNumVertices();

				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				dwSizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].Mesh->GetFVF());

				//���_�o�b�t�@�����b�N
				g_aModel[nCnt].Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);		//���_���W�̑��

				//�}�e���A�����ɑ΂���|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{//�e�N�X�`���t�@�C�������݂���

					 //�e�N�X�`���̓ǂݍ���
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_aModel[nCntMat].apTexture[nCntMat]);
					}
				}

				//�e��ݒ�
				g_aModel[nCnt].nIdxShadow = SetShadow();

			case 1:
				//X�t�@�C���̓ǂݍ���
				D3DXLoadMeshFromX("data\\MODEL\\switch.x",
					D3DXMESH_SYSTEMMEM,
					pDevice,
					NULL,
					&g_aModel[nCnt].BuffMat,
					NULL,
					&g_aModel[nCnt].dwNumMat,
					&g_aModel[nCnt].Mesh);

				//���_�����擾
				nNumVtx = g_aModel[nCnt].Mesh->GetNumVertices();

				//���_�t�H�[�}�b�g�̃T�C�Y���擾
				dwSizeFVF = D3DXGetFVFVertexSize(g_aModel[nCnt].Mesh->GetFVF());

				//���_�o�b�t�@�����b�N
				g_aModel[nCnt].Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);		//���_���W�̑��

				//�}�e���A�����ɑ΂���|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aModel[nCnt].BuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)g_aModel[nCnt].dwNumMat; nCntMat++)
				{
					if (pMat[nCntMat].pTextureFilename != NULL)
					{//�e�N�X�`���t�@�C�������݂���

						//�e�N�X�`���̓ǂݍ���
						D3DXCreateTextureFromFile(pDevice,
							pMat[nCntMat].pTextureFilename,
							&g_aModel[nCnt].apTexture[nCntMat]);
					}
				}
				//�e��ݒ�
				g_aModel[nCnt].nIdxShadow = SetShadow();
			}
		}
	}
}

