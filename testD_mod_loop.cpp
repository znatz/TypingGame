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

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

        int Count = 0; // �J�E���^
        int Handle = LoadGraph("�摜/�L�����N�^01.png"); // �摜�����[�h

        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, �L�[�̓��͏�ԍX�V)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){

                DrawGraph(   0, Count% 50, Handle, TRUE ); // ����  50�J�E���g �Ń��[�v�\������
                DrawGraph( 100, Count%100, Handle, TRUE ); // ���� 100�J�E���g �Ń��[�v�\������
                DrawGraph( 200, Count%150, Handle, TRUE ); // ���� 150�J�E���g �Ń��[�v�\������

                Count++; // �J�E���^���Z

        }

        DxLib_End(); // DX���C�u�����I������
        return 0;
}