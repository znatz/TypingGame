#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode( TRUE ); // ウィンドウモードに設定
		DxLib_Init(); // DXライブラリ初期化処理

		int x = 50;
		int Handle; // 画像格納用ハンドル
		Handle = LoadGraph( "画像/キャラクタ01.png" ); // 画像のロード

		while( 1 ){
				if( ProcessMessage() != 0 ){ // メッセージ処理
						break;//ウィンドウの×ボタンが押されたらループを抜ける
				}
				ClearDrawScreen(); // 画面を消す
				DrawGraph( x, 100, Handle, TRUE ); //画像の描画
				x = x + 2; // xを2増やす
				Sleep(7); // 7[ms]待機
		}
		
		DxLib_End(); // DXライブラリ終了処理
		return 0;
} 