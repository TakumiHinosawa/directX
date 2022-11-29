//======================================
//
//���C�g����
//Author:�����V����	[light.cpp]
//
//=====================================
#include"light.h"

//�}�N����`
#define MAX_LIGHT	(3)		//���C�g�̐�

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[MAX_LIGHT];

//================================================
//���C�g�̏���������
//================================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;		//�ݒ�����x�N�g��

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		//���C�g�̏����N���A����
		ZeroMemory(&g_light[nCnt], sizeof(D3DLIGHT9));

		//���C�g�̎�ނ�ݒ�
		g_light[nCnt].Type = D3DLIGHT_DIRECTIONAL;

		switch (nCnt)
		{
		case 0:
			//���C�g�̊g�U����ݒ�
			g_light[nCnt].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.22f, -0.85f, 0.45f);
			break;

		case 1:
			//���C�g�̊g�U����ݒ�
			g_light[nCnt].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.89f, -0.15f, 0.15f);
			break;

		case 2:
			//���C�g�̊g�U����ݒ�
			g_light[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���C�g�̕�����ݒ�
			vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
			break;
		}

		D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g���𐳋K������
		g_light[nCnt].Direction = vecDir;
		
		//���C�g��ݒ肷��
		pDevice->SetLight(nCnt, &g_light[nCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}
//================================================
//���C�g�̏I������
//================================================
void UninitLight(void)
{

}

//================================================
//���C�g�̍X�V����
//================================================
void UpdateLight(void)
{

}
