#include "DxLib.h"
#include "item.h"

int ITEM::graph[2];

ITEM::ITEM()
{
	if (graph[0] == 0)
	{
		// 0���X�R�A���Z��S�@1���p���[�A�b�v��P
		graph[0] = LoadGraph("data/png/Item/item1.png");
		graph[1] = LoadGraph("data/png/Item/item2.png");
	}

	x = 0;
	y = 0;
	prevY = 0;

	GetGraphSize(graph[0], &width, &height);

	fallFlag = false;
	flag = false;
}

void ITEM::Updata()
{
	double tempY;

	if (!fallFlag)
	{
		tempY = y;
		// �������ꂽ�ۂɈ�x��Ɉړ�������
		y += (y - prevY) + 1;
		// ���_�܂ōs������t���O�𗧂Ă�
		if ((y - prevY) + 1 == 0)
		{
			fallFlag = true;
		}
		prevY = tempY;
	}
	else
	{
		// �������͈�葬�x�ŗ���
		y += 0.5;
	}

	if (y > 520)
	{
		Delete();
	}
}

void ITEM::Delete()
{
	fallFlag = false;
	flag = false;
}

void ITEM::Draw()
{
	// DrawGraph(x, y, graph[type], FALSE);
	DrawExtendGraph(x, y, x + width / 2, y + height / 2, graph[type], FALSE);	// �k���\��
}

void ITEM::SetFlag(double x, double y, int type)
{
	this->x = x;
	this->y = y - 8;
	prevY = y;
	this->type = type;

	flag = true;

}

bool ITEM::GetFlag()
{
	return flag;
}

void ITEM::GetPosition(double *x, double *y)
{
	*x = this->x + width / 2;
	*y = this->y + height / 2;
}

int ITEM::GetType()
{
	return type;
}

void ITEM::All()
{
	Updata();
	Draw();
}
