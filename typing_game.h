#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#define WM_TARGET_HIT		(WM_USER + 1)		//ユーザー定義メッセージ	//これを追加
#define WM_DRAW_BACKGROUND	(WM_USER + 2)

typedef struct GAMEDATA Game;
struct GAMEDATA {
	string FILENAME ; 
	const TCHAR* PNGNAME	;
	int MAXCOUNTS   ; 
	int WORDCOUNTS  ;
	int XSPREAD	    ;
	int DROPSPEED   ;
	double MINSPEED ; 
	int FONTSIZE    ;
	int SCORE		;
	int MISS		;
};

typedef struct TARGETS Targets;
struct TARGETS {
	int x;
	int xEnd;
	int y;
	int y_increment;
	int color;
	const TCHAR* word;
};

typedef struct HIT Hit_t;
struct HIT {
	bool hit ;		// hit or not
	POINT p;		// hitpoint
	int frame;		// hitした時のframe
};

typedef struct BACKGROUND Backgroud_M;
struct BACKGROUND{
		int SizeX;				// 画面横サイズ
		int SizeY;				// 画面縦サイズ
		int ColorBitDepth;		// 画面色ビット深さ
		int Frame;				// frame計数
		int count;				// 円の数
		int* rArr;				// 円達の半径
		int* refreshArr;		// 円達の描画間隔
		int* repoRadArr;		// 画面中心と円の距離
};

void InitBackground(Backgroud_M * background, int count);
void ShowBackground(Backgroud_M* background);
void DrawInfo(int x, int y, Game* g);
void DrawFrame(int x, int y);