#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode( TRUE ); // ウィンドウモードに設定
	DxLib_Init(); // DXライブラリ初期化処理
	SetDrawScreen( DX_SCREEN_BACK ); //描画先を裏画面に設定

		int x = 0;
		int Handle;     // 画像格納用ハンドル
		Handle = LoadGraph( "画像/キャラクタ01.png" ); // 画像のロード

		while( 1 ){
				if( ProcessMessage() != 0 ){ // メッセージ処理
						break;//ウィンドウの×ボタンが押されたらループを抜ける
				}
				ClearDrawScreen(); // 画面を消す
				DrawGraph( x, 100, Handle, TRUE ); //画像の描画
				x = x + 2; // xを2増やす
				ScreenFlip(); //裏画面を表画面に反映
	}
	
	DxLib_End(); // DXライブラリ終了処理
	return 0;
}