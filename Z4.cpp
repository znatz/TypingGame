#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./文書/words.txt"
#define MAXCOUNTS 200
#define WORDCOUNTS 7
#define DROPSPEED 500
#define FONTSIZE 20

typedef struct TARGETS Targets;
struct TARGETS {
	int x;
	int y;
	int y_increment;
	int color;
	const TCHAR* word;
};

//template<typename T>
//void shuffle(T arr[], int n){   // nは配列の長さ
//  int i, rnd;
//  T temp;
//
//  for(i=0;i<n;i++){
//	rnd = GetRand(100) % n;
//	temp = arr[i];
//	arr[i] = arr[rnd];
//	arr[rnd] = temp;
//  }
//}

void Inittargets( Targets* t){
	// 単語を読み取る
	ifstream file(FILENAME);
	string* myArray = new string[MAXCOUNTS];  // myArrayのサイズはWORDCOUNTSより大きはず
	if(file.is_open())
	{
		for(int i = 0; i < MAXCOUNTS; ++i)
		{
			file >> myArray[i];
		}
	}

	// targets初期化
	for(int i = 0; i < WORDCOUNTS; ++i)
	{
		file >> myArray[i];
		t[i].x = FONTSIZE * i * 5 ;
		t[i].y = 10;
		t[i].y_increment = GetRand(DROPSPEED)/100 + 1 ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(MAXCOUNTS)].c_str();  //ランダム取り出す、stringからconst TCHAR*変換
	}
}

int Color, Count;
void ChangeCallback( void *Data )
{
	int Table[4][3] = { 255,0,0,  0,255,0,  0,0,255,  255,255,255 };

	// カウントの値によって色を変更する
	Count = ( Count + 1 ) % 4 ;
	Color = GetColor( Table[Count][0], Table[Count][1], Table[Count][2] );
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	// 最大化ボタンを有効にする
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	
	// 変数初期化
	int i;
	const TCHAR** words = new const TCHAR* [WORDCOUNTS];
	SetFontSize(FONTSIZE);
	Targets targets[WORDCOUNTS] ;
	Inittargets(targets);


	// 画面に描画
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		for (i=0; i<WORDCOUNTS; i++){
			DrawFormatString( targets[i].x, targets[i].y, targets[i].color, "%s", targets[i].word) ; // 単語の間、全角空白をいれないこと
			targets[i].y += targets[i].y_increment;
		}
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;
	
	return 0 ;

}