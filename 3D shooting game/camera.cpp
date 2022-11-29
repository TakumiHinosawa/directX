//======================================
//
//�J��������
//Author:�����V����	[camera.cpp]
//
//=====================================
#include"camera.h"
#include"main.h"
#include"input.h"
#include"model.h"
#include"player.h"

//�}�N����`
#define MOVE	(0.25f)		//�ړ���
#define MOVES	(0.01f)		//�p�x�ړ���
#define DIS		(300.0f)	//����

//�O���[�o���ϐ��錾
Camera g_camera;

//================================================
//�J�����̏���������
//================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 80.0f,-300.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//================================================
//�J�����̏I������
//================================================
void UninitCamera(void)
{

}

//================================================
//�J�����̍X�V����
//================================================
void UpdateCamera(void)
{
	//-----------------------------------
	//�L�[�{�[�h����
	//-----------------------------------
	if (GetKeyboardPress(DIK_A) == true)
	{//���ړ�
		g_camera.move.x += sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * MOVE;
	}
	if (GetKeyboardPress(DIK_D) == true)
	{//�E�ړ�
		g_camera.move.x += sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * MOVE;
	}
	if (GetKeyboardPress(DIK_W) == true)
	{//��ړ�
		g_camera.move.x += sinf(g_camera.rot.y) * MOVE;
		g_camera.move.z += cosf(g_camera.rot.y) * MOVE;
	}
	if (GetKeyboardPress(DIK_S) == true)
	{//���ړ�
		g_camera.move.x -= sinf(g_camera.rot.y) * MOVE;
		g_camera.move.z -= cosf(g_camera.rot.y) * MOVE;
	}

	if (GetKeyboardPress(DIK_X) == true)
	{//Y���W��
		g_camera.move.y += MOVE;
	}
	if (GetKeyboardPress(DIK_Z) == true)
	{//Y���W��
		g_camera.move.y -= MOVE;
	}

	//-----------------------------------
	//			     ���_
	//-----------------------------------
	if (GetKeyboardPress(DIK_E) == true)
	{//�E��]
		g_camera.rot.y += MOVES;
	}
	if (GetKeyboardPress(DIK_Q) == true)
	{//����]
		g_camera.rot.y -= MOVES;
	}
	//�J������]
	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * DIS;		//���_���猩��rot�̕����ɂǂꂾ������Ă��邩
	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * DIS;

	if (GetKeyboardPress(DIK_1) == true)
	{//���_��]
		g_camera.rot.y += MOVES;
	}
	if (GetKeyboardPress(DIK_3) == true)
	{//���_��]
		g_camera.rot.y -= MOVES;
	}
	//�J������]
	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -DIS;	//�����_���猩��rot�̕����ɂǂꂾ������Ă��邩
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -DIS;

	if (GetKeyboardPress(DIK_T) == true)
	{//�������
		g_camera.posR.y += MOVE;
	}
	if (GetKeyboardPress(DIK_G) == true)
	{//��������
		g_camera.posR.y -= MOVE;
	}

	//�ړ��ʑ��
	g_camera.posV += g_camera.move;
	g_camera.posR += g_camera.move;

	//�v���C���[���擾
	Player *pPlayer = GetPlayer();

	//���f���̈ړ��ʂ��X�V(����������)
	g_camera.move.x += (0.0f - g_camera.move.x) * 0.12f;
	g_camera.move.y += (0.0f - g_camera.move.y) * 0.12f;
	g_camera.move.z += (0.0f - g_camera.move.z) * 0.12f;

	//����
	g_camera.posVDest.x = pPlayer->pos.x + sinf(g_camera.rot.y) * -DIS;	//�ړI�̎��_�Ƀ��f���̈ʒu����(���΍��W)
	g_camera.posVDest.z = pPlayer->pos.z + cosf(g_camera.rot.y) * -DIS;	//�ړI�̎��_�Ƀ��f���̈ʒu����(���΍��W)
	(g_camera.posVDest - g_camera.posV) * 0.1f;

	//�J�����Ǐ]����
	g_camera.posR = pPlayer->pos;		//�����_�Ƀ��f���̈ʒu����	
	g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.1f;	//���_�Ƀ��f���̈ʒu����(���΍��W)
	g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.1f;	//���_�Ƀ��f���̈ʒu����(���΍��W)
}

//================================================
//�J�����̐ݒ菈��
//================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),	//����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	//�A�X�y�N�g��
		10.0f,		//Z�l�̍ŏ��l
		5000.0f);	//Z�l�̍ő�l

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_camera.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,	//���_
		&g_camera.posR,	//�����_
		&g_camera.posU);//������x�N�g��

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//================================================
//�J������]����
//================================================
void RotCamera(void)
{
	//�ڕW�̊p�x
	D3DXVECTOR3 RotDiff;

	//���f���̏��擾
	Player *pPlayer = GetPlayer();

	//�v���C���[�̊p�x��ݒ�
	g_camera.rotDest = pPlayer->rot;
	RotDiff = g_camera.rotDest - g_camera.rot;

	//�ړ������̕␳
	if (RotDiff.y > D3DX_PI || RotDiff.y < -D3DX_PI)
	{
		if (RotDiff.y > D3DX_PI)
		{
			RotDiff.y += -D3DX_PI * 2;
		}
		else if (RotDiff.y < -D3DX_PI)
		{
			RotDiff.y += D3DX_PI * 2;
		}
	}

	g_camera.rot.y += RotDiff.y * 0.03f;

	//�ړ������̕␳
	if (g_camera.rot.y > D3DX_PI || g_camera.rot.y < -D3DX_PI)
	{
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y += -D3DX_PI * 2;
		}
		else if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y += D3DX_PI * 2;
		}
	}

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * -DIS;	//�����_���猩��rot�̕����ɂǂꂾ������Ă��邩
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * -DIS;

}


//================================================
//�J�������̎擾
//================================================
Camera *GetCamera(void)
{
	return &g_camera;
}


