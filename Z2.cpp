#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./文書/words.txt"
#define WORDCOUNTS 7
#define DROPSPEED 1
#define FONTSIZE 10

const TCHAR** Getwords(){
	ifstream file(FILENAME);
	string* myArray = new string[WORDCOUNTS];
	const TCHAR** result = new const TCHAR* [WORDCOUNTS];
	if(file.is_open())
	{
		for(int i = 0; i < WORDCOUNTS; ++i)
		{
			file >> myArray[i];
			result[i] = myArray[i].c_str();  // string -> const TCHAR*
		}
	}
	return result;
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	
	// 変数初期化
	const TCHAR** words = new const TCHAR* [WORDCOUNTS];
	int incY = 0;
	int i;
	SetFontSize(FONTSIZE);

	// 単語を読み込む
	words = Getwords();

	// 画面に描画
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		for (i=0; i<WORDCOUNTS; i++){
			// DrawString( 10 + i*FONTSIZE*5, incY, words[i], GetColor( 255,255,255 ) ) ; // 単語の間、全角空白をいれないこと
			DrawFormatString( 10 + i*FONTSIZE*5, incY, GetColor( 255,255,255 ), "%s", words[i]) ; // 単語の間、全角空白をいれないこと
		}
		incY += DROPSPEED;
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;

	return 0 ;

}