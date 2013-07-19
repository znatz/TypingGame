#include "typing_game.h"


// Target初期化、画面中の配置
void Inittargets( Targets* t, string* myArray, Game g){
	for(int i = 0; i < g.WORDCOUNTS; ++i)
	{
		t[i].word = myArray[GetRand(g.MAXCOUNTS)].c_str();  //ランダム取り出す、stringからconst TCHAR*変換
		if (i == 0) 
			t[i].x = i * GetRand(g.XSPREAD) + 120;			// 120はDrawFrame中の100より大き
		else 
			t[i].x = t[i-1].xEnd  + GetRand(g.XSPREAD) ;  // <========= TODO!!!! use GetDrawStringWidth
		t[i].xEnd = t[i].x + GetDrawStringWidth(t[i].word, strlen(t[i].word), FALSE);
		t[i].y = 10;
		t[i].y_increment =(int) GetRand(g.DROPSPEED) % g.DROPSPEED + g.MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
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

int Stage(int& _hit, int& _totalhit, 
		  int _sizeX, int _sizeY, int _colorBitDepth, 
		  char* _userInput, int& _inputHandle, 
		  Targets* _targets, Game* g, 
		  /*int* GBuff, */ /*int GBuff,*/ int Frame){
		
		int i;
		
		// Hitしたら、入力領域クリア、Hitリセット
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			// DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	
		
		SetActiveKeyInput( _inputHandle ) ;					// 作成したキー入力ハンドルをアクティブにする
		DrawKeyInputModeString( _sizeX , _sizeY ) ;			// 入力モードを描画準備

		GetKeyInputString( _userInput , _inputHandle ) ;	// 入力取得
		string str(_userInput);								// stringへ変換

		// Hit判断
		for (i=0; i<g->WORDCOUNTS; i++){
			if (_totalhit == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // 単語の間、全角空白をいれないこと
				_targets[i].y += _targets[i].y_increment;
				// g.MISS ++;
			} else {	
				// hit
				PostMessage(GetMainWindowHandle(), WM_TARGET_HIT, _targets[i].x, _targets[i].y);
				_targets[i].word = "";
				_hit ++;
				g->SCORE ++;
				if (_totalhit == 0) break;
				_totalhit--;
			}
		}

		
		DrawFrame(_sizeX, _sizeY);									// 窓の周りを描く
		DrawInfo(_sizeX, _sizeY, g);						// 説明を描く
		DxLib::DrawKeyInputString( 100 , _sizeY-100 , _inputHandle ) ;		// 入力途中の文字列を描画
		return _totalhit;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)	{
		case WM_TARGET_HIT:
			break;
		//case WM_DRAW_BACKGROUND:
		//	ShowBackground((Backgroud_M*) wParam);
		//	break;
	}
	return 0;
}



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	// -----　Window設定
#pragma region initialize_game_data
	Game g = {
		"./文書/words.txt",				// filename
		"./画像/bomb.png",				// flare png
		200,							// max counts
		2,								// word counts
		100,							// xspread
		1,								// dropspeed
		1,								// minspeed
		20,								// fontsize
		0,								// score
		0								// missed
	};
#pragma endregion

	SetHookWinProc(WindowProc);		// Hook Message

	SetOutApplicationLogValidFlag(FALSE);	// Log.txt生成しないように
	SetWindowUserCloseEnableFlag( FALSE ) ;	// メインウインドウの×ボタンを押した時にライブラリが自動的にウインドウを閉じるかどうかのフラグをセットする
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// 最大化ボタンを有効にする
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
	SetDrawMode( DX_DRAWMODE_BILINEAR );	// DrawGraphF系関数つかうため
	
		//int GBuff;
		//GBuff = DxLib::LoadGraph(g.PNGNAME, 0);

	// 文字表示設定
	DxLib::ChangeFont( "ＭＳ 明朝" ) ;
	DxLib::SetFontSize(g.FONTSIZE);

	// -----　ファイルから単語を読み取る
	string* myArray = new string[g.MAXCOUNTS];  // myArrayのサイズはg.WORDCOUNTSより大きはず
	InitData(myArray, g);
	
	// ゲームメインループ
	bool restartgame = true;
	while (true) {
			// 変数初期化
			g.WORDCOUNTS ++;			// ゲームレベル調整、レベルアップした後の処理追加し、レベルデーターを作成してください

			char UserInput[100];		// user input
			int InputHandle;			
			int Hit = 0;				// 1: 1つ単語正解
			int TotalHit = g.WORDCOUNTS;			// g.WORDCOUNTS: Stage内正解回数
			// 背景用変数
			int count = 10;
			Backgroud_M *background = (Backgroud_M*) malloc(sizeof(Backgroud_M) * count);
			InitBackground(background, count);

			// 落ちる単語を選ぶ
			Targets *targets = (Targets*) malloc(sizeof(Targets)*g.WORDCOUNTS);
			Inittargets(targets, myArray, g);

 
			// キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


			// 画面に描画
			while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				// 背景処理
				background->Frame ++;
				ShowBackground(background);
				// if (background->Frame % 100 == 1) PostMessage(GetMainWindowHandle(), WM_DRAW_BACKGROUND, (WPARAM)background, 0);
				#pragma region message_handler
				// バテンボタンを押す時
				if( GetWindowUserCloseFlag() == TRUE ){
					DrawFormatString( background->SizeX/2 - g.FONTSIZE* 10 , background->SizeY/2 - g.FONTSIZE/2 , GetColor(255,255,255), "%s", "ゲームを終了します　何かキーを入力してください") ;
					DrawString(100,100,"ゲームを終了します　何かキーを入力してください",GetColor(255,255,255), 0);
					WaitKey();
					return 0;
				}
				// F1でゲーム終了
				if( CheckHitKey(KEY_INPUT_F1) == 1 ){
					restartgame = false;  // exit game
					break;
				}
				// F2でレベル再開
				if( CheckHitKey(KEY_INPUT_F2) == 1 ){
					g.WORDCOUNTS --;
					break;
				}
				#pragma endregion

				// Stageを描画
				if (Stage(Hit, TotalHit, background->SizeX, background->SizeY, background->ColorBitDepth, UserInput, InputHandle, targets, &g, /*GBuff,*/ background->Frame) == 0) {
					break;				// すべてのtargetsをクリア（０になったら）、restart
				};
			}
			if (restartgame == false) break;
	}

	// ＤＸライブラリの後始末
	DxLib_End() ;
	
	return 0 ;

}