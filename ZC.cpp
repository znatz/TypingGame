#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

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

// Target�������A��ʒ��̔z�u
void Inittargets( Targets* t, string* myArray, Game g){
	for(int i = 0; i < g.WORDCOUNTS; ++i)
	{
		t[i].word = myArray[GetRand(g.MAXCOUNTS)].c_str();  //�����_�����o���Astring����const TCHAR*�ϊ�
		if (i == 0) 
			t[i].x = i * GetRand(g.XSPREAD) + 120;			// 120��DrawFrame����100���傫
		else 
			t[i].x = t[i-1].xEnd  + GetRand(g.XSPREAD) ;  // <========= TODO!!!! use GetDrawStringWidth
		t[i].xEnd = t[i].x + GetDrawStringWidth(t[i].word, strlen(t[i].word), FALSE);
		t[i].y = 10;
		t[i].y_increment =(int) GetRand(g.DROPSPEED) % g.DROPSPEED + g.MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
	}
}

// �t�@�C������ǂݎ�����P���ۑ�����
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

void DrawFrame(int x, int y){
	DrawBox(100, y-100, x-100, y-50, GetColor(26,5,0), TRUE);
	DrawLine(0, 0, 0, y, GetColor(173,114,75), 100);
	DrawLine(0, 0, x, 0, GetColor(173,114,75), 100);
	DrawLine(0, y, x, y, GetColor(173,114,75), 100);
	DrawLine(x, 0, x, y, GetColor(173,114,75), 100);
}

int Stage(int& _hit, int& _totalhit, 
		  int _sizeX, int _sizeY, int _colorBitDepth, 
		  char* _userInput, int& _inputHandle, 
		  Targets* _targets, Game g, int* GBuff){
		
		int i;
		
		// Hit������A���͗̈�N���A�AHit���Z�b�g
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	
		
		SetActiveKeyInput( _inputHandle ) ;					// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
		DrawKeyInputModeString( _sizeX , _sizeY ) ;			// ���̓��[�h��`��
		//DrawFrame(_sizeX, _sizeY);
		DrawKeyInputString( 100 , _sizeY-100 , _inputHandle ) ;		// ���͓r���̕������`��
		GetKeyInputString( _userInput , _inputHandle ) ;
		string str(_userInput);

		// Hit���f
		for (i=0; i<g.WORDCOUNTS; i++){
			if (_totalhit == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
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
		DrawFrame(_sizeX, _sizeY);
		return _totalhit;
}



void ShowBackground(int KeyFrame, int SizeX, int SizeY, int* r, int* refresh, int* repoRad, int count){
	double MidX = SizeX / 2;
	double MidY = SizeY / 2;
	double _Frame = (double) KeyFrame;
	int i;
	for (i=0; i<count; i++){
		double Rad = _Frame/repoRad[i];
		double CenterX = Rad*cos(_Frame/refresh[i]) + MidX - r[i]/2;  // Background 200 * 200
		double CenterY = Rad*sin(_Frame/refresh[i]) + MidY - r[i]/2;
		DrawCircle(CenterX, CenterY, r[i], GetColor(255,255,255),1);
	}
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	// -----�@Window�ݒ�
	Game g = {
		"./����/words.txt",				// filename
		"./�摜/��01.png",				// flare png
		200,							// max counts
		2,								// word counts
		100,							// xspread
		1,								// dropspeed
		1,							// minspeed
		20								// fontsize
	};
	SetOutApplicationLogValidFlag(FALSE); // Log.txt�������Ȃ��悤��
	SetWindowUserCloseEnableFlag( FALSE ) ;// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// �ő剻�{�^����L���ɂ���
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetDrawMode( DX_DRAWMODE_BILINEAR );
	// ����Effect�p�摜�����[�h����
	int GBuff[8];
	LoadDivGraph("./�摜/explosion.png", 8, 8, 1, 40, 40, GBuff);	
	// �w�i�摜�����[�h����
		//int Background;
		//Background = LoadGraph(g.PNGNAME, FALSE);

	// �����\���ݒ�
	ChangeFont( "�l�r ����" ) ;
	SetFontSize(g.FONTSIZE);

	// -----�@�t�@�C������P���ǂݎ��
	string* myArray = new string[g.MAXCOUNTS];  // myArray�̃T�C�Y��g.WORDCOUNTS���傫�͂�
	InitData(myArray, g);
	
	// �Q�[�����C�����[�v
	bool restartgame = true;
	while (true) {
			// �ϐ�������
			g.WORDCOUNTS ++;			// �Q�[�����x�������A���x���A�b�v������̏����ǉ����A���x���f�[�^�[���쐬���Ă�������
			int SizeX;					// ��ʃT�C�X
			int SizeY;					// ��ʃT�C�X
			int ColorBitDepth;			// ��ʐF
			char UserInput[100];		// user input
			int InputHandle;			
			int Hit = 0;				// 1: 1�P�ꐳ��
			int TotalHit = g.WORDCOUNTS;			// g.WORDCOUNTS: Stage��������
			// �w�i�p�ϐ�
			int Frame = 0;				// frame�v��
			int count = 10;
			int* rArr = new int[count];
			int* refreshArr= new int[count];
			int* repoRadArr= new int[count];
			int i;
			for (i=0; i<count; i++) {
				rArr[i] = GetRand(10);
				refreshArr[i] = GetRand(10);
				repoRadArr[i] = GetRand(10);
			}

			GetScreenState( &SizeX , &SizeY , &ColorBitDepth );

			// ������P���I��
			Targets *targets = (Targets*) malloc(sizeof(Targets)*g.WORDCOUNTS);
			Inittargets(targets, myArray, g);

 
			// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


			// ��ʂɕ`��
			while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				// �w�i����
				Frame ++;
				ShowBackground(Frame, SizeX, SizeY, rArr, refreshArr, repoRadArr, count);

				// �o�e���{�^����������
				if( GetWindowUserCloseFlag() == TRUE ){
					DrawFormatString( SizeX/2 - g.FONTSIZE* 10 , SizeY/2 - g.FONTSIZE/2 , GetColor(255,255,255), "%s", "�Q�[�����I�����܂��@�����L�[����͂��Ă�������") ;
					DrawString(100,100,"�Q�[�����I�����܂��@�����L�[����͂��Ă�������",GetColor(255,255,255), 0);
					WaitKey();
					return 0;
				}
				// F1�ŃQ�[���I��
				if( CheckHitKey(KEY_INPUT_F1) == 1 ){
					restartgame = false;  // exit game
					break;
				}
				// F2�Ń��x���ĊJ
				if( CheckHitKey(KEY_INPUT_F2) == 1 ){
					g.WORDCOUNTS --;
					break;
				}
				// Stage��`��
				if (Stage(Hit, TotalHit, SizeX, SizeY, ColorBitDepth, UserInput, InputHandle, targets, g, GBuff) == 0) {
					break;				// exit stage restart game
				};

				// Debug
				// DrawFormatString( 100, 200, GetColor(255,255,255), "TotalHit! %d", TotalHit) ;
			}
			if (restartgame == false) break;
	}

	// �c�w���C�u�����̌�n��
	DxLib_End() ;
	
	return 0 ;

}