#include "DxLib.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

			DWORD color = GetColor(53,108,33);
			
		// while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
		while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

			DrawFormatString(250,250,color,"����������Ȃ��I");	
			DrawFormatString(250,300,color,"%d�ʖڂ̃r�[��", 3);	

		}
		
		DxLib_End(); // DX���C�u�����I������
		return 0;
} 