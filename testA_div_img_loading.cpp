#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

	int image[16];
	int image_index = 0;

	LoadDivGraph( "�摜/�L�����N�^10.png" , 16 , 4 , 4 , 32 , 32 , image ); // �摜�̕����ǂݍ���

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				DrawGraph( 0, 0, image[8], TRUE );      // �摜��\��

				DrawGraph( 0, 50, image[image_index], TRUE );      // �摜�񒆂�1��\��
				image_index = (image_index + 1 ) % 16 ;  

		}

		DxLib_End(); // DX���C�u�����I������
		return 0;
}