#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
		 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode( TRUE );
	char Name[ 31 ] ;

	// �c�w���C�u�����̏�����
	if( DxLib_Init() == -1 ) return -1 ;

	// ���O���͎w��������̕`��
	DrawString( 0 , 0 , "���O����͂��Ă�������" , GetColor( 255 , 255 , 255 ) ) ;

	// ���O�̓���
	KeyInputString( 0 , 16 , 30 , Name , FALSE ) ;

	// ��ʂ̏�����
	ClearDrawScreen() ;

	// ���O�̕\��
	DrawString( 0 , 0 , "���Ȃ��̖��O��" , GetColor( 255 , 255 , 255 ) ) ;
	DrawString( 0 , 16 , Name ,  GetColor( 255 , 255 , 255 ) ) ;
		
	// �L�[���͑҂�    
	WaitKey() ;

	// �c�w���C�u�����̎g�p�I��
	DxLib_End() ;

	// �I��
	return 0 ;
}