
// AircraftBattleDoc.cpp : CAircraftBattleDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AircraftBattle.h"
#endif

#include "AircraftBattleDoc.h"
#include"AircraftBattle4.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAircraftBattleDoc

IMPLEMENT_DYNCREATE(CAircraftBattleDoc, CDocument)

BEGIN_MESSAGE_MAP(CAircraftBattleDoc, CDocument)
END_MESSAGE_MAP()


// CAircraftBattleDoc 构造/析构

CAircraftBattleDoc::CAircraftBattleDoc()
{
	// TODO: 在此添加一次性构造代码
	control = new Control;
}

CAircraftBattleDoc::~CAircraftBattleDoc()
{
}

BOOL CAircraftBattleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CAircraftBattleDoc 序列化

void CAircraftBattleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CAircraftBattleDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CAircraftBattleDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CAircraftBattleDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CAircraftBattleDoc 诊断

#ifdef _DEBUG
void CAircraftBattleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAircraftBattleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAircraftBattleDoc 命令
Control::Control()
{
	stage = 1;
	int i;
	for (i = 0;i < EP_num;i++)
		EP[i] = NULL;
	for (i = 0;i < EPBomb_num;i++)
		EB[i] = NULL;
	for (i = 0;i < MPBomb_num;i++)
		MB[i] = NULL;
}
void Control::Choose_Fly(char inputchar)
{
	if (inputchar == '1')
	{
		MP = new MyPlane(1);
		stage = 2;
		score = 0;
		unique_skill_num = 1;
		used_US = 0;
		run = true;
		live = true;
		win = false;
		god_like = false;
	}
	else if (inputchar == '2')
	{
		MP = new MyPlane(2);
		stage = 2;
		score = 0;
		unique_skill_num = 1;
		used_US = 0;
		run = true;
		live = true;
		win = false;
		god_like = false;
	}
	else if (inputchar == '3')
	{
		MP = new MyPlane(4);
		stage = 2;
		score = 0;
		unique_skill_num = 1;
		used_US = 0;
		run = true;
		live = true;
		win = false;
		god_like = false;
	}
	else if (inputchar == '4')
	{
		MP = new MyPlane(10);
		stage = 2;
		score = 0;
		unique_skill_num = 0;
		used_US = 0;
		run = true;
		live = true;
		win = false;
		god_like = false;
	}
	//进入游戏阶段
}
void Control::KeyboardOperate(char inputchar)
{
	if (inputchar == 'a')
	{
		if (MP->point_x > 0)
			MP->point_x -= PixelWidth;
		HitCheck();
		ImpackCheck();
	}
	else if (inputchar == 'd')
	{
		if (MP->point_x < PixelWidth * M)
			MP->point_x += PixelWidth;
		HitCheck();
		ImpackCheck();
	}
	else if (inputchar == 'w')
	{
		if (MP->point_y > 0)
			MP->point_y -= PixelWidth;
		HitCheck();
		ImpackCheck();
	}
	else if (inputchar == 's')
	{
		if (MP->point_y < PixelWidth * N)
			MP->point_y += PixelWidth;
		HitCheck();
		ImpackCheck();
	}
	else if (inputchar == 'q')
	{
		int i;
		if (MP->point_y > 0)
			//边界不能发射子弹
		{
			if (MP->version == 1 || MP->version == 2)
			{
				for (i = 0;i < MPBomb_num;i++)
				{
					if (MB[i] == NULL)
					{
						MB[i] = new Bomb(MP->point_x, MP->point_y - PixelWidth, 14, true);
						break;
					}
				}
			}
			else if (MP->version == 4)
			{
				for (i = 0;i < MPBomb_num;i++)
				{
					if (MB[i] == NULL)
					{
						MB[i] = new Bomb(MP->point_x, MP->point_y - PixelWidth, 16, true);
						break;
					}
				}
			}
			else if (MP->version == 3)
			{
				if (MP->point_x > 0)
					//边界不能发射子弹
				{
					for (i = 0;i < MPBomb_num;i++)
					{
						if (MB[i] == NULL)
						{
							MB[i] = new Bomb(MP->point_x - PixelWidth, MP->point_y - PixelWidth, 14, true);
							break;
						}
					}
				}
				if (MP->point_x < M * PixelWidth)
				{
					for (i = 0;i < MPBomb_num;i++)
					{
						if (MB[i] == NULL)
						{
							MB[i] = new Bomb(MP->point_x + PixelWidth, MP->point_y - PixelWidth, 14, true);
							break;
						}
					}
				}
				for (i = 0;i < MPBomb_num;i++)
				{
					if (MB[i] == NULL)
					{
						MB[i] = new Bomb(MP->point_x, MP->point_y - PixelWidth, 14, true);
						break;
					}
				}
			}
			else if (MP->version == 10)
			{
				for (i = 0;i < EP_num;i++)
				{
					if (EP[i] != NULL)
					{
						EP[i]->blood--;
						MP->blood++;
						if (EP[i]->blood <= 0)
						{
							//结算分数
							score += MP->scoremultiples*EP[i]->scoreweight;
							unique_skill_num = score / UniqueSkill - used_US + 1;
							if (EP[i]->version == 12)
							{
								win = true;
								stage = 3;
							}
							delete EP[i];
							EP[i] = NULL;
						}
					}
				}
			}
		}
	}
	else if (inputchar == 'p')
	{
		stage = 4;
	}
	else if (inputchar == 'e')
	{
		if (unique_skill_num > 0)
		{
			unique_skill_num--;
			used_US++;
			god_like = true;
			Unique_Skill();
		}
	}
}
void Control::In_Pause(char inputchar)
{
	if (inputchar == 'p')
		stage = 2;
}
void Control::To_End(char inputchar)
{
	if(inputchar=='c')
		stage = 5;
}
void Control::The_End(char inputchar)
{
		stage = 1;
		int i;
		for (i = 0;i < EP_num;i++)
			EP[i] = NULL;
		for (i = 0;i < EPBomb_num;i++)
			EB[i] = NULL;
		for (i = 0;i < MPBomb_num;i++)
			MB[i] = NULL;
}
void Control::NewEP(int i)
{
	if (score > ScoreThreshold)
	{
		score = score / ScoreThreshold;
		EP[i] = new EnemyPlane(12);
		EP[i]->point_x = (M / 2)*PixelWidth;
		EP[i]->point_y = 0;
	}
	else
	{
		EP[i] = new EnemyPlane(rand() % 3 + 5);
		EP[i]->point_x = (rand() % M) * PixelWidth;
		EP[i]->point_y = 0;
	}
}
void Control::BombMove()
{
	int i;
	for (i = 0;i < EPBomb_num;i++)
		//敌方子弹运动
	{
		if (EB[i] != NULL)
		{
			if (EB[i]->point_y < N*PixelWidth)
			{
				EB[i]->point_y += PixelWidth;
				if (EB[i]->vertical)
					//斜行的子弹
				{
					if (EB[i]->is_right)
					{
						if (EB[i]->point_x < M*PixelWidth)
							EB[i]->point_x += PixelWidth;
						else
							//子弹飞出边界会删除
						{
							delete EB[i];
							EB[i] = NULL;
						}
					}
					else
					{
						if (EB[i]->point_x > 0)
							EB[i]->point_x -= PixelWidth;
						else
						{
							delete EB[i];
							EB[i] = NULL;
						}
					}
				}
			}
			else
			{
				delete EB[i];
				EB[i] = NULL;
			}
		}
	}
	for (i = 0;i < MPBomb_num;i++)
		//我方子弹运动，我方无斜行子弹
	{
		if (MB[i] != NULL)
		{
			if (MB[i]->point_y > 0)
				MB[i]->point_y -= PixelWidth;
			else
			{
				delete MB[i];
				MB[i] = NULL;
			}
		}
	}
}
void Control::EnemyShoot(int v)
{
	int i, j;
	if (v == 1)
	//2s发射一颗直行的子弹
	{
		for (i = 0;i < EP_num;i++)
		{
			if (EP[i] != NULL)
			{
				if (EP[i]->version == 5 || EP[i]->version == 12)
				{
					if (EP[i]->point_y >= 0 && EP[i]->point_y < N*PixelWidth)
					{
						for (j = 0;j < EPBomb_num;j++)
						{
							if (EB[j] == NULL)
							{
								EB[j] = new Bomb(EP[i]->point_x, EP[i]->point_y + PixelWidth, 14, true);
								break;
							}
						}
					}
				}
			}
		}
	}
	else
	//4s发射一颗斜行的子弹
	{
		for (i = 0;i < EP_num;i++)
		{
			if (EP[i] != NULL)
			{
				if (EP[i]->version == 7)
				{
					if (EP[i]->point_y >= 0 && EP[i]->point_y < N * PixelWidth)
					//边界不发射子弹
					{
						if (EP[i]->is_right && EP[i]->point_x > 0)
						{
							for (j = 0;j < EPBomb_num;j++)
							{
								if (EB[j] == NULL)
								{
									EB[j] = new Bomb(EP[i]->point_x - PixelWidth, EP[i]->point_y + PixelWidth, 15, !EP[i]->is_right);
									break;
								}
							}
						}
						else if (!EP[i]->is_right && EP[i]->point_x < M * PixelWidth)
						{
							for (j = 0;j < EPBomb_num;j++)
							{
								if (EB[j] == NULL)
								{
									EB[j] = new Bomb(EP[i]->point_x + PixelWidth, EP[i]->point_y + PixelWidth, 15, !EP[i]->is_right);
									break;
								}
							}
						}
					}
				}
				else if (EP[i]->version == 12)
				{
					for (j = 0;j < EPBomb_num;j++)
					{
						if (EB[j] == NULL)
						{
							EB[j] = new Bomb(EP[i]->point_x + PixelWidth, EP[i]->point_y + PixelWidth, 15, true);
							//EB[j] = new Bomb(EP[i]->point_x - PixelWidth, EP[i]->point_y + PixelWidth, 15, false);
							break;
						}
					}
					for (j = 0;j < EPBomb_num;j++)
					{
						if (EB[j] == NULL)
						{
							//EB[j] = new Bomb(EP[i]->point_x + PixelWidth, EP[i]->point_y + PixelWidth, 15, true);
							EB[j] = new Bomb(EP[i]->point_x - PixelWidth, EP[i]->point_y + PixelWidth, 15, false);
							break;
						}
					}
				}
			}
		}
	}
}
void Control::HitCheck()
{
	int i, j;
	for (i = 0;i < EP_num;i++)
		//我方子弹击中敌机
	{
		if (EP[i] != NULL)
		{
			for (j = 0;j < MPBomb_num;j++)
			{
				if (MB[j] != NULL)
				{
					if (MB[j]->point_x == EP[i]->point_x && MB[j]->point_y == EP[i]->point_y)
					{
						EP[i]->blood -= MB[j]->weight;
						delete MB[j];
						MB[j] = NULL;
					}
				}
			}
		}
	}
	for (i = 0;i < EP_num;i++)
		//判断敌机是否死亡
	{
		if (EP[i] != NULL)
		{
			if (EP[i]->blood <= 0)
			{
				//结算分数
				score += MP->scoremultiples * EP[i]->scoreweight;
				unique_skill_num = score / UniqueSkill - used_US + 1;
				if (EP[i]->version == 12)
				{
					win = true;
					stage = 3;
				}
				delete EP[i];
				EP[i] = NULL;
			}
		}
	}
	//敌方子弹击中我机
	for (j = 0;j < EPBomb_num;j++)
	{
		if (EB[j] != NULL)
		{
			if (EB[j]->point_x == MP->point_x && EB[j]->point_y == MP->point_y)
			{
				MP->blood -= EB[j]->weight;
				//普通战机处于无敌状态或J-hhh击中无损
				if (god_like)
					MP->blood += EB[j]->weight;
				delete EB[j];
				EB[j] = NULL;
			}
		}
	}
	if (MP->blood <= 0)
		stage = 3;
}
void Control::ImpackCheck()
{
	int i;
	for (i = 0;i < EP_num;i++)
	{
		if (EP[i] != NULL)
		{
			if (EP[i]->point_x == MP->point_x && EP[i]->point_y == MP->point_y)
			{
				//撞击死亡也计算分数
				score += MP->scoremultiples*EP[i]->scoreweight;
				unique_skill_num = score / UniqueSkill - used_US +1;
				if (MP->version == 10)
				{
					MP->blood = MP->blood - EP[i]->blood;
					if (MP->blood <= 0)
						stage = 3;
				}
				if (EP[i]->version != 12)
				{
					delete EP[i];
					EP[i] = NULL;
				}
				if (!(god_like && MP->version == 1) && MP->version != 10)
					stage = 3;
			}
		}
	}
}
void Control::Unique_Skill()
{
	if (MP->version == 4)
	{
		int i;
		for (i = 0;i < EP_num;i++)
		{
			if (EP[i] != NULL)
			{
				if (EP[i]->point_y >= (N / 2) * PixelWidth)
				{
					delete EP[i];
					EP[i] = NULL;
				}
			}
		}
		for (i = 0;i < EPBomb_num;i++)
		{
			if (EB[i] != NULL)
			{
				if (EB[i]->	point_y >= (N / 2) * PixelWidth)
				{
					delete EB[i];
					EB[i] = NULL;
				}
			}
		}
		End_US();
	}
	else if (MP->version == 2)
	{
		MP->version = 3;
	}
}
void Control::End_US()
{
	god_like = false;
	if (MP->version == 3)
	{
		MP->version = 2;
	}
}
MyPlane::MyPlane(int x)
{
	version = x;
	point_x = (N - 2) * 20;
	point_y = (M / 2) * 20;
	if (version == 1)
	{
		blood = 3;
		scoremultiples = 2;
	}
	else if (version == 2)
	{
		blood = 6;
		scoremultiples = 1;
	}
	else if (version == 4)
	{
		blood = 3;
		scoremultiples = 1;
	}
	else
	{
		blood = 3;
		scoremultiples = 2;
	}
}
EnemyPlane::EnemyPlane(int x)
{
	version = x;
	if (version == 5)
	{
		frequence = 1000;//1000ms
		vertical = false;//直行
		scoreweight = 3;
		blood = 2;
	}
	else if (version == 6)
	{
		frequence = 500;//500ms
		vertical = false;
		scoreweight = 1;
		blood = 1;
	}
	else if (version == 7)
	{
		frequence = 1000;//1000ms
		vertical = true;
		int r = rand() % 2;
		if (r == 0)
			is_right = false;
		else
			is_right = true;
		scoreweight = 5;
		blood = 5;
	}
	else if (version == 12)
	{
		frequence = 0;
		vertical = false;
		scoreweight = 100;
		blood = BossBlood;
	}
}
void EnemyPlane::Move()
{
	if (version != 12)
	{
		if (point_y < N*PixelWidth)
			point_y += PixelWidth;
		else
			point_y = -PixelWidth;
		if (vertical)
			//斜行的飞机
		{
			if (is_right)
			{
				if (point_x < M*PixelWidth)
					point_x += PixelWidth;
				else
				{
					point_x -= PixelWidth;
					is_right = !is_right;
				}
			}
			else
			{
				if (point_x > 0)
					point_x -= PixelWidth;
				else
				{
					point_x += PixelWidth;
					is_right = !is_right;
				}
			}
		}
	}
	//Boss机不移动
}
Bomb::Bomb(int x, int y, int k, bool l)
{
	point_x = x;
	point_y = y;
	version = k;
	if (version == 16)
		weight = 2;
	else
		weight = 1;
	if (version == 15)
		vertical = true;
	else
		vertical = false;
	if (vertical)
		is_right = l;
}