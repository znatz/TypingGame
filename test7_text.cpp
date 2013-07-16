#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定

			DWORD color = GetColor(53,108,33);
			
		// while(裏画面を表画面に反映, メッセージ処理, 画面クリア)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

			DrawFormatString(250,250,color,"今日も眠れない！");	
			DrawFormatString(250,300,color,"%d缶目のビール", 3);	

		}
		
		DxLib_End(); // DXライブラリ終了処理
		return 0;
} 