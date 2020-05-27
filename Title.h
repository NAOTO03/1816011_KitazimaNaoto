#pragma once

class Title
{
public:
	void All();
	void Initialize();
	void Finalize();
	static Title& GetInstance()
	{
		static Title title;
		return title;
	}
private:
	void Update();
	void Draw();
	void KeySound(bool flag);
private:
	int graph[2];
	int keySound;
	bool keyFlag;
};

