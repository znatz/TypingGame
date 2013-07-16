#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

        int Handle, Count=0;
        Handle = LoadSoundMem("サウンド/1up.wav"); // サウンド/1up.wavをロードし、識別番号をHandleに格納

        // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

                if( Count % 120 == 0 ){ // 2秒に一度
                        PlaySoundMem( Handle, DX_PLAYTYPE_BACK ); // 効果音を再生する
                }

                Count++;

        }

        DxLib_End(); // DXライブラリ終了処理
        return 0;
} 