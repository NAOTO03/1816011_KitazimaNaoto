#ifndef _EFFECT_PDEAD
#define _EFFECT_PDEAD

struct PLAYER_EFFECT 
{
	double x;
	double y;
	double rad;
	int speed;
};

class EFFECT_PDEAD 
{
private:
	//座標
	double x, y;
	//画像のサイズ
	int width;
	int height;
	//グラフィックハンドル
	int graph[3];
	//カウント
	int count;
	//実行中かどうかのフラグ
	bool flag;
	//どの画像を使うかの添字
	int index;
	PLAYER_EFFECT pEffect[EFFECT_PDEADNUM];

private:
	void Updata();
	void Draw();
public:
	EFFECT_PDEAD();
	void SetFlag(double x, double y, int index);
	bool GetFlag();
	void All();
};

#endif
