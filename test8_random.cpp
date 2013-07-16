#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

        int Random[8];
        int Green = GetColor( 0, 255, 0 );      // 緑の色コードを取得

        SRand( 123456 ); // 乱数の初期値を123456に設定する、SRandがなければ、毎回異なる乱数が生成される

        Random[0] = GetRand( 100 ); // 0~100までの乱数を生成する
        Random[1] = GetRand( 100 );
        Random[2] = GetRand( 100 );
        Random[3] = GetRand( 100 );

        SRand( 123456 ); // 乱数の初期値を123456に再度設定する

        Random[4] = GetRand( 100 ); // 0~100までの乱数を生成する
        Random[5] = GetRand( 100 );
        Random[6] = GetRand( 100 );
        Random[7] = GetRand( 100 );

        // while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

                for( int i=0; i<8; i++ ){
                        DrawFormatString( 0, 20*i, Green, "%d", Random[i] ); // 文字を描画する
                }

        }

        DxLib_End(); // DXライブラリ終了処理
        return 0;
} 