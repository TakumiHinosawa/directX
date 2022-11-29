//==========================================
//
// �G�t�F�N�g���� [effect.cpp]
//	Author:�����V����
//
//==========================================

#include"effect.h"

//�}�N����`
#define MAX_EFFECT		(512)		//�G�t�F�N�g�̍ő吔
#define SIZE			(10)		//�G�t�F�N�g�̃T�C�Y

//�G�t�F�N�g�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXCOLOR col;		//�J���[
	float fRadius;		//���a
	int nLife;			//����
	bool bUse;			//�g�p���Ă��邩�ǂ���
	D3DXMATRIX g_mtxWorld;		//���[���h�}�g���b�N�X
}Effect;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Effect g_aEffect[MAX_EFFECT];						//�G�t�F�N�g�̏��

//========================================
//�G�t�F�N�g�̏���������
//========================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureEffect);

	//�G�t�F�N�g�̏��̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].fRadius = 10;
		g_aEffect[nCntEffect].nLife = 20;
		g_aEffect[nCntEffect].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
 	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos.x = (-SIZE);
		pVtx[1].pos.x = (+SIZE);
		pVtx[2].pos.x = (-SIZE);
		pVtx[3].pos.x = (+SIZE);

		pVtx[0].pos.y = (+SIZE);
		pVtx[1].pos.y = (+SIZE);
		pVtx[2].pos.y = (-SIZE);
		pVtx[3].pos.y = (-SIZE);

		pVtx[0].pos.z = (0);
		pVtx[1].pos.z = (0);
		pVtx[2].pos.z = (0);
		pVtx[3].pos.z = (0);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//========================================
//�G�t�F�N�g�̏I������
//========================================
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//========================================
//�G�t�F�N�g�̍X�V����
//========================================
void UpdateEffect(void)
{
	int nCntEffect;
	VERTEX_3D *pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g�p�����
			
			//�G�t�F�N�g����
			g_aEffect[nCntEffect].nLife--;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = (-SIZE);
			pVtx[1].pos.x = (+SIZE);
			pVtx[2].pos.x = (-SIZE);
			pVtx[3].pos.x = (+SIZE);

			pVtx[0].pos.y = (+SIZE);
			pVtx[1].pos.y = (+SIZE);
			pVtx[2].pos.y = (-SIZE);
			pVtx[3].pos.y = (-SIZE);

			pVtx[0].pos.z = (0);
			pVtx[1].pos.z = (0);
			pVtx[2].pos.z = (0);
			pVtx[3].pos.z = (0);

			if (g_aEffect[nCntEffect].nLife <= 0)
			{
				g_aEffect[nCntEffect].bUse = false;
			}

		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();

}

//========================================
//�G�t�F�N�g�̕`�揈��
//========================================
void DrawEffect(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;
	D3DXMATRIX mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X�擾�p
	int nCntEffect;

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//a�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEffect[nCntEffect].g_mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aEffect[nCntEffect].g_mtxWorld, NULL, &mtxView);		//�t�s������߂�
			g_aEffect[nCntEffect].g_mtxWorld._41 = 0.0f;
			g_aEffect[nCntEffect].g_mtxWorld._42 = 0.0f;
			g_aEffect[nCntEffect].g_mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
			D3DXMatrixMultiply(&g_aEffect[nCntEffect].g_mtxWorld, &g_aEffect[nCntEffect].g_mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].g_mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`�揈��
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);		//�v���~�e�B�u�̎��
		}

	}

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	//a�u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//========================================
//�G�t�F�N�g�̐ݒ菈��
//========================================
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_3D *pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;
			g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].pos.x = (-SIZE);
			pVtx[1].pos.x = (+SIZE);
			pVtx[2].pos.x = (-SIZE);
			pVtx[3].pos.x = (+SIZE);

			pVtx[0].pos.y = (+SIZE);
			pVtx[1].pos.y = (+SIZE);
			pVtx[2].pos.y = (-SIZE);
			pVtx[3].pos.y = (-SIZE);

			pVtx[0].pos.z = (0);
			pVtx[1].pos.z = (0);
			pVtx[2].pos.z = (0);
			pVtx[3].pos.z = (0);

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}
