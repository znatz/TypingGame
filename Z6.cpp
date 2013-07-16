#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./����/words.txt"
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
//void shuffle(T arr[], int n){   // n�͔z��̒���
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
	// �P���ǂݎ��
	ifstream file(FILENAME);
	string* myArray = new string[MAXCOUNTS];  // myArray�̃T�C�Y��WORDCOUNTS���傫�͂�
	if(file.is_open())
	{
		for(int i = 0; i < MAXCOUNTS; ++i)
		{
			file >> myArray[i];
		}
	}

	// targets������
	for(int i = 0; i < WORDCOUNTS; ++i)
	{
		file >> myArray[i];
		t[i].x = FONTSIZE * i * 5 ;
		t[i].y = 10;
		t[i].y_increment = GetRand(DROPSPEED) + 0.1 ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
		t[i].word = myArray[GetRand(MAXCOUNTS)].c_str();  //�����_�����o���Astring����const TCHAR*�ϊ�
	}
}

void ChangeCallback( void *Data )
{
	// TODO :: add event handler to return to default windows size;
}

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	SetOutApplicationLogValidFlag(FALSE); // Log.txt�������Ȃ��悤��
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// �ő剻�{�^����L���ɂ���
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	

	// �ϐ�������
	int i;
	int SizeX;					// ��ʃT�C�X
	int SizeY;					// ��ʃT�C�X
	int ColorBitDepth;			// ��ʐF
	char UserInput[10];			// user input
	int InputHandle;			
	int Hit = 0;
	const TCHAR** words = new const TCHAR* [WORDCOUNTS];

	GetScreenState( &SizeX , &SizeY , &ColorBitDepth );
	SetFontSize(FONTSIZE);
	Targets targets[WORDCOUNTS] ;
	Inittargets(targets);

 
	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


	// ��ʂɕ`��
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		if (Hit != 0) { InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; Hit = 0; }
		// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
		SetActiveKeyInput( InputHandle ) ;
		// ���̓��[�h��`��
		DrawKeyInputModeString( SizeX , SizeY ) ; 
		// ���͓r���̕������`��
		DrawKeyInputString( 0 , 0 , InputHandle ) ;
		GetKeyInputString( UserInput , InputHandle ) ;
		string str(UserInput);

		// ���ʂ̕`��
		for (i=0; i<WORDCOUNTS; i++){
			if (targets[i].word == "") continue;
			if ( str.compare(targets[i].word) != 0) {
				DrawFormatString( targets[i].x, targets[i].y, targets[i].color, "%s", targets[i].word) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
				targets[i].y += targets[i].y_increment;
			} else {
				targets[i].word = "";
				Hit ++;
			}
		}
	}

	// �c�w���C�u�����̌�n��
	DxLib_End() ;
	
	return 0 ;

}