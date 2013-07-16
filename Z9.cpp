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

// Target������
void Inittargets( Targets* t, string* myArray, Game g){
	for(int i = 0; i < g.WORDCOUNTS; ++i)
	{
		t[i].x = g.FONTSIZE * i * 10 + GetRand(g.XSPREAD);
		t[i].y = 10;
		t[i].y_increment =(int) GetRand(g.DROPSPEED) % g.DROPSPEED + g.MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(g.MAXCOUNTS)].c_str();  //�����_�����o���Astring����const TCHAR*�ϊ�
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

int Stage(int& _hit, int& _totalhit, int _sizeX, int _sizeY, int _colorBitDepth, char* _userInput, int& _inputHandle, Targets* _targets, Game g){
		
		int i;
		
		// Hit������A���͗̈�N���A�AHit���Z�b�g
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	
		
		SetActiveKeyInput( _inputHandle ) ;				// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
		DrawKeyInputModeString( _sizeX , _sizeY ) ;		// ���̓��[�h��`��		
		DrawKeyInputString( 0 , 0 , _inputHandle ) ;		// ���͓r���̕������`��
		GetKeyInputString( _userInput , _inputHandle ) ;
		string str(_userInput);

		// Hit���f
		for (i=0; i<g.WORDCOUNTS; i++){
			if (_totalhit == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
				_targets[i].y += _targets[i].y_increment;
			} else {								// hit
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
	// -----�@Window�ݒ�
	SetOutApplicationLogValidFlag(FALSE); // Log.txt�������Ȃ��悤��
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// �ő剻�{�^����L���ɂ���
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	Game g = {
		"./����/words.txt",		// filename
		200,					// max counts
		2,						// word counts
		100,					// xspread
		1,						// dropspeed
		0.1,					// minspeed
		10						// fontsize
	};

	// -----�@�t�@�C������P���ǂݎ��
	string* myArray = new string[g.MAXCOUNTS];  // myArray�̃T�C�Y��g.WORDCOUNTS���傫�͂�
	InitData(myArray, g);

	bool restartgame = true;
	while (true) {
			// �ϐ�������
			int SizeX;					// ��ʃT�C�X
			int SizeY;					// ��ʃT�C�X
			int ColorBitDepth;			// ��ʐF
			char UserInput[100];			// user input
			int InputHandle;			
			int Hit = 0;				// 1: 1�P�ꐳ��
			int TotalHit = g.WORDCOUNTS;			// g.WORDCOUNTS: Stage��������

			GetScreenState( &SizeX , &SizeY , &ColorBitDepth );
			SetFontSize(g.FONTSIZE);
			Targets *targets = (Targets*) malloc(sizeof(Targets)*g.WORDCOUNTS);
			Inittargets(targets, myArray, g);

 
			// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


			// ��ʂɕ`��
			while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
				if( CheckHitKey(KEY_INPUT_F1) == 1 ){
					restartgame = false;  // exit game
					break;
				}
				if (Stage(Hit, TotalHit, SizeX, SizeY, ColorBitDepth, UserInput, InputHandle, targets, g) == 0) {
					break;				// exit stage restart game
				};
				DrawFormatString( 100, 200, GetColor(255,255,255), "TotalHit! %d", TotalHit) ;
			}
			if (restartgame == false) break;
	}
	// �c�w���C�u�����̌�n��
	DxLib_End() ;
	
	return 0 ;

}