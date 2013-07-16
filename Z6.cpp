#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./文書/words.txt"
#define MAXCOUNTS 200
#define WORDCOUNTS 10
#define DROPSPEED 0.1
#define FONTSIZE 10

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
		t[i].y_increment = GetRand(DROPSPEED) + 0.1 ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(MAXCOUNTS)].c_str();  //ランダム取り出す、stringからconst TCHAR*変換
	}
}

void ChangeCallback( void *Data )
{
	// TODO :: add event handler to return to default windows size;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txt生成しないように
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// 最大化ボタンを有効にする
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	

	// 変数初期化
	int i;
	int SizeX;					// 画面サイス
	int SizeY;					// 画面サイス
	int ColorBitDepth;			// 画面色
	char UserInput[10];			// user input
	int InputHandle;			
	int Hit = 0;
	const TCHAR** words = new const TCHAR* [WORDCOUNTS];

	GetScreenState( &SizeX , &SizeY , &ColorBitDepth );
	SetFontSize(FONTSIZE);
	Targets targets[WORDCOUNTS] ;
	Inittargets(targets);

 
	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


	// 画面に描画
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		if (Hit != 0) { InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; Hit = 0; }
		// 作成したキー入力ハンドルをアクティブにする
		SetActiveKeyInput( InputHandle ) ;
		// 入力モードを描画
		DrawKeyInputModeString( SizeX , SizeY ) ; 
		// 入力途中の文字列を描画
		DrawKeyInputString( 0 , 0 , InputHandle ) ;
		GetKeyInputString( UserInput , InputHandle ) ;
		string str(UserInput);

		// 普通の描画
		for (i=0; i<WORDCOUNTS; i++){
			if (targets[i].word == "") continue;
			if ( str.compare(targets[i].word) != 0) {
				DrawFormatString( targets[i].x, targets[i].y, targets[i].color, "%s", targets[i].word) ; // 単語の間、全角空白をいれないこと
				targets[i].y += targets[i].y_increment;
			} else {
				targets[i].word = "";
				Hit ++;
			}
		}
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;
	
	return 0 ;

}