#include "SceneMgr.h"
#include "DxLib.h"
#include "Title.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"

static SCENE scene = SCENE_TITLE;       //�V�[���Ǘ��ϐ�
static SCENE nextScene = SCENE_NONE;    //���̃V�[���Ǘ��ϐ�

static void InitializeModule(SCENE scene); //�w�胂�W���[��������������
static void FinalizeModule(SCENE scene);   //�w�胂�W���[���̏I���������s��

// ������
void SceneMgr::Initialize()
{
	InitializeModule(scene);
}

//�I������
void SceneMgr::Finalize() 
{
	FinalizeModule(scene);
}

void SceneMgr::All()
{
	// �^�C�g���N���X�쐬
	Title &title = Title::GetInstance();
	// �Q�[���N���X����
	Game &game = Game::GetInstance();
	// �Q�[���N���A�N���X����
	GameClear &gameClear = GameClear::GetInstance();
	// �Q�[���I�[�o�[�N���X����
	GameOver &gameOver = GameOver::GetInstance();

	if (fadeIn)
	{
		if (!FadeInScreen(5)) fadeIn = false;
	}
	else if (fadeOut)
	{
		if (!FadeOutScreen(5))
		{
			FinalizeModule(scene);		//���݂̃V�[���̏I�����������s
			scene = nextScene;			//���̃V�[�������݂̃V�[���Z�b�g
			nextScene = SCENE_NONE;     //���̃V�[�������N���A
			InitializeModule(scene);    //���݂̃V�[����������
			fadeOut = false;
			fadeIn = true;
		}
	}

	if (nextScene != SCENE_NONE)	     //���̃V�[�����Z�b�g����Ă�����
	{
		fadeOut = true;
	}
		

	//�V�[���ɂ���ď����𕪊�
	switch (scene)
	{       
	case SCENE_TITLE:   
		title.All();
		break;
	case SCENE_GAME:
		game.All();
		break;
	case SCENE_CLEAR:
		gameClear.All();
		break;
	case SCENE_GAMEOVER:
		gameOver.All();
		break;
	}
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr::ChangeScene(SCENE NextScene)
{
	nextScene = NextScene;    //���̃V�[�����Z�b�g����
}

// ����scene���W���[��������������
static void InitializeModule(SCENE scene)
{
	// �^�C�g���N���X�쐬
	Title &title = Title::GetInstance();
	// �Q�[���N���X����
	Game &game = Game::GetInstance();
	// �Q�[���N���A�N���X����
	GameClear &gameClear = GameClear::GetInstance();
	// �Q�[���I�[�o�[�N���X����
	GameOver &gameOver = GameOver::GetInstance();

	//�V�[���ɂ���ď����𕪊�
	switch (scene)
	{
	case SCENE_TITLE:
		title.Initialize();
		break;
	case SCENE_GAME:
		game.Initialize();
		break;
	case SCENE_CLEAR:
		gameClear.Initialize();
		break;
	case SCENE_GAMEOVER:
		gameOver.Initialize();
		break;
	}
}

// ����scene���W���[���̏I���������s��
static void FinalizeModule(SCENE scene) 
{
	// �^�C�g���N���X�쐬
	Title &title = Title::GetInstance();
	// �Q�[���N���X����
	Game &game = Game::GetInstance();
	// �Q�[���N���A�N���X����
	GameClear &gameClear = GameClear::GetInstance();
	// �Q�[���I�[�o�[�N���X����
	GameOver &gameOver = GameOver::GetInstance();

	//�V�[���ɂ���ď����𕪊�
	switch (scene)
	{
	case SCENE_TITLE:
		title.Finalize();
		break;
	case SCENE_GAME:
		game.~Game();
		break;
	case SCENE_CLEAR:
		gameClear.Finalize();
		break;
	case SCENE_GAMEOVER:
		gameOver.Finalize();
		break;
	}
}

// ̪��޲ݏ���
bool SceneMgr::FadeInScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255) 
	{
		SetDrawBright(fadeCnt, fadeCnt, fadeCnt);
		return true;
	}
	else 
	{
		fadeCnt = 0;
		SetDrawBright(255, 255, 255);
		return false;
	}
}

// ̪��ޱ�ď���
bool SceneMgr::FadeOutScreen(int fadeStep)
{
	fadeCnt += fadeStep;
	if (fadeCnt <= 255)
	{
		SetDrawBright(255 - fadeCnt, 255 - fadeCnt, 255 - fadeCnt);
		return true;
	}
	else
	{
		fadeCnt = 0;
		SetDrawBright(0, 0, 0);
		return false;
	}
}