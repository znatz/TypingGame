#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
        LPSTR lpCmdLine, int nCmdShow )
{
    char String[ 256 ] ;
    int InputHandle ;

    // ＤＸライブラリの初期化
    if( DxLib_Init() == -1 ) return -1 ;

    // 描画先を裏にする
    SetDrawScreen( DX_SCREEN_BACK ) ;

    // キー入力ハンドルを作る(キャンセルなし全角文字有り数値入力じゃなし)
    InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;

    // 作成したキー入力ハンドルをアクティブにする
    SetActiveKeyInput( InputHandle ) ;

    // キー入力終了待ちループ
    // (ProcessMessageをループごとに行う)
    while( !ProcessMessage() )
    {
        // 入力が終了している場合は終了
        if( CheckKeyInput( InputHandle ) != 0 ) break ;

        // 画面の初期化
        ClearDrawScreen() ;

        // 入力モードを描画
        DrawKeyInputModeString( 640 , 480 ) ; 

        // 入力途中の文字列を描画
        DrawKeyInputString( 0 , 0 , InputHandle ) ;

        // 裏画面の内容を表画面に反映させる
        ScreenFlip() ;
    }

    // 入力された文字列を取得
    GetKeyInputString( String , InputHandle ) ;

    // 用済みのインプットハンドルを削除する
    DeleteKeyInput( InputHandle ) ;

    // 画面の初期化
    ClearDrawScreen() ;

    // 入力された文字列を画面に表示する
    DrawString( 0 , 0 , "あなたが入力した文字列は" , GetColor( 255 , 255 , 255 ) ) ;
    DrawString( 0 , 16 , String , GetColor( 255 , 255 , 255 ) ) ;

    // 裏画面の内容を表画面に反映させる
    ScreenFlip() ;

    // キー入力待ち
    WaitKey() ;

    // ＤＸライブラリの使用終了
    DxLib_End() ;

    // 終了
    return 0 ;
}