#pragma once

class GameOver
{
public:
	void All();
	void Initialize();
	void Finalize();
	static GameOver& GetInstance()
	{
		static GameOver gameOver;
		return gameOver;
	}
private:
	void Update();
	void Draw();
private:
	int graph;
};
