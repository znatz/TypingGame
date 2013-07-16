#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nCmdShow )
{
    char String[ 256 ] ;
    int InputHandle ;

    // �c�w���C�u�����̏�����
    if( DxLib_Init() == -1 ) return -1 ;

    // �`���𗠂ɂ���
    SetDrawScreen( DX_SCREEN_BACK ) ;

    // �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
    InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;

    // �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
    SetActiveKeyInput( InputHandle ) ;

    // �L�[���͏I���҂����[�v
    // (ProcessMessage�����[�v���Ƃɍs��)
    while( !ProcessMessage() )
    {
        // ���͂��I�����Ă���ꍇ�͏I��
        if( CheckKeyInput( InputHandle ) != 0 ) break ;

        // ��ʂ̏�����
        ClearDrawScreen() ;

        // ���̓��[�h��`��
        DrawKeyInputModeString( 640 , 480 ) ; 

        // ���͓r���̕������`��
        DrawKeyInputString( 0 , 0 , InputHandle ) ;

        // ����ʂ̓��e��\��ʂɔ��f������
        ScreenFlip() ;
    }

    // ���͂��ꂽ��������擾
    GetKeyInputString( String , InputHandle ) ;

    // �p�ς݂̃C���v�b�g�n���h�����폜����
    DeleteKeyInput( InputHandle ) ;

    // ��ʂ̏�����
    ClearDrawScreen() ;

    // ���͂��ꂽ���������ʂɕ\������
    DrawString( 0 , 0 , "���Ȃ������͂����������" , GetColor( 255 , 255 , 255 ) ) ;
    DrawString( 0 , 16 , String , GetColor( 255 , 255 , 255 ) ) ;

    // ����ʂ̓��e��\��ʂɔ��f������
    ScreenFlip() ;

    // �L�[���͑҂�
    WaitKey() ;

    // �c�w���C�u�����̎g�p�I��
    DxLib_End() ;

    // �I��
    return 0 ;
}