#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./文書/words.txt"
#define MAXCOUNTS 200
#define WORDCOUNTS 10
#define DROPSPEED 0.1
#define MINSPEED 0.1
#define FONTSIZE 10

typedef struct TARGETS Targets;
struct TARGETS {
	int x;
	int y;
	int y_increment;
	int color;
	const TCHAR* word;
};

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
		t[i].y_increment = GetRand(DROPSPEED) + MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(MAXCOUNTS)].c_str();  //ランダム取り出す、stringからconst TCHAR*変換
	}
}

void ChangeCallback( void *Data )
{
	// TODO :: add event handler to return to default windows size;
}

int Stage(int& _hit, int _succeed, int _sizeX, int _sizeY, int _colorBitDepth, char* _userInput, int& _inputHandle, Targets* _targets){
		
		int i;
		//int _inputHandle;
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	// Hitしたら、入力領域クリア、Hitリセット
		
		SetActiveKeyInput( _inputHandle ) ;				// 作成したキー入力ハンドルをアクティブにする
		DrawKeyInputModeString( _sizeX , _sizeY ) ;		// 入力モードを描画		
		DrawKeyInputString( 0 , 0 , _inputHandle ) ;		// 入力途中の文字列を描画
		GetKeyInputString( _userInput , _inputHandle ) ;
		string str(_userInput);

		// Hit判断
		for (i=0; i<WORDCOUNTS; i++){
			if (_succeed == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // 単語の間、全角空白をいれないこと
				_targets[i].y += _targets[i].y_increment;
			} else {
				_targets[i].word = "";
				_hit ++;
				if (_succeed == 0) break;
				_succeed--;
			}
		}
		return _succeed;
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
	int Hit = 0;				// 1: 1つ単語正解
	int Succeed = 10;			// 10: Stage内正解回数

	GetScreenState( &SizeX , &SizeY , &ColorBitDepth );
	SetFontSize(FONTSIZE);
	Targets targets[WORDCOUNTS] ;
	Inittargets(targets);

 
	// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
	InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


	// 画面に描画
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		if (Stage(Hit, Succeed, SizeX, SizeY, ColorBitDepth, UserInput, InputHandle, targets) == 0) {/*restart staget*/};
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;
	
	return 0 ;

}