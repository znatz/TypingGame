#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

typedef struct GAMEDATA Game;
struct GAMEDATA {
	string FILENAME ; 
	int MAXCOUNTS   ; 
	int WORDCOUNTS  ;
	int XSPREAD	    ;
	int DROPSPEED   ;
	double MINSPEED ; 
	int FONTSIZE    ;
};

typedef struct TARGETS Targets;
struct TARGETS {
	int x;
	int y;
	int y_increment;
	int color;
	const TCHAR* word;
};

// Target初期化、画面中の配置
void Inittargets( Targets* t, string* myArray, Game g){
	for(int i = 0; i < g.WORDCOUNTS; ++i)
	{
		t[i].x = i * GetRand(g.XSPREAD) + i * g.FONTSIZE * 10;  // <========= TODO!!!! use GetDrawStringWidth
		t[i].y = 10;
		t[i].y_increment =(int) GetRand(g.DROPSPEED) % g.DROPSPEED + g.MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(g.MAXCOUNTS)].c_str();  //ランダム取り出す、stringからconst TCHAR*変換
	}
}

// ファイルから読み取った単語を保存する
void InitData( string* &myArray, Game g){
	ifstream file(g.FILENAME);
	if(file.is_open())
	{
		for(int i = 0; i < g.MAXCOUNTS; ++i)
		{
			file >> myArray[i];
		}
	}
}

void ChangeCallback( void *Data )
{
	// TODO :: add event handler to return to default windows size;
}

void DrawHitEffect(int x, int y, int* GBuff){
	int i;
	for (i = 0; i < 7; i++) {
		DrawGraph(x, y, GBuff[i], TRUE);
	}
}

int Stage(int& _hit, int& _totalhit, 
		  int _sizeX, int _sizeY, int _colorBitDepth, 
		  char* _userInput, int& _inputHandle, 
		  Targets* _targets, Game g, int* GBuff){
		
		int i;
		
		// Hitしたら、入力領域クリア、Hitリセット
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	
		
		SetActiveKeyInput( _inputHandle ) ;					// 作成したキー入力ハンドルをアクティブにする
		DrawKeyInputModeString( _sizeX , _sizeY ) ;			// 入力モードを描画		
		DrawKeyInputString( 0 , 0 , _inputHandle ) ;		// 入力途中の文字列を描画
		GetKeyInputString( _userInput , _inputHandle ) ;
		string str(_userInput);

		// Hit判断
		for (i=0; i<g.WORDCOUNTS; i++){
			if (_totalhit == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // 単語の間、全角空白をいれないこと
				_targets[i].y += _targets[i].y_increment;
			} else {	
				// hit
				DrawHitEffect(_targets[i].x, _targets[i].y, GBuff);
				_targets[i].word = "";
				_hit ++;
				if (_totalhit == 0) break;
				_totalhit--;
			}
		}
		DrawFormatString( 100, 300, GetColor(255,255,255), "_totalhit! %d", _totalhit) ; // debug
		return _totalhit;
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	// -----　Window設定
	SetOutApplicationLogValidFlag(FALSE); // Log.txt生成しないように
	SetWindowUserCloseEnableFlag( FALSE ) ;// メインウインドウの×ボタンを押した時にライブラリが自動的にウインドウを閉じるかどうかのフラグをセットする
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// 最大化ボタンを有効にする
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	int GBuff[8];
	LoadDivGraph("./画像/explosion.png", 8, 8, 1, 40, 40, GBuff);
	Game g = {
		"./文書/words.txt",		// filename
		200,					// max counts
		2,						// word counts
		100,					// xspread
		10,						// dropspeed
		0.1,					// minspeed
		20						// fontsize
	};

	// 文字表示設定
	ChangeFont( "ＭＳ 明朝" ) ;
	SetFontSize(g.FONTSIZE);

	// -----　ファイルから単語を読み取る
	string* myArray = new string[g.MAXCOUNTS];  // myArrayのサイズはg.WORDCOUNTSより大きはず
	InitData(myArray, g);
	
	// ゲームメインループ
	bool restartgame = true;
	while (true) {
			// 変数初期化
			g.WORDCOUNTS ++;			// ゲームレベル調整
			int SizeX;					// 画面サイス
			int SizeY;					// 画面サイス
			int ColorBitDepth;			// 画面色
			char UserInput[100];			// user input
			int InputHandle;			
			int Hit = 0;				// 1: 1つ単語正解
			int TotalHit = g.WORDCOUNTS;			// g.WORDCOUNTS: Stage内正解回数

			GetScreenState( &SizeX , &SizeY , &ColorBitDepth );

			// 落ちる単語を選ぶ
			Targets *targets = (Targets*) malloc(sizeof(Targets)*g.WORDCOUNTS);
			Inittargets(targets, myArray, g);

 
			// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


			// 画面に描画
			while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
				if( GetWindowUserCloseFlag() == TRUE ){
					DrawFormatString( SizeX/2 - g.FONTSIZE* 10 , SizeY/2 - g.FONTSIZE/2 , GetColor(255,255,255), "%s", "ゲームを終了します　何かキーを入力してください") ;
					DrawString(100,100,"ゲームを終了します　何かキーを入力してください",GetColor(255,255,255), 0);
					WaitKey();
					return 0;
				}
				if( CheckHitKey(KEY_INPUT_F1) == 1 ){
					restartgame = false;  // exit game
					break;
				}
				if (Stage(Hit, TotalHit, SizeX, SizeY, ColorBitDepth, UserInput, InputHandle, targets, g, GBuff) == 0) {
					break;				// exit stage restart game
				};
				DrawFormatString( 100, 200, GetColor(255,255,255), "TotalHit! %d", TotalHit) ;
			}
			if (restartgame == false) break;
	}
	// ＤＸライブラリの後始末
	DxLib_End() ;
	
	return 0 ;

}