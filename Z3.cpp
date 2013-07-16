#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./����/words.txt"
#define WORDCOUNTS 7
#define DROPSPEED 1
#define FONTSIZE 10


//class Targets            //�N���X�錾
//{
//public:
//	int x_init;
//	int y_increment;
//	const TCHAR* word;
//};

typedef struct TARGETS Targets;
struct TARGETS {
	int x_init;
	int y_increment;
	const TCHAR* word;
};


//const TCHAR** Getwords(){
//	ifstream file(FILENAME);
//	string* myArray = new string[WORDCOUNTS];
//	const TCHAR** result = new const TCHAR* [WORDCOUNTS];
//	if(file.is_open())
//	{
//		for(int i = 0; i < WORDCOUNTS; ++i)
//		{
//			file >> myArray[i];
//			result[i] = myArray[i].c_str();  // string -> const TCHAR*
//		}
//	}
//	return result;
//}

void Inittargets( Targets* t){
	ifstream file(FILENAME);
	string* myArray = new string[WORDCOUNTS];
	const TCHAR** result = new const TCHAR* [WORDCOUNTS];
	if(file.is_open())
	{
		for(int i = 0; i < WORDCOUNTS; ++i)
		{
			file >> myArray[i];
			t[i].x_init = 10*i;
			t[i].y_increment = 10;
			t[i].word = new const TCHAR[50];
			t[i].word = myArray[i].c_str();  // string -> const TCHAR*
		}
	}
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	
	// �ϐ�������
	const TCHAR** words = new const TCHAR* [WORDCOUNTS];
	int incY = 0;
	int i;
	SetFontSize(FONTSIZE);

	
	// �P���ǂݍ���
	//words = Getwords();

	// temp
	Targets targets[WORDCOUNTS] ;
	Inittargets(targets);
	//for (i=0; i<WORDCOUNTS; i++){
	//	targets[i].x_init = 10*i;
	//	targets[i].y_increment = 10;
	//	targets[i].word = new const TCHAR[50];
	//	targets[i].word = words[i];
	//}
	


	// ��ʂɕ`��
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		for (i=0; i<WORDCOUNTS; i++){
			// DrawString( 10 + i*FONTSIZE*5, incY, words[i], GetColor( 255,255,255 ) ) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
			DrawFormatString( 10 + i*FONTSIZE*5, incY, GetColor( 255,255,255 ), "%s", targets[i].word) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
		}
		incY += DROPSPEED;
	}

	// �c�w���C�u�����̌�n��
	DxLib_End() ;
	
	return 0 ;

}