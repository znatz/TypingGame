#include "DxLib.h"

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey(){
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for( int i=0; i<256; i++ ){ 
		if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		} else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int x=320, y=240;
int Handle;

void gpCalc(){
	if( Key[ KEY_INPUT_RIGHT ] >= 1 ){
		x++;
	}
	if( Key[ KEY_INPUT_DOWN  ] >= 1 ){
		y++;
	}
	if( Key[ KEY_INPUT_LEFT  ] >= 1 ){
		x--;
	}
	if( Key[ KEY_INPUT_UP    ] >= 1 ){
		y--;
	}
}

void gpDraw(){
		DrawRotaGraph( x, y, 1.0, 0.0, Handle, TRUE );
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

		Handle = LoadGraph("�摜/�L�����N�^01.png");

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̍X�V)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){

				gpCalc();

				gpDraw();

	}

	DxLib_End(); // DX���C�u�����I������
	return 0;
}