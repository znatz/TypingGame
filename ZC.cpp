#include "typing_game.h"


// Target�������A��ʒ��̔z�u
void Inittargets( Targets* t, string* myArray, Game g){
	for(int i = 0; i < g.WORDCOUNTS; ++i)
	{
		t[i].word = myArray[GetRand(g.MAXCOUNTS)].c_str();  //�����_�����o���Astring����const TCHAR*�ϊ�
		if (i == 0) 
			t[i].x = i * GetRand(g.XSPREAD) + 120;			// 120��DrawFrame����100���傫
		else 
			t[i].x = t[i-1].xEnd  + GetRand(g.XSPREAD) ;  // <========= TODO!!!! use GetDrawStringWidth
		t[i].xEnd = t[i].x + GetDrawStringWidth(t[i].word, strlen(t[i].word), FALSE);
		t[i].y = 10;
		t[i].y_increment =(int) GetRand(g.DROPSPEED) % g.DROPSPEED + g.MINSPEED ;
		t[i].color = GetColor(GetRand(255), GetRand(255), GetRand(255));
	}
}

// �t�@�C������ǂݎ�����P���ۑ�����
void InitData( string* &myArray, Game g){
	ifstream file(g.FILENAME);
	if(file.is_open())
	{
		for(int i = 0; i < g.MAXCOUNTS; ++i)
		{
			file >> myArray[i];
		}
	}
}

void ChangeCallback( void *Data )
{
	// TODO :: add event handler to return to default windows size;
}

int Stage(int& _hit, int& _totalhit, 
		  int _sizeX, int _sizeY, int _colorBitDepth, 
		  char* _userInput, int& _inputHandle, 
		  Targets* _targets, Game* g, 
		  /*int* GBuff, */ /*int GBuff,*/ int Frame, Hit_t* h){
		
		int i;
		
		// Hit������A���͗̈�N���A�AHit���Z�b�g
		if (_hit != 0) { 
			_inputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ; 
			// DrawFormatString( 100, 100, GetColor(255,255,255), "Hit! %d", _hit) ; // debug
			_hit = 0; 
		}	
		
		SetActiveKeyInput( _inputHandle ) ;					// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
		DrawKeyInputModeString( _sizeX , _sizeY ) ;			// ���̓��[�h��`�揀��

		GetKeyInputString( _userInput , _inputHandle ) ;	// ���͎擾
		string str(_userInput);								// string�֕ϊ�

		// �e�P���`��AHit���f
		for (i=0; i<g->WORDCOUNTS; i++){
			if (_totalhit == 0) break;
			if (_targets[i].word == "") continue;
			if ( str.compare(_targets[i].word) != 0) {
				DrawFormatString( _targets[i].x, _targets[i].y, _targets[i].color, "%s", _targets[i].word) ; // �P��̊ԁA�S�p�󔒂�����Ȃ�����
				_targets[i].y += _targets[i].y_increment;
				// g.MISS ++;
			} else {	
				// hit
				h->hit = true;
				h->p.x = _targets[i].x;
				h->p.y = _targets[i].y;
				h->frame = Frame;
				PostMessage(GetMainWindowHandle(), WM_TARGET_HIT, (WPARAM) h, 0);
				_targets[i].word = "";
				_hit ++;
				g->SCORE ++;
				if (_totalhit == 0) break;
				_totalhit--;
			}
		}

		
		DrawFrame(_sizeX, _sizeY);									// ���̎����`��
		DrawInfo(_sizeX, _sizeY, g);						// ������`��
		DxLib::DrawKeyInputString( 100 , _sizeY-100 , _inputHandle ) ;		// ���͓r���̕������`��
		return _totalhit;
}



LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)	{
		case WM_TARGET_HIT:
			((Hit_t*)wParam)->hit = true;		// hit������Aglobal�ϐ�h��hit�ɋL�^����
			break;
	}
	return 0;
}



int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPSTR lpCmdLine, int nCmdShow )
{
	// -----�@Window�ݒ�
#pragma region initialize_game_data
	Game g = {
		"./����/words.txt",				// filename
		"./�摜/bomb.png",				// flare png
		200,							// max counts
		2,								// word counts
		100,							// xspread
		1,								// dropspeed
		1,								// minspeed
		20,								// fontsize
		0,								// score
		0								// missed
	};
#pragma endregion

	SetHookWinProc(WindowProc);		// Hook Message

	SetOutApplicationLogValidFlag(FALSE);	// Log.txt�������Ȃ��悤��
	SetWindowUserCloseEnableFlag( FALSE ) ;	// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����
	SetUseASyncChangeWindowModeFunction( TRUE, ChangeCallback, NULL );										// �ő剻�{�^����L���ɂ���
	ChangeWindowMode(TRUE), DxLib_Init(), SetGraphMode( 1024 , 600 , 32 ), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetDrawMode( DX_DRAWMODE_BILINEAR );	// DrawGraphF�n�֐���������
	
		//int GBuff;
		//GBuff = DxLib::LoadGraph(g.PNGNAME, 0);

	// �����\���ݒ�
	DxLib::ChangeFont( "�l�r ����" ) ;
	DxLib::SetFontSize(g.FONTSIZE);

	// -----�@�t�@�C������P���ǂݎ��
	string* myArray = new string[g.MAXCOUNTS];  // myArray�̃T�C�Y��g.WORDCOUNTS���傫�͂�
	InitData(myArray, g);
	
	// �Q�[�����C�����[�v
	bool restartgame = true;
	while (true) {
			// �ϐ�������
			g.WORDCOUNTS ++;			// �Q�[�����x�������A���x���A�b�v������̏����ǉ����A���x���f�[�^�[���쐬���Ă�������

			char UserInput[100];		// user input
			int InputHandle;			
			int Hit = 0;				// 1: 1�P�ꐳ��
			int TotalHit = g.WORDCOUNTS;			// g.WORDCOUNTS: Stage��������
			// �w�i�p�ϐ�
			int count = 10;
			Backgroud_M *background = (Backgroud_M*) malloc(sizeof(Backgroud_M) * count);
			InitBackground(background, count);

			// ������P���I��
			Targets *targets = (Targets*) malloc(sizeof(Targets)*g.WORDCOUNTS);
			Inittargets(targets, myArray, g);

			// Stage�Ƀp�X���A����hit������AStage��post message�A���b�Z�[�W�����@�\��hit��true�ɂ���A�w�i�����͂���ɂ���ĕ`�悷��B
			Hit_t *h = (Hit_t*) malloc(sizeof(Hit_t));
			h->hit	 = false;
			h->frame = 0;
			 
			// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
			InputHandle = MakeKeyInput( 50 , FALSE , FALSE , FALSE ) ;


			// ��ʂɕ`��
			while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

				// �w�i����
				background->Frame ++;
				ShowBackground(background);
				if (background->Frame - h->frame > 200) h->hit = false;					// 200 frame�̊Ԃ����`�� 
				if (h->hit ) DrawString(100, 100, "Fuck you hit me", GetColor(255,255,255),0);	//�@hit�̕`��
				
				#pragma region message_handler
				// �o�e���{�^����������
				if( GetWindowUserCloseFlag() == TRUE ){
					DrawFormatString( background->SizeX/2 - g.FONTSIZE* 10 , background->SizeY/2 - g.FONTSIZE/2 , GetColor(255,255,255), "%s", "�Q�[�����I�����܂��@�����L�[����͂��Ă�������") ;
					DrawString(100,100,"�Q�[�����I�����܂��@�����L�[����͂��Ă�������",GetColor(255,255,255), 0);
					WaitKey();
					return 0;
				}
				// F1�ŃQ�[���I��
				if( CheckHitKey(KEY_INPUT_F1) == 1 ){
					restartgame = false;  // exit game
					break;
				}
				// F2�Ń��x���ĊJ
				if( CheckHitKey(KEY_INPUT_F2) == 1 ){
					g.WORDCOUNTS --;
					break;
				}
				#pragma endregion

				// Stage��`��
				if (Stage(Hit, TotalHit, background->SizeX, background->SizeY, background->ColorBitDepth, UserInput, InputHandle, targets, &g, /*GBuff,*/ background->Frame, h) == 0) {
					break;				// ���ׂĂ�targets���N���A�i�O�ɂȂ�����j�Arestart
				};
			}
			if (restartgame == false) break;
	}

	// �c�w���C�u�����̌�n��
	DxLib_End() ;
	
	return 0 ;

}