//======================================
//
//�v���C���[����
//Author:�����V����	[model.cpp]
//
//=====================================
#include"main.h"
#include"player.h"
#include"input.h"
#include"camera.h"
#include"shadow.h"
#include"bullet.h"
#include"wall.h"

//�}�N����`
#define MOVE	(0.8f)	//�ړ���
#define MAX_TEX	(32)	//�e�N�X�`���ő吔
#define TIMING	(20)	//�e���˂̑��x
#define BULLETSPEED	(10.0f)

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshPlayer = NULL;			//���b�V��(���_���)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;	//�}�e���A���̃|�C���^
LPDIRECT3DTEXTURE9 g_apTexturePlayer[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;				//�}�e���A���̐�
int g_nCounter;
Player g_Player;	//���f���̏��
bool b_camera;	//�J�����Ǐ]�I���I�t

//=========================================================================
//�v���C���[�̏���������
//=========================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	//�e��ϐ�������
	g_Player.pos = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//�ʒu�̏�����
	g_Player.rot = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//����������������(Z�l���g�p����)
	g_Player.nIdxShadow = -1;								//�Ώۂ̉e�̃C���f�b�N�X(�ԍ�)������
	b_camera = false;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\trueno.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{//�e�N�X�`���t�@�C�������݂���

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}
	//�e��ݒ�
	g_Player.nIdxShadow = SetShadow();
}

//===================================
//�v���C���[�̏I������
//===================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//===================================
//�v���C���[�̍X�V����
//===================================
void UpdatePlayer(void)
{
	//�J�������擾
	Camera *pCamera = GetCamera();
	float fRotMove = g_Player.rot.y;	//���݂̌���
	float fRotDest = g_Player.rot.y;	//�s����������
	float fRotDiff = g_Player.rot.y;	//�ړI�̕���

	//-------------------------------------------------
	//�L�[�{�[�h����
	//-------------------------------------------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{//���������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_UP) == true)
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.25f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.75f);
		}
		else
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * MOVE;
			fRotDest = pCamera->rot.y - (D3DX_PI * 0.5f);
		}
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{//���������ꂽ�Ƃ�
		if (GetKeyboardPress(DIK_UP) == true)
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.25f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.25f);
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.75f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.75f);
		}
		else
		{//��
			g_Player.move.x += sinf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * MOVE;
			g_Player.move.z += cosf(pCamera->rot.y - (-D3DX_PI * 0.5f)) * MOVE;
			fRotDest = pCamera->rot.y - (-D3DX_PI * 0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{//��ړ�
		g_Player.move.x += sinf(pCamera->rot.y) * MOVE;
		g_Player.move.z += cosf(pCamera->rot.y) * MOVE;
		fRotDest = pCamera->rot.y;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{//���ړ�
		g_Player.move.x -= sinf(pCamera->rot.y) * MOVE;
		g_Player.move.z -= cosf(pCamera->rot.y) * MOVE;
		fRotDest = pCamera->rot.y + D3DX_PI;
	}

	if (GetKeyboardPress(DIK_I) == true)
	{//�㏸
		g_Player.move.y += MOVE;
	}
	if (GetKeyboardPress(DIK_K) == true)
	{//���~
		g_Player.move.y -= MOVE;
	}
	if (GetKeyboardPress(DIK_RETURN) == true)
	{//�|���S���ʒu���Z�b�g
		g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
	}
	if (GetKeyboardPress(DIK_SPACE) == true/* && g_nCounter >= TIMING*/)
	{//SPACE�L�[�������ꂽ
		SetBullet(g_Player.pos, D3DXVECTOR3(sinf(g_Player.rot.y) * BULLETSPEED, 0.0f, cosf(g_Player.rot.y) * BULLETSPEED), 20, BULLETTYPE_PLAYER);
		g_nCounter = 0;
	}

	//�ړ��ʑ��
	g_Player.pos += g_Player.move;

	//�e�̈ʒu��ݒ�
	SetPositionShadow(g_Player.nIdxShadow, g_Player.pos);

	//�ړ��ʂ��X�V(����������)
	g_Player.move.x += (0.0f - g_Player.move.x) * 0.12f;
	g_Player.move.y += (0.0f - g_Player.move.y) * 0.12f;
	g_Player.move.z += (0.0f - g_Player.move.z) * 0.12f;

	if (b_camera == false)
	{
		//�ړ��ʂ��[���ɋ߂Â����Ƃ�
		if (g_Player.move.x <= 0.01f && g_Player.move.x >= -0.01f)
		{
			if (g_Player.move.z <= 0.01f && g_Player.move.z >= -0.01f)
			{
				RotCamera();
			}
		}
	}
	if (GetKeyboardPress(DIK_F1) == true)
	{//F1�������ꂽ��Ǐ]�I��
		b_camera = true;
	}
	else if (GetKeyboardPress(DIK_F2) == true)
	{//F2�������ꂽ��Ǐ]�J�n
		b_camera = false;
	}

	//�p�x�Z�o
	fRotDiff = fRotDest - fRotMove;		//�ڕW�̈ړ������܂ł̍���

	//�ړ������̕␳
	if (fRotDiff > D3DX_PI || fRotDiff < -D3DX_PI)
	{
		if (fRotDiff > D3DX_PI)
		{
			fRotDiff += -D3DX_PI * 2;
		}
		else if (fRotDiff < -D3DX_PI)
		{
			fRotDiff += D3DX_PI * 2;
		}
	}

	g_Player.rot.y += fRotDiff * 0.1f;

	//�ړ������̕␳
	if (g_Player.rot.y > D3DX_PI || g_Player.rot.y < -D3DX_PI)
	{
		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y += -D3DX_PI * 2;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2;
		}
	}
	g_nCounter++;

	//���̔���
	if (g_Player.pos.y <= 0.0f)
	{
		g_Player.pos.y = 0.0f;
	}

	//�ǂ̔���
	if (g_Player.pos.z >= 2000.0f)
	{
		g_Player.pos.z = 2000.0f;
	}
	if (g_Player.pos.z <= -2000.0f)
	{
		g_Player.pos.z = -2000.0f;
	}
	if (g_Player.pos.x <= -2000.0f)
	{
		g_Player.pos.x = -2000.0f;
	}
	if (g_Player.pos.x >= 2000.0f)
	{
		g_Player.pos.x = 2000.0f;
	}
}

//====================================
//�v���C���[�̕`�揈��
//====================================
void DrawPlayer(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		//�f�o�C�X�̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;					//�v�Z�p
	D3DMATERIAL9 matDef;		//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;			//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.g_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.g_mtxWorld, &g_Player.g_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.g_mtxWorld, &g_Player.g_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.g_mtxWorld);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}
	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//====================================
//�v���C���[�̐ݒ菈��
//====================================
Player *GetPlayer(void)
{
	return &g_Player;
}
