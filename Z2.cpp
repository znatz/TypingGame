#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./����/words.txt"
#define WORDCOUNTS 7
#define DROPSPEED 1
#define FONTSIZE 10

const TCHAR** Getwords(){
	ifstream file(FILENAME);
	string* myArray = new string[WORDCOUNTS];
	const TCHAR** result = new const TCHAR* [WORDCOUNTS];
	if(file.is_open())
	{
		for(int i = 0; i < WORDCOUNTS; ++i)
		{
			file >> myArray[i];
			result[i] = myArray[i].c_str();  // string -> const TCHAR*
		}
	}
	return result;
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
	words = Getwords();

	// ��ʂɕ`��
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

		for (i=0; i<WORDCOUNTS; i++){
			// DrawString( 10 + i*FONTSIZE*5, incY, words[i], GetColor( 255,255,255 ) ) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
			DrawFormatString( 10 + i*FONTSIZE*5, incY, GetColor( 255,255,255 ), "%s", words[i]) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
		}
		incY += DROPSPEED;
	}

	// �c�w���C�u�����̌�n��
	DxLib_End() ;

	return 0 ;

}