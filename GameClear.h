#pragma once

class GameClear
{
public:
	void All();
	void Finalize();
	static GameClear& GetInstance()
	{
		static GameClear gameClear;
		return gameClear;
	}
private:
	void Initialize();
	void Update();
	void Draw();
private:
	int graph;
};

