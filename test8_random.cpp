#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

        int Random[8];
        int Green = GetColor( 0, 255, 0 );      // �΂̐F�R�[�h���擾

        SRand( 123456 ); // �����̏����l��123456�ɐݒ肷��ASRand���Ȃ���΁A����قȂ闐�������������

        Random[0] = GetRand( 100 ); // 0~100�܂ł̗����𐶐�����
        Random[1] = GetRand( 100 );
        Random[2] = GetRand( 100 );
        Random[3] = GetRand( 100 );

        SRand( 123456 ); // �����̏����l��123456�ɍēx�ݒ肷��

        Random[4] = GetRand( 100 ); // 0~100�܂ł̗����𐶐�����
        Random[5] = GetRand( 100 );
        Random[6] = GetRand( 100 );
        Random[7] = GetRand( 100 );

        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

                for( int i=0; i<8; i++ ){
                        DrawFormatString( 0, 20*i, Green, "%d", Random[i] ); // ������`�悷��
                }

        }

        DxLib_End(); // DX���C�u�����I������
        return 0;
} 