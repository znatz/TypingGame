#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

		int x = 0;
		double angle = 0;
		int Handle1, Handle2;     // �摜�i�[�p�n���h��
		Handle1 = LoadGraph( "�摜/�L�����N�^01.png" ); // �摜�̃��[�h
		Handle2 = LoadGraph( "�摜/�L�����N�^01.png" ); // �摜�̃��[�h

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				DrawGraph( x, 100, Handle1, TRUE ); //�摜�̕`��
				DrawGraph( x, 110, Handle2, TRUE ); //�摜�̕`��
				DrawRotaGraph(200, 200, 1.0, angle, Handle1, TRUE);
				x = x + 2; // x��2���₷
				angle += 2;

				SetDrawBlendMode( DX_BLENDMODE_ALPHA,  128 );		//�u�����h���[�h����(128/255)�ɐݒ�
				DrawRotaGraph(200, 400, 1.0, angle, Handle1, TRUE);
				SetDrawBlendMode( DX_BLENDMODE_NOBLEND,  0 );		//�u�����h���[�h���I�t

		}
		
		DxLib_End(); // DX���C�u�����I������
		return 0;
} 