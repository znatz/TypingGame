#include "DxLib.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
		 LPSTR lpCmdLine, int nCmdShow )
{
	ChangeWindowMode( TRUE );
	char Name[ 31 ] ;

	// ＤＸライブラリの初期化
	if( DxLib_Init() == -1 ) return -1 ;

	// 名前入力指示文字列の描画
	DrawString( 0 , 0 , "名前を入力してください" , GetColor( 255 , 255 , 255 ) ) ;

	// 名前の入力
	KeyInputString( 0 , 16 , 30 , Name , FALSE ) ;

	// 画面の初期化
	ClearDrawScreen() ;

	// 名前の表示
	DrawString( 0 , 0 , "あなたの名前は" , GetColor( 255 , 255 , 255 ) ) ;
	DrawString( 0 , 16 , Name ,  GetColor( 255 , 255 , 255 ) ) ;
		
	// キー入力待ち    
	WaitKey() ;

	// ＤＸライブラリの使用終了
	DxLib_End() ;

	// 終了
	return 0 ;
}