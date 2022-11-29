//======================================
//
//�|���S���\������
//Author:�����V����	[polygon.cpp]
//
//=====================================
#include"main.h"
#include"Polygon.h"
#include"input.h"

//�}�N����`
#define POLYGON_SIZE (2000.0f)		//�|���S���T�C�Y
//�O���[�o���ϐ��錾
LPDIRECT3DTEXTURE9	g_pTexturePolygon = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPolygon = NULL;	//���_�̃o�b�t�@
D3DXVECTOR3 g_posPolygon;		//�ʒu
D3DXVECTOR3 g_movePolygon;		//�ړ�
D3DXVECTOR3 g_rotPolygon;		//����
D3DXMATRIX g_mtxWorldPolygon;	//���[���h�}�g���b�N�X

//=========================================================================
//�|���S���̏���������
//=========================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tnt000.png",
		&g_pTexturePolygon);

	//�e��ϐ�������
	g_posPolygon = D3DXVECTOR3(0.0f,0.0f, 0.0f);		//�ʒu�̏�����
	g_rotPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);			//����������������(Z�l���g�p����)
	g_movePolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʏ�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = (-POLYGON_SIZE);
	pVtx[1].pos.x = (+POLYGON_SIZE);
	pVtx[2].pos.x = (-POLYGON_SIZE);
	pVtx[3].pos.x = (+POLYGON_SIZE);

	pVtx[0].pos.y = (+ 0.0f);
	pVtx[1].pos.y = (+ 0.0f);
	pVtx[2].pos.y = (+ 0.0f);
	pVtx[3].pos.y = (+ 0.0f);

	pVtx[0].pos.z = (+POLYGON_SIZE);
	pVtx[1].pos.z = (+POLYGON_SIZE);
	pVtx[2].pos.z = (-POLYGON_SIZE);
	pVtx[3].pos.z = (-POLYGON_SIZE);
	
	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();

}

//===================================
//�|���S���̏I������
//===================================
void UninitPolygon(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}

	//���_�o�b�t�@�̏���
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}

}

//===================================
//�|���S���̍X�V����
//===================================
void UpdatePolygon(void)
{
	
}

//====================================
//�|���S���̕`�揈��
//====================================
void DrawPolygon(void)
{

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,g_rotPolygon.y,g_rotPolygon.x,g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon,&g_mtxWorldPolygon,&mtxRot);
	
	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD,&g_mtxWorldPolygon);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`�揈��
	pDevice->SetTexture(0, g_pTexturePolygon);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		//�v���~�e�B�u�̎��
}