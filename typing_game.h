#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

#define WM_TARGET_HIT		(WM_USER + 1)		//���[�U�[��`���b�Z�[�W	//�����ǉ�
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
	int frame;		// hit��������frame
};

typedef struct BACKGROUND Backgroud_M;
struct BACKGROUND{
		int SizeX;				// ��ʉ��T�C�Y
		int SizeY;				// ��ʏc�T�C�Y
		int ColorBitDepth;		// ��ʐF�r�b�g�[��
		int Frame;				// frame�v��
		int count;				// �~�̐�
		int* rArr;				// �~�B�̔��a
		int* refreshArr;		// �~�B�̕`��Ԋu
		int* repoRadArr;		// ��ʒ��S�Ɖ~�̋���
};

void InitBackground(Backgroud_M * background, int count);
void ShowBackground(Backgroud_M* background);
void DrawInfo(int x, int y, Game* g);
void DrawFrame(int x, int y);