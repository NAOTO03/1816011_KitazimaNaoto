#pragma once

class DESCRIPTION
{
public:
	void Initialize();
	void Finalize();
	static DESCRIPTION& GetInstance()
	{
		static DESCRIPTION description;
		return description;
	}
	void All();
private:
	void Update();
	void Draw();
	void KeySound(bool flag);
private:
	int graph[3];
	int keySound;
	bool keyFlag;
};
