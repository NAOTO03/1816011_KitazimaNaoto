#pragma once

class Title
{
public:
	void All();
	void Finalize();
	static Title& GetInstance()
	{
		static Title title;
		return title;
	}
private:
	void Initialize();
	void Update();
	void Draw();
private:
	int graph[2];
};

