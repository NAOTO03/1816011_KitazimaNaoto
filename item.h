#pragma once

class ITEM
{
public:
	ITEM();
	void SetFlag(double x, double y, int type);
	bool GetFlag();
	void Delete();
	void GetPosition(double *x, double *y);
	int GetType();
	void GetSize(int *width, int *height);
	void All();
private:
	void Updata();
	void Draw();
private:
	// グラフィックハンドル
	static int graph[2];
	// どっちのアイテムかを示す変数
	int type;
	// 座標
	double x, y;
	double prevY;
	//画像幅
	int width, height;
	// アイテムが落下し始めるフラグ
	bool fallFlag;
	// 出現中かどうかのフラグ
	bool flag;
};

