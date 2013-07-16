#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

		int x = 0;
		double angle = 0;
		int Handle1, Handle2;     // 画像格納用ハンドル
		Handle1 = LoadGraph( "画像/キャラクタ01.png" ); // 画像のロード
		Handle2 = LoadGraph( "画像/キャラクタ01.png" ); // 画像のロード

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				DrawGraph( x, 100, Handle1, TRUE ); //画像の描画
				DrawGraph( x, 110, Handle2, TRUE ); //画像の描画
				DrawRotaGraph(200, 200, 1.0, angle, Handle1, TRUE);
				x = x + 2; // xを2増やす
				angle += 2;

				SetDrawBlendMode( DX_BLENDMODE_ALPHA,  128 );		//ブレンドモードをα(128/255)に設定
				DrawRotaGraph(200, 400, 1.0, angle, Handle1, TRUE);
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );		//ブレンドモードをオフ

		}
		
		DxLib_End(); // DXライブラリ終了処理
		return 0;
} 