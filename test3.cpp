#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	ChangeWindowMode( TRUE ); // �E�B���h�E���[�h�ɐݒ�
	DxLib_Init(); // DX���C�u��������������
	SetDrawScreen( DX_SCREEN_BACK ); //�`���𗠉�ʂɐݒ�

		int x = 0;
		int Handle;     // �摜�i�[�p�n���h��
		Handle = LoadGraph( "�摜/�L�����N�^01.png" ); // �摜�̃��[�h

		while( 1 ){
				if( ProcessMessage() != 0 ){ // ���b�Z�[�W����
						break;//�E�B���h�E�́~�{�^���������ꂽ�烋�[�v�𔲂���
				}
				ClearDrawScreen(); // ��ʂ�����
				DrawGraph( x, 100, Handle, TRUE ); //�摜�̕`��
				x = x + 2; // x��2���₷
				ScreenFlip(); //����ʂ�\��ʂɔ��f
	}
	
	DxLib_End(); // DX���C�u�����I������
	return 0;
}