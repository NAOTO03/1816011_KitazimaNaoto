#pragma once

class EFFECT_EDEAD
{
public:
	EFFECT_EDEAD();
	bool GetFlag();
	void SetFlag(double x, double y, int index);
	void All();
private:
	void Updata();
	void Draw();
private:
	//座標
	double x, y;
	//グラフィックハンドル
	static int graph[2];
	//エフェクト画像の角度
	double rad;
	//拡大率
	double rate;
	//透明度
	int alpha;
	//どの画像を使うかの添字
	int index;
	//カウント
	int count;
	//実行中かどうかのフラグ
	bool flag;
};

