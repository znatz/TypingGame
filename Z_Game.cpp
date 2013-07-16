#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./文書/words.txt"

 #include "DxLib.h"

string *Getwords(){
	ifstream file(FILENAME);
	string* myArray = new string[5];
	if(file.is_open())
	{
		for(int i = 0; i < 5; ++i)
		{
			file >> myArray[i];
		}
	}
	return myArray;
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode( TRUE );
	string* words = new string[5];
	words = Getwords();

	// ＤＸライブラリの初期化
	if( DxLib_Init() == -1 ) return -1 ;


	// 画面に描画
	DrawString( 0, 10, words[0].c_str(), GetColor( 255,255,255 ) ) ; // 単語の間、全角空白をいれないこと
	DrawString( 0, 30, words[1].c_str(), GetColor( 255,255,255 ) ) ;


	// キー入力待ち
	WaitKey() ;

	// ＤＸライブラリの後始末
	DxLib_End() ;

	return 0 ;
}