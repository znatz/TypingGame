#include "DxLib.h"

int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey(){
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll( tmpKey ); // 全てのキーの入力状態を得る
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		} else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

int x=320, y=240;
int Handle;

void gpCalc(){
	if( Key[ KEY_INPUT_RIGHT ] >= 1 ){
		x++;
	}
	if( Key[ KEY_INPUT_DOWN  ] >= 1 ){
		y++;
	}
	if( Key[ KEY_INPUT_LEFT  ] >= 1 ){
		x--;
	}
	if( Key[ KEY_INPUT_UP    ] >= 1 ){
		y--;
	}
}

void gpDraw(){
		DrawRotaGraph( x, y, 1.0, 0.0, Handle, TRUE );
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

		Handle = LoadGraph("画像/キャラクタ01.png");

		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キーの更新)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){

				gpCalc();

				gpDraw();

	}

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}