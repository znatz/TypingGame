#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

        int Handle, Count=0;
        Handle = LoadSoundMem("�T�E���h/1up.wav"); // �T�E���h/1up.wav�����[�h���A���ʔԍ���Handle�Ɋi�[

        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

                if( Count % 120 == 0 ){ // 2�b�Ɉ�x
                        PlaySoundMem( Handle, DX_PLAYTYPE_BACK ); // ���ʉ����Đ�����
                }

                Count++;

        }

        DxLib_End(); // DX���C�u�����I������
        return 0;
} 