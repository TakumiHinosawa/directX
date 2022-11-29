//======================================
//
//���C���֐�
//Author:�����V����	[main.h]
//
//=====================================

#include"main.h"
#include"Polygon.h"
#include"input.h"
#include"camera.h"
#include"light.h"
#include"model.h"
#include"player.h"
#include"shadow.h"
#include"wall.h"
#include"billboard.h"
#include"bullet.h"
#include"explosion.h"
#include"effect.h"
#include"particle.h"
#include"meshfield.h"
#include"meshcylinder.h"

//�}�N����`
#define CLASS_NAME		"WindowClass"				//�E�C���h�N���X�̖��O
#define WINDOW_NAME		"3D�Q�[��"			    //�E�C���h�̖��O

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DebugPolygon(void);
void DebugCamera(void);
void DrawFPS(void);

//�O���[�o���錾
LPDIRECT3D9	g_pD3D = NULL;						//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;						//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;							//FPS�J�E���^�[

//�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================
//���C���֐�
//=========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;		//���ݎ���
	DWORD dwExecLastTime;		//�Ō�ɏ�����������
	DWORD dwFrameCount;			//�t���[���J�E���^�[
	DWORD dwFPSLastTime;		//�Ō��FPS���v����������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASS�̃������T�C�Y
		CS_CLASSDC,							//�E�C���h�E�X�^�C��
		WindowProc,							//�E�C���h�E�v���V�[�W��
		0,									//0�ɂ���
		0,									//0�ɂ���
		hInstance,							//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),		//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),			//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),			//�N���C�A���g�̈�̔w�i�F
		NULL,								//���j���[�o�[
		CLASS_NAME,							//�E�C���h�E�n���h��(���ʎq)
		LoadIcon(NULL,IDI_APPLICATION)		//���b�Z�[�W���i�[����ϐ�
	};

	HWND hWnd;			//�E�C���h�E�n���h��
	MSG msg;			//���b�Z�[�W���i�[����ϐ�

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };	//��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,		//�g���E�C���h�X�^�C��
		CLASS_NAME,					//�E�C���h�E�N���X�̖��O
		WINDOW_NAME,				//�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,		//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,				//�E�C���h�E����X���W
		CW_USEDEFAULT,				//�E�C���h�E����Y���W
		SCREEN_WIDTH,				//�E�C���h�E��
		SCREEN_HEIGHT,				//�E�C���h�E����
		NULL,						//�e�E�C���h�E�̃n���h��
		NULL,						//���j���[�܂��͎q�E�C���h�E��ID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�C���h�E�쐬�f�[�^

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//����������
	dwExecLastTime = timeGetTime();		//���ݎ������擾

	dwFrameCount = 0;					//����������
	dwFPSLastTime = timeGetTime();		//���ݎ������擾

										//�E�C���h�̕\��
	ShowWindow(hWnd, nCmdShow);			//�E�C���h�E�̕\����Ԃ�ݒ�

	UpdateWindow(hWnd);					//�N���C�A���g�̈���X�V

										//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v�𔲂���
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);	//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);  //�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}

		}

		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5�b�o��
		 //FPS���v��
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			dwFPSLastTime = dwCurrentTime;		//FPS���v������������ۑ�
			dwFrameCount = 0;					//�t���[���J�E���g���N���A

		}

		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;

				dwFrameCount++;		//�t���[���J�E���g�����Z

				//�X�V����
				Update();

				//�`�揈��
				Draw();

			}

		}

	}

	//�I������
	Uninit();

	//�E�C���h�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}


//=========================================================================================
//�E�C���h�E�v���V�[�W��
//=========================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;													//�Ԃ�l���i�[
	char aString[256] = "test";									//�`�悷��e�L�X�g���i�[
	static POINT pos = { 100,100 };								//�����̎n�_(X���W�EY���W)
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//�E�C���h�E�̗̈�
	static POINT move = { 2,3 };								//�����̎��_�ړ���(X�����EY����)

	switch (uMsg)
	{
	case WM_DESTROY:		//�E�C���h�E�j���̃��b�Z�[�W
							//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_CLOSE:			//����{�^���̉����̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{//�I���{�^���������ꂽ

		 //�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;		//0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;

	case WM_KEYDOWN:		//�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:		//ESC�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);

			}

			break;

		}

		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}


//=========================================================================================
//�������ݒ菈��
//=========================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//����������
	D3DDISPLAYMODE d3ddm;				//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;		//�v���[���e�[�V�����p�����[�^

	//DirectX 3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���s�̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//�p�����[�^�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;								//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;											//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;								//�f�v�X�o�b�t�@�ƃX�e���c���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//�f�v�X�o�b�t�@�Ƃ���16bit�g��
	d3dpp.Windowed = bWindow;											//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//�C���^�[�o��

																		//DirectX 3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))

		{
			return E_FAIL;
		}

	}

	//�e��I�u�W�F�N�g�̏������ݒ�

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�}�E�X�̏�����
	InitMouse(hInstance, hWnd);

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();

	//�|���S���̏���������
	InitPolygon();

	//�ǂ̏���������
	InitWall();

	//�e�̏���������
	InitShadow();

	//���f���̏���������
	InitModel();

	//�v���C���[�̏���������
	InitPlayer();

	//�r���{�[�h�̏�����
	InitBillboard();

	//�e�̏���������
	InitBullet();

	//�����̏���������
	InitExplosion();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//���b�V���V�����_�[�̏���������
	InitMeshCylinder();

	return S_OK;

}

//================================================
//�I������
//================================================
void Uninit(void)
{
	//�e��I�u�W�F�N�g�̏I������

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	//�}�E�X�̏I������
	UninitMouse();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	//�|���S���̏I������
	UninitPolygon();

	//���f���̏I������
	UninitModel();

	//�v���C���[�̏I������
	UninitPlayer();

	//�ǂ̏I������
	UninitWall();

	//�e�̏I������
	UninitShadow();

	//�r���{�[�h�̏I������
	UninitBillboard();

	//�e�̏I������
	UninitBullet();

	//�����̏I������
	UninitExplosion();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//���b�V���V�����_�[�̏I������
	UninitMeshCylinder();

	//�f�o�C�X�\���p�t�H���g�̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct 3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

//================================================
//�X�V����
//================================================
void Update(void)
{
	//�e��I�u�W�F�N�g�̍X�V����

	//�L�[�{�[�h�̍X�V����
	UpdateKeyboard();

	//�}�E�X�̍X�V����
	UpdateMouse();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateCamera();

	//�|���S���̍X�V����
	UpdatePolygon();

	//���f���̍X�V����
	UpdateModel();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�ǂ̍X�V����
	UpdateWall();

	//�e�̍X�V����
	UpdateShadow();

	//�r���{�[�h�̍X�V����
	UpdateBillboard();

	//�e�̍X�V����
	UpdateBullet();

	//�����̍X�V����
	UpdateExplosion();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//���b�V���V�����_�[�̍X�V����
	UpdateMeshCylinder();
}

//================================================
//�`�揈��
//================================================
void Draw(void)
{
	//��ʃN���A
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

#ifdef _DEBUG	//�f�o�b�O�\��
		DebugPolygon();
		DebugCamera();
		DrawFPS();
		GetMouseDB();
#endif
		//�J�����̐ݒ�
		SetCamera();

		//�|���S���̕`�揈��
		DrawPolygon();

		//���f���̕`�揈��
		DrawModel();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�ǂ̕`�揈��
		DrawWall();

		//�r���{�[�h�̕`�揈��
		DrawBillboard();

		//�e�̕`�揈��
		DrawShadow();

		//�e�̕`�揈��
		DrawBullet();

		//�����̕`�揈��
		DrawExplosion();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//���b�V���t�B�[���h�̕`�揈��
		//DrawMeshField();

		//���b�V���V�����_�[�̕`�揈��
		DrawMeshCylinder();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�A�b�v�ƃt�����g�o�b�t�@�̐؂�ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//�t�H���g�̎擾����
//================================================
LPD3DXFONT GetFont(void)
{
	return g_pFont;
}

//====================================================
//FPS�̕\������
//====================================================
void DrawFPS(void)
{
#if 1
	RECT rect = { 600,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//================================================
//�f�o�b�O[�|���S��]�\��
//================================================
void DebugPolygon(void)
{
#if 1

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrP[256];

	//������ɑ��
	wsprintf(&aStrP[0], "---������@[model]---\n �@�@�@��ړ�[��]\n �@�@�@���ړ�[��]\n �@�@�@�E�ړ�[��]\n �@�@�@���ړ�[��]\n �@�@�@�����l[Enter]");

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrP[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif
}

//================================================
//�f�o�b�O[�J����]�\��
//================================================
void DebugCamera(void)
{
#if 1

	RECT rect = { 0,120,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrC[2][256];

	//������ɑ��
	wsprintf(&aStrC[0][0], "---������@[camera]---\n �@�@�@��ړ�[W]\n �@�@�@���ړ�[A]\n �@�@�@�E�ړ�[D]\n �@�@�@���ړ�[S]\n �@�@�@�E����[E]\n �@�@�@������[Q]\n �@�@�@�����l[G]\n");

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrC[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif
}

