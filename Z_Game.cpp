#include "DxLib.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define FILENAME "./����/words.txt"

 #include "DxLib.h"

string *Getwords(){
	ifstream file(FILENAME);
	string* myArray = new string[5];
	if(file.is_open())
	{
		for(int i = 0; i < 5; ++i)
		{
			file >> myArray[i];
		}
	}
	return myArray;
}


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode( TRUE );
	string* words = new string[5];
	words = Getwords();

	// �c�w���C�u�����̏�����
	if( DxLib_Init() == -1 ) return -1 ;


	// ��ʂɕ`��
	DrawString( 0, 10, words[0].c_str(), GetColor( 255,255,255 ) ) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
	DrawString( 0, 30, words[1].c_str(), GetColor( 255,255,255 ) ) ;


	// �L�[���͑҂�
	WaitKey() ;

	// �c�w���C�u�����̌�n��
	DxLib_End() ;

	return 0 ;
}