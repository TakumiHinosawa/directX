//======================================
//
//メイン関数
//Author:日野澤匠泉	[main.h]
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

//マクロ定義
#define CLASS_NAME		"WindowClass"				//ウインドクラスの名前
#define WINDOW_NAME		"3Dゲーム"			    //ウインドの名前

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DebugPolygon(void);
void DebugCamera(void);
void DrawFPS(void);

//グローバル宣言
LPDIRECT3D9	g_pD3D = NULL;						//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;		//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;						//フォントへのポインタ
int g_nCountFPS = 0;							//FPSカウンター

//デバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//=========================
//メイン関数
//=========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;		//最後に処理した時刻
	DWORD dwFrameCount;			//フレームカウンター
	DWORD dwFPSLastTime;		//最後にFPSを計測した時刻

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//WNDCLASSのメモリサイズ
		CS_CLASSDC,							//ウインドウスタイル
		WindowProc,							//ウインドウプロシージャ
		0,									//0にする
		0,									//0にする
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//ウインドウハンドル(識別子)
		LoadIcon(NULL,IDI_APPLICATION)		//メッセージを格納する変数
	};

	HWND hWnd;			//ウインドウハンドル
	MSG msg;			//メッセージを格納する変数

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };	//画面サイズの構造体

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);


	//ウインドウを生成
	hWnd = CreateWindowEx(0,		//拡張ウインドスタイル
		CLASS_NAME,					//ウインドウクラスの名前
		WINDOW_NAME,				//ウインドウの名前
		WS_OVERLAPPEDWINDOW,		//ウインドウスタイル
		CW_USEDEFAULT,				//ウインドウ左上X座標
		CW_USEDEFAULT,				//ウインドウ左上Y座標
		SCREEN_WIDTH,				//ウインドウ幅
		SCREEN_HEIGHT,				//ウインドウ高さ
		NULL,						//親ウインドウのハンドル
		NULL,						//メニューまたは子ウインドウのID
		hInstance,					//インスタンスハンドル
		NULL);						//ウインドウ作成データ

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;					//初期化する
	dwExecLastTime = timeGetTime();		//現在時刻を取得

	dwFrameCount = 0;					//初期化する
	dwFPSLastTime = timeGetTime();		//現在時刻を取得

										//ウインドの表示
	ShowWindow(hWnd, nCmdShow);			//ウインドウの表示状態を設定

	UpdateWindow(hWnd);					//クライアント領域を更新

										//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらメッセージループを抜ける
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);	//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg);  //ウインドウプロシージャへメッセージを送出
			}

		}

		if ((dwCurrentTime - dwFPSLastTime) >= 500)
		{//0.5秒経過
		 //FPSを計測
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

			dwFPSLastTime = dwCurrentTime;		//FPSを計測した時刻を保存
			dwFrameCount = 0;					//フレームカウントをクリア

		}

		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				dwFrameCount++;		//フレームカウントを加算

				//更新処理
				Update();

				//描画処理
				Draw();

			}

		}

	}

	//終了処理
	Uninit();

	//ウインドクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;

}


//=========================================================================================
//ウインドウプロシージャ
//=========================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;													//返り値を格納
	char aString[256] = "test";									//描画するテキストを格納
	static POINT pos = { 100,100 };								//線分の始点(X座標・Y座標)
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };		//ウインドウの領域
	static POINT move = { 2,3 };								//線分の視点移動量(X方向・Y方向)

	switch (uMsg)
	{
	case WM_DESTROY:		//ウインドウ破棄のメッセージ
							//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_CLOSE:			//閉じるボタンの押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{//終了ボタンが押された

		 //ウインドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);

		}

		else
		{
			return 0;		//0を返さないと終了してしまう
		}

		break;

	case WM_KEYDOWN:		//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:		//ESCキーが押された

			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウインドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);

			}

			break;

		}

		break;

	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}


//=========================================================================================
//初期化設定処理
//=========================================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//初期化処理
	D3DDISPLAYMODE d3ddm;				//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;		//プレゼンテーションパラメータ

	//DirectX 3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現行のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータ設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));									//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;								//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;								//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;								//バックバッファの形式
	d3dpp.BackBufferCount = 1;											//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;							//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;								//デプスバッファとステンツルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;							//デプスバッファとして16bit使う
	d3dpp.Windowed = bWindow;											//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;			//インターバル

																		//DirectX 3Dデバイスの生成
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

	//各種オブジェクトの初期化設定

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//デバッグ表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//マウスの初期化
	InitMouse(hInstance, hWnd);

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();

	//ポリゴンの初期化処理
	InitPolygon();

	//壁の初期化処理
	InitWall();

	//影の初期化処理
	InitShadow();

	//モデルの初期化処理
	InitModel();

	//プレイヤーの初期化処理
	InitPlayer();

	//ビルボードの初期化
	InitBillboard();

	//弾の初期化処理
	InitBullet();

	//爆発の初期化処理
	InitExplosion();

	//エフェクトの初期化処理
	InitEffect();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//メッシュシリンダーの初期化処理
	InitMeshCylinder();

	return S_OK;

}

//================================================
//終了処理
//================================================
void Uninit(void)
{
	//各種オブジェクトの終了処理

	//キーボードの終了処理
	UninitKeyboard();

	//マウスの終了処理
	UninitMouse();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	//ポリゴンの終了処理
	UninitPolygon();

	//モデルの終了処理
	UninitModel();

	//プレイヤーの終了処理
	UninitPlayer();

	//壁の終了処理
	UninitWall();

	//影の終了処理
	UninitShadow();

	//ビルボードの終了処理
	UninitBillboard();

	//弾の終了処理
	UninitBullet();

	//爆発の終了処理
	UninitExplosion();

	//エフェクトの終了処理
	UninitEffect();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//メッシュシリンダーの終了処理
	UninitMeshCylinder();

	//デバイス表示用フォントの破棄
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct 3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

}

//================================================
//更新処理
//================================================
void Update(void)
{
	//各種オブジェクトの更新処理

	//キーボードの更新処理
	UpdateKeyboard();

	//マウスの更新処理
	UpdateMouse();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateCamera();

	//ポリゴンの更新処理
	UpdatePolygon();

	//モデルの更新処理
	UpdateModel();

	//プレイヤーの更新処理
	UpdatePlayer();

	//壁の更新処理
	UpdateWall();

	//影の更新処理
	UpdateShadow();

	//ビルボードの更新処理
	UpdateBillboard();

	//弾の更新処理
	UpdateBullet();

	//爆発の更新処理
	UpdateExplosion();

	//エフェクトの更新処理
	UpdateEffect();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//メッシュシリンダーの更新処理
	UpdateMeshCylinder();
}

//================================================
//描画処理
//================================================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

#ifdef _DEBUG	//デバッグ表示
		DebugPolygon();
		DebugCamera();
		DrawFPS();
		GetMouseDB();
#endif
		//カメラの設定
		SetCamera();

		//ポリゴンの描画処理
		DrawPolygon();

		//モデルの描画処理
		DrawModel();

		//プレイヤーの描画処理
		DrawPlayer();

		//壁の描画処理
		DrawWall();

		//ビルボードの描画処理
		DrawBillboard();

		//影の描画処理
		DrawShadow();

		//弾の描画処理
		DrawBullet();

		//爆発の描画処理
		DrawExplosion();

		//エフェクトの描画処理
		DrawEffect();

		//メッシュフィールドの描画処理
		//DrawMeshField();

		//メッシュシリンダーの描画処理
		DrawMeshCylinder();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックアップとフロントバッファの切り替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//================================================
//フォントの取得処理
//================================================
LPD3DXFONT GetFont(void)
{
	return g_pFont;
}

//====================================================
//FPSの表示処理
//====================================================
void DrawFPS(void)
{
#if 1
	RECT rect = { 600,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	//文字列に代入
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//================================================
//デバッグ[ポリゴン]表示
//================================================
void DebugPolygon(void)
{
#if 1

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrP[256];

	//文字列に代入
	wsprintf(&aStrP[0], "---操作方法[model]---\n 　　　上移動[↑]\n 　　　左移動[←]\n 　　　右移動[→]\n 　　　下移動[↓]\n 　　　初期値[Enter]");

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrP[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif
}

//================================================
//デバッグ[カメラ]表示
//================================================
void DebugCamera(void)
{
#if 1

	RECT rect = { 0,120,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStrC[2][256];

	//文字列に代入
	wsprintf(&aStrC[0][0], "---操作方法[camera]---\n 　　　上移動[W]\n 　　　左移動[A]\n 　　　右移動[D]\n 　　　下移動[S]\n 　　　右旋回[E]\n 　　　左旋回[Q]\n 　　　初期値[G]\n");

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrC[0][0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

#endif
}

