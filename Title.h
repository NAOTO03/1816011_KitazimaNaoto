#pragma once

class Title
{
public:
	void Initialize();
	void Finalize();
	static Title& GetInstance()
	{
		static Title title;
		return title;
	}
	void All();
private:
	void Update();
	void Draw();
	void KeySound(bool flag);
private:
	int graph[2];
	int keySound;
	bool keyFlag;
};

