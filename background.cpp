#include "typing_game.h"

void InitBackground(Backgroud_M * background, int count){
		int SizeX;					// 画面サイス
		int SizeY;					// 画面サイス
		int ColorBitDepth;			// 画面色
		GetScreenState( &SizeX , &SizeY , &ColorBitDepth );
		int i;
		background->count = count;
		background->rArr = new int[count];
		background->refreshArr = new int[count];
		background->repoRadArr = new int[count];
		background->Frame = 0;
		background->SizeX = SizeX;
		background->SizeY = SizeY;
		background->ColorBitDepth = ColorBitDepth;
		for (i=0; i<count; i++) {
			background->rArr[i] = GetRand(10);
			background->refreshArr[i] = GetRand(10);
			background->repoRadArr[i] = GetRand(10);
		}
}

void ShowBackground(Backgroud_M* background){
	double MidX = background->SizeX / 2;
	double MidY = background->SizeY / 2;
	double _Frame = (double) background->Frame;
	int i;
	for (i=0; i<background->count; i++){
		double Rad = _Frame/background->repoRadArr[i];
		double CenterX = Rad*cos(_Frame/background->refreshArr[i]) * (i + 1) + MidX - background->rArr[i]/2;  // Background 200 * 200
		double CenterY = Rad*sin(_Frame/background->refreshArr[i]) * (i + 1) + MidY - background->rArr[i]/2;
		if (CenterX < background->SizeX && CenterY < background->SizeY)
			DrawCircle(CenterX, CenterY, background->rArr[i], GetColor(255,255,255),1);
	}
}

void DrawInfo(int x, int y, Game* g){
	int tempFontSize = GetFontSize();
	SetFontSize(15);
	int color = GetColor(250, 250, 250);
	DrawFormatString( 100, y-50, color, "F1でゲーム終了、F2でレベル再開") ; 
	DrawFormatString( 100, y-25, color, "ミス：%d　　あたり：%d", g->MISS, g->SCORE) ; 
	SetFontSize(tempFontSize);
}

void DrawFrame(int x, int y){
	// 入力のところ
	DrawBox(100, y-100, x-100, y-50, GetColor(56,38,25), TRUE);
	// 口
	int color = GetColor(110, 41, 7); 
	DrawLine(0, 0, 0, y, color, 100);
	DrawLine(0, 0, x, 0, color, 100);
	DrawLine(0, y, x, y, color, 100);
	DrawLine(x, 0, x, y, color, 100);
}