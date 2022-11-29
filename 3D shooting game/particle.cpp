//======================================
//
//�p�[�e�B�N������
//Author:�����V����	[particle.cpp]
//
//=====================================
#include"particle.h"
#include"effect.h"

//�}�N����`
#define MAX_PARTICLE	(128)		//�p�[�e�B�N���ő吔
#define SIZE			(20)		//�p�[�e�B�N���T�C�Y

//�p�[�e�B�N���̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 rot;		//����
	int nLife;				//����
	int nType;				//���
	bool bUse;				//�g�p���Ă��邩�ǂ���
	D3DXMATRIX g_mtxWorld;	//���[���h�}�g���b�N�X
}Particle;

//�O���[�o���ϐ��錾
Particle g_aParticle[MAX_PARTICLE];
LPDIRECT3DTEXTURE9 g_pTextureParticle = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	//���_�o�b�t�@�ւ̃|�C���^

//=========================================================================
//�p�[�e�B�N���̏���������
//=========================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.jpg",
		&g_pTextureParticle);

	//�p�[�e�B�N���̏��̏�����
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt)
	{
		g_aParticle[MAX_PARTICLE].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[MAX_PARTICLE].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[MAX_PARTICLE].nLife = 20;
		g_aParticle[MAX_PARTICLE].bUse = false;
		g_aParticle[MAX_PARTICLE].nType = 0;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_PARTICLE; nCntEffect++)
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
	g_pVtxBuffParticle->Unlock();
}

//=========================================================================
//�p�[�e�B�N���̏I������
//=========================================================================
void UninitParticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}
}

//=========================================================================
//�p�[�e�B�N���̍X�V����
//=========================================================================
void UpdateParticle(void)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//�p�[�e�B�N���̍쐬
			for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
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

				//�p�[�e�B�N���̋���
				g_aParticle[nCnt].nLife--;

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

				SetEffect(g_aParticle[nCnt].pos, D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),SIZE,g_aParticle[nCnt].nLife);
			}
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//=========================================================================
//�p�[�e�B�N���̕`�揈��
//=========================================================================
void DrawParticle(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();;
	D3DXMATRIX mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X�擾�p
	int nCnt;

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

	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aParticle[nCnt].g_mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_aParticle[nCnt].g_mtxWorld, NULL, &mtxView);		//�t�s������߂�
			g_aParticle[nCnt].g_mtxWorld._41 = 0.0f;
			g_aParticle[nCnt].g_mtxWorld._42 = 0.0f;
			g_aParticle[nCnt].g_mtxWorld._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCnt].pos.x, g_aParticle[nCnt].pos.y, g_aParticle[nCnt].pos.z);
			D3DXMatrixMultiply(&g_aParticle[nCnt].g_mtxWorld, &g_aParticle[nCnt].g_mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCnt].g_mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�|���S���̕`�揈��
			pDevice->SetTexture(0, g_pTextureParticle);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);		//�v���~�e�B�u�̎��
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

//=========================================================================
//�p�[�e�B�N���̐ݒ菈��
//=========================================================================
void SetParticle(D3DXVECTOR3 pos,int nType)
{
	int nCnt;
	VERTEX_3D *pVtx = 0;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].nType = nType;
			g_aParticle[nCnt].bUse = true;

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
	g_pVtxBuffParticle->Unlock();
}