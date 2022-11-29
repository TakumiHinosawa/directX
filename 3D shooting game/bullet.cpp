//==========================================================================
//
//�ʂ̔��ˏ���
//Author:�����V����
//
//=========================================================================

#include"bullet.h"
#include"main.h"
#include"input.h"
#include"wall.h"
#include"explosion.h"
#include"shadow.h"
#include"effect.h"

//�}�N����`
#define MAX_BULLET		(128)		//�e�̍ő吔
#define SIZE			(10)		//�e�̃T�C�Y
#define WALL_SIZE	(200.0f)	//�ǂ̃T�C�Y

//�e�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXMATRIX g_mtxWorldBullet;		//���[���h�}�g���b�N�X
	BULLETTYPE type;
	int nIdxShadow = -1;				//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)
	int nLife;
	bool bUse;

}Bullet;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�̃o�b�t�@
Bullet g_aBullet[MAX_BULLET];		//�e�̏��

//============================================================================
//�e�̏���������
//============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\ball09_orange.png",
		&g_pTextureBullet);

	//�e�̏��̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 20;
		g_aBullet[nCntBullet].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
		g_aBullet[nCntBullet].nIdxShadow = -1;
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
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

		pVtx[0].pos.z = (0.0f);
		pVtx[1].pos.z = (0.0f);
		pVtx[2].pos.z = (0.0f);
		pVtx[3].pos.z = (0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//=======================================================================
//�e�̏I������
//=======================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=======================================================================
//�e�̍X�V����
//=======================================================================
void UpdateBullet(void)
{
	int nCntBullet;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p�����

			//�e�̈ʒu��ݒ�
 			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			//�G�t�F�N�g�X�V
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 14, 8);

			//�e�̈ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//���������炷����
			g_aBullet[nCntBullet].nLife--;

			//�����̃J�E���g�_�E��
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
 				SetExplosion(g_aBullet[nCntBullet].pos, D3DCOLOR_RGBA(255, 255, 255, 255));
				TrushShadow(g_aBullet[nCntBullet].nIdxShadow);
				g_aBullet[nCntBullet].bUse = false;			//�g�p���Ă��Ȃ���Ԃɂ���	
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBullet->Unlock();
		}
		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}
}

//========================================================================
//�e�̕`�揈��
//========================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X�擾�p
	int nCntBullet;

	//�A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p���ꂽ

		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].g_mtxWorldBullet);

		//�r���[�}�g���b�N�X���擾
		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
		D3DXMatrixInverse(&g_aBullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);		//�t�s������߂�
		g_aBullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
		g_aBullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
		g_aBullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].g_mtxWorldBullet, &g_aBullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].g_mtxWorldBullet);

		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�|���S���̕`�揈��
		pDevice->SetTexture(0, g_pTextureBullet);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);		//�v���~�e�B�u�̎��
		}
	}
	//�A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
}

//========================================================================
//�e�̐ݒ菈��
//========================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE type)
{
	int nCntBullet;
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g�p����Ȃ�
			g_aBullet[nCntBullet].pos = pos;
			g_aBullet[nCntBullet].type = type;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 20;
			g_aBullet[nCntBullet].bUse = true;
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			break;
		}
		pVtx += 4;		//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
