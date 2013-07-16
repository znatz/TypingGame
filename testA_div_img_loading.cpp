#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

	int image[16];
	int image_index = 0;

	LoadDivGraph( "画像/キャラクタ10.png" , 16 , 4 , 4 , 32 , 32 , image ); // 画像の分割読み込み

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				DrawGraph( 0, 0, image[8], TRUE );      // 画像を表示

				DrawGraph( 0, 50, image[image_index], TRUE );      // 画像列中の1つを表示
				image_index = (image_index + 1 ) % 16 ;  

		}

		DxLib_End(); // DXライブラリ終了処理
		return 0;
}