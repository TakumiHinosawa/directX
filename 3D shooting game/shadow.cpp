//======================================
//
//�e�\������
//Author:�����V����	[shadow.cpp]
//
//=====================================
#include"main.h"
#include"shadow.h"
#include"input.h"

//�}�N����`
#define SHADOW_SIZE	(30.0f)			//�e�̃T�C�Y
#define SHADOW_MAX	(128)			//�e�̍ő吔

//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9	g_pTextureShadow = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffShadow = NULL;	//���_�̃o�b�t�@
Shadow g_aShadow[SHADOW_MAX];	//�e�̏��

//=========================================================================
//�e�̏���������
//=========================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		//�e��ϐ�������
		g_aShadow[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aShadow[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����������������(Z�l���g�p����)
		g_aShadow[nCnt].bUse = false;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * SHADOW_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = (-SHADOW_SIZE);
		pVtx[1].pos.x = (+SHADOW_SIZE);
		pVtx[2].pos.x = (-SHADOW_SIZE);
		pVtx[3].pos.x = (+SHADOW_SIZE);

		pVtx[0].pos.y = (+0.0f);
		pVtx[1].pos.y = (+0.0f);
		pVtx[2].pos.y = (+0.0f);
		pVtx[3].pos.y = (+0.0f);

		pVtx[0].pos.z = (+SHADOW_SIZE);
		pVtx[1].pos.z = (+SHADOW_SIZE);
		pVtx[2].pos.z = (-SHADOW_SIZE);
		pVtx[3].pos.z = (-SHADOW_SIZE);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();

}

//===================================
//�e�̏I������
//===================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̏���
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//===================================
//�e�̍X�V����
//===================================
void UpdateShadow(void)
{

}

//====================================
//�e�̕`�揈��
//====================================
void DrawShadow(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aShadow[nCnt].g_mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aShadow[nCnt].rot.y, g_aShadow[nCnt].rot.x,  g_aShadow[nCnt].rot.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].g_mtxWorld, &g_aShadow[nCnt].g_mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aShadow[nCnt].pos.x, g_aShadow[nCnt].pos.y, g_aShadow[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aShadow[nCnt].g_mtxWorld, &g_aShadow[nCnt].g_mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aShadow[nCnt].g_mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`�揈��
			pDevice->SetTexture(0, g_pTextureShadow);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCnt, 2);		//�v���~�e�B�u�̎��
		}
	}

	//�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//====================================
//�e�̐ݒ菈��
//====================================
int SetShadow(void)
{
	int nCntShadow = -1;

	for (int nCnt = 0; nCnt < SHADOW_MAX; nCnt++)
	{
		if (g_aShadow[nCnt].bUse == false)
		{//�g���Ă��Ȃ������Ƃ�
			nCntShadow = nCnt;
			g_aShadow[nCnt].bUse = true;
			break;
		}
	}

	return nCntShadow;
}

//====================================
//�e�̐ݒ菈��
//====================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	g_aShadow[nIdxShadow].pos.x = pos.x;
	g_aShadow[nIdxShadow].pos.z = pos.z;
}

//====================================
//�e�̍폜����
//====================================
void TrushShadow(int nIdxShadow)
{
	g_aShadow[nIdxShadow].bUse = false;
}
