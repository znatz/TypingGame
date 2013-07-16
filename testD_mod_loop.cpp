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

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

        int Count = 0; // カウンタ
        int Handle = LoadGraph("画像/キャラクタ01.png"); // 画像をロード

        // while(裏画面を表画面に反映, メッセージ処理, キーの入力状態更新)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){

                DrawGraph(   0, Count% 50, Handle, TRUE ); // 周期  50カウント でループ表示する
                DrawGraph( 100, Count%100, Handle, TRUE ); // 周期 100カウント でループ表示する
                DrawGraph( 200, Count%150, Handle, TRUE ); // 周期 150カウント でループ表示する

                Count++; // カウンタ加算

        }

        DxLib_End(); // DXライブラリ終了処理
        return 0;
}