#include "SceneMgr.h"
#include "DxLib.h"
#include "Title.h"
#include "Game.h"
#include "GameClear.h"
#include "GameOver.h"

static SCENE scene = SCENE_TITLE;    //�V�[���Ǘ��ϐ�
static SCENE nextScene = SCENE_NONE;    //���̃V�[���Ǘ��ϐ�

static void FinalizeModule(SCENE scene);//�w�胂�W���[���̏I���������s��

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

	if (nextScene != SCENE_NONE)	     //���̃V�[�����Z�b�g����Ă�����
	{
		// FinalizeModule(scene);		//���݂̃V�[���̏I�����������s
		scene = nextScene;			//���̃V�[�������݂̃V�[���Z�b�g
		nextScene = SCENE_NONE;     //���̃V�[�������N���A
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