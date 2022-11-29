//======================================
//
//�Ǖ\������
//Author:�����V����	[wall.cpp]
//
//=====================================
#include"main.h"
#include"wall.h"
#include"input.h"
#include"model.h"
#include"player.h"

//�}�N����`
#define WALL_SIZE	(2000.0f)	//�ǂ̃T�C�Y
#define NUM_WALL	(4)			//�ǂ̌�

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9	g_pTextureWall = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffWall = NULL;	//���_�̃o�b�t�@
WALL g_aWall[NUM_WALL];

//=========================================================================
//�ǂ̏���������
//=========================================================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);
	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����������������(Z�l���g�p����)
		g_aWall[nCntWall].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = (-WALL_SIZE);
		pVtx[1].pos.x = (+WALL_SIZE * 2);
		pVtx[2].pos.x = (-WALL_SIZE);
		pVtx[3].pos.x = (+WALL_SIZE * 2);

		pVtx[0].pos.y = (+WALL_SIZE * 2);
		pVtx[1].pos.y = (+WALL_SIZE * 2);
		pVtx[2].pos.y = (+0.0f);
		pVtx[3].pos.y = (+0.0f);

		pVtx[0].pos.z = (0.0f);
		pVtx[1].pos.z = (0.0f);
		pVtx[2].pos.z = (0.0f);
		pVtx[3].pos.z = (0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();

	//--------------------------------------
	//�ǂ̐ݒu
	//--------------------------------------
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), 0);		//�O
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), 1);		//���
	SetWall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), 2);		//��
	SetWall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), 3);		//�E
}

//===================================
//�ǂ̏I������
//===================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̏���
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//===================================
//�ǂ̍X�V����
//===================================
void UpdateWall(void)
{
	VERTEX_3D *pVtx;
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			switch (g_aWall[nCntWall].nType)
			{
			case 0://�O
				//���_���W�̐ݒ�
				pVtx[0].pos.x = (-WALL_SIZE);
				pVtx[1].pos.x = (+WALL_SIZE);
				pVtx[2].pos.x = (-WALL_SIZE);
				pVtx[3].pos.x = (+WALL_SIZE);

				pVtx[0].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[1].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+0.0f);
				pVtx[3].pos.y = (+0.0f);

				pVtx[0].pos.z = (+0.0f);
				pVtx[1].pos.z = (+0.0f);
				pVtx[2].pos.z = (+0.0f);
				pVtx[3].pos.z = (+0.0f);
				break;

			case 1://���
				//���_���W�̐ݒ�
				pVtx[0].pos.x = (-WALL_SIZE);
				pVtx[1].pos.x = (+WALL_SIZE);
				pVtx[2].pos.x = (-WALL_SIZE);
				pVtx[3].pos.x = (+WALL_SIZE);

				pVtx[0].pos.y = (+0.0f);
				pVtx[1].pos.y = (+0.0f);
				pVtx[2].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[3].pos.y = (+WALL_SIZE * 0.5f);

				pVtx[0].pos.z = (+0.0f);
				pVtx[1].pos.z = (+0.0f);
				pVtx[2].pos.z = (+0.0f);
				pVtx[3].pos.z = (+0.0f);
				break;

			case 2://��
				//���_���W�̐ݒ�
				pVtx[0].pos.x = (-0.0f);
				pVtx[1].pos.x = (+0.0f);
				pVtx[2].pos.x = (-0.0f);
				pVtx[3].pos.x = (+0.0f);

				pVtx[0].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[1].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+0.0f);
				pVtx[3].pos.y = (+0.0f);

				pVtx[0].pos.z = (-WALL_SIZE);
				pVtx[1].pos.z = (+WALL_SIZE);
				pVtx[2].pos.z = (-WALL_SIZE);
				pVtx[3].pos.z = (+WALL_SIZE);
				break;

			case 3://�E
				//���_���W�̐ݒ�
				pVtx[0].pos.x = (-0.0f);
				pVtx[1].pos.x = (+0.0f);
				pVtx[2].pos.x = (-0.0f);
				pVtx[3].pos.x = (+0.0f);

				pVtx[0].pos.y = (+0.0f);
				pVtx[1].pos.y = (+0.0f);
				pVtx[3].pos.y = (+WALL_SIZE * 0.5f);
				pVtx[2].pos.y = (+WALL_SIZE * 0.5f);

				pVtx[0].pos.z = (-WALL_SIZE);
				pVtx[1].pos.z = (+WALL_SIZE);
				pVtx[2].pos.z = (-WALL_SIZE);
				pVtx[3].pos.z = (+WALL_SIZE);
				break;
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//====================================
//�ǂ̕`�揈��
//====================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p�}�g���b�N�X
	int nCntWall;

	for (nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aWall[nCntWall].g_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorld, &g_aWall[nCntWall].g_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
		D3DXMatrixMultiply(&g_aWall[nCntWall].g_mtxWorld, &g_aWall[nCntWall].g_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].g_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�ǂ̕`�揈��
		pDevice->SetTexture(0, g_pTextureWall);

		//�ǂ̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * NUM_WALL, 2);		//�v���~�e�B�u�̎��
	}
}

//====================================
//�ǂ̐ݒ菈��
//====================================
void SetWall(D3DXVECTOR3 pos,int nType)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{//�G���g�p����Ȃ�
			g_aWall [nCntWall].pos = pos;
			g_aWall[nCntWall].nType = nType;
			g_aWall[nCntWall].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = (-WALL_SIZE);
			pVtx[1].pos.x = (+WALL_SIZE * 2);
			pVtx[2].pos.x = (-WALL_SIZE);
			pVtx[3].pos.x = (+WALL_SIZE * 2);

			pVtx[0].pos.y = (+WALL_SIZE * 2);
			pVtx[1].pos.y = (+WALL_SIZE * 2);
			pVtx[2].pos.y = (+0.0f);
			pVtx[3].pos.y = (+0.0f);

			pVtx[0].pos.z = (0);
			pVtx[1].pos.z = (0);
			pVtx[2].pos.z = (0);
			pVtx[3].pos.z = (0);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//====================================
//�ǂ̎擾����
//====================================
WALL *GetWall(void)
{
	return &g_aWall[NUM_WALL];
}

