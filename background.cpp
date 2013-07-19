#include "typing_game.h"

void InitBackground(Backgroud_M * background, int count){
		int SizeX;					// ��ʃT�C�X
		int SizeY;					// ��ʃT�C�X
		int ColorBitDepth;			// ��ʐF
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
	DrawFormatString( 100, y-50, color, "F1�ŃQ�[���I���AF2�Ń��x���ĊJ") ; 
	DrawFormatString( 100, y-25, color, "�~�X�F%d�@�@������F%d", g->MISS, g->SCORE) ; 
	SetFontSize(tempFontSize);
}

void DrawFrame(int x, int y){
	// ���͂̂Ƃ���
	DrawBox(100, y-100, x-100, y-50, GetColor(56,38,25), TRUE);
	// ��
	int color = GetColor(110, 41, 7); 
	DrawLine(0, 0, 0, y, color, 100);
	DrawLine(0, 0, x, 0, color, 100);
	DrawLine(0, y, x, y, color, 100);
	DrawLine(x, 0, x, y, color, 100);
}