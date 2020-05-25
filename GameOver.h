#pragma once

class GameOver
{
public:
	void All();
	void Finalize();
	static GameOver& GetInstance()
	{
		static GameOver gameOver;
		return gameOver;
	}
private:
	void Initialize();
	void Update();
	void Draw();
private:
	int graph;
};
