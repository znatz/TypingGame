// ��R�̃L�[�̓��͏�Ԃ��m�F���������́A������̊֐����Ă�ł����̂Ŕ�����ł��B
// �����ŁA�S�Ă܂Ƃ߂Ď擾�ł��� GetHitKeyStateAll�֐� ���g�p���܂��B

#include "DxLib.h"

int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey(){
		char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
		GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
		for( int i=0; i<256; i++ ){ 
				if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
						Key[i]++;     // ���Z�A�������ςȂ����肽��
				} else {              // ������Ă��Ȃ����
						Key[i] = 0;   // 0�ɂ���
				}
		}
		return 0;
}

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

		int x=0;

		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̏�ԍX�V)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0 ){

				DrawFormatString( x, 0, GetColor(255,255,255), "?!" ); // x,0 �̈ʒu�ɔ��� ?! ��`��

				if( Key[KEY_INPUT_RIGHT] == 1 ){ // �E�L�[�������ꂽ�u�ԂȂ�
						x = x + 50;                 // x��50���Z
				}

				if( Key[KEY_INPUT_Z] >= 60 ){ // 60�t���[���ȏ㉟����Ă�����
					DrawFormatString( 0, 0, GetColor(255,255,255), "<-" ); // ������\��
				}
		}

		DxLib_End(); // DX���C�u�����I������
		return 0;
} 