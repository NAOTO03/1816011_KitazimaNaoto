#pragma once

typedef enum
{
	SCENE_TITLE,	// �^�C�g�����
	SCENE_GAME,		// �Q�[�����
	SCENE_CLEAR,	// �N���A���
	SCENE_GAMEOVER, // �Q�[���I�[�o�[���
	SCENE_NONE,		// ����
}SCENE;

class SceneMgr
{
public:
public:
	void All();
private:
	void Initialize();
	void Finalize();
	void Update();
	void Draw();
	void ChangeScene(SCENE nextScene);	// �����@nextScene �ɃV�[����ύX����
};

