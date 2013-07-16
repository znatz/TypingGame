#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

		int Handle;     // 画像格納用ハンドル
		Handle = LoadGraph( "画像/弾00.png" ); // 画像のロード

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 );   //ブレンドモードをα(128/255)に設定
				DrawGraph( 100, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 120, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 140, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 160, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 180, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 200, 200, Handle, TRUE ); //画像の描画
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );           //ブレンドモードをオフ

				SetDrawBlendMode( DX_BLENDMODE_ADD,  255 );             //ブレンドモードを加算(255/255)に設定
				DrawGraph( 300, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 320, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 340, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 360, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 380, 200, Handle, TRUE ); //画像の描画
				DrawGraph( 400, 200, Handle, TRUE ); //画像の描画
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );           //ブレンドモードをオフ

		}

		DxLib_End(); // DXライブラリ終了処理
		return 0;
} 