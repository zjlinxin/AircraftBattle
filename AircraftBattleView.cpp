
// AircraftBattleView.cpp : CAircraftBattleView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "AircraftBattle.h"
#endif

#include "AircraftBattleDoc.h"
#include "AircraftBattleView.h"
#include "AircraftBattle4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAircraftBattleView

IMPLEMENT_DYNCREATE(CAircraftBattleView, CView)

BEGIN_MESSAGE_MAP(CAircraftBattleView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CAircraftBattleView 构造/析构

CAircraftBattleView::CAircraftBattleView()
{
	// TODO: 在此处添加构造代码

}

CAircraftBattleView::~CAircraftBattleView()
{
}

BOOL CAircraftBattleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CAircraftBattleView 绘制

void CAircraftBattleView::OnDraw(CDC* pDC)
{
	CAircraftBattleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int x, y, i;
	if (pDoc->control->GetStage() == 1)
	{
		COLORREF old_text_color = pDC->SetTextColor(RGB(255, 0, 255));
		pDC->TextOut(0, 0, L"欢迎进入打飞机游戏");
		pDC->TextOut(0, PixelWidth * 15, L"游戏中，a：向左；d：向右；w：向上；s：向下；q：发射子弹；e：大招；p：暂停/继续");
		pDC->SetTextColor(old_text_color); 
		old_text_color = pDC->SetTextColor(RGB(0, 255, 0));
		pDC->TextOut(0, PixelWidth * 2, L"首先，你需要了解一下共和国的战机");
		pDC->TextOut(0, PixelWidth * 8, L"或许，你还需要了解一下米帝国的战机");
		pDC->TextOut(0, PixelWidth * 13, L"好了，请按下1,2,3，或4，选择您钟意的战机，祝您玩得愉快！");
		pDC->SetTextColor(old_text_color);
		old_text_color = pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOut(0, PixelWidth * 3, L"J-233隐形歼击机，拥有两倍于其他战机的得分并且能够变身超级赛亚人5s，同归于尽吧！");
		pDC->TextOut(0, PixelWidth * 4, L"J-250主战歼击机，拥有两倍于其他战机的血量并且能够有3个子弹发射器5s，放箭！放箭！");
		pDC->TextOut(0, PixelWidth * 5, L"J-666地空强歼机，拥有两倍于其他战机威力的子弹并且能够召唤无敌引力波，全都去死吧！");
		pDC->TextOut(0, PixelWidth * 6, L"J-hhh作为共和国最优秀的非战斗序列特种战机，祂的存在是为了向东亚区某高级玩家致敬！");
		pDC->SetTextColor(old_text_color);
		old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
		pDC->TextOut(0, PixelWidth * 9, L"F-999那愚蠢的飞行员只会沿着直线飞行，并且每隔2s发射一颗子弹,击落他，你会得到中等分数");
		pDC->TextOut(0, PixelWidth * 10, L"F-998高速运动使得飞行员忘记了发射子弹，这或许就是炮灰的意义吧。击落他，你会得到少量分数");
		pDC->TextOut(0, PixelWidth * 11, L"F-997这款战机的雷达应该被我方干扰，否则为什么它的一切都是歪的？击落他，你会得到大量分数");
		pDC->TextOut(0, PixelWidth * 12, L"这个世界上能够战胜米帝boss的或许只有王牌飞行员和J-hhh的驾驶员了,记住，别试图用你的战机与其同归于尽");
		pDC->SetTextColor(old_text_color);

	}

	else if (pDoc->control->GetStage() == 2 || pDoc->control->GetStage() == 3)
	{
		pDoc->SetModifiedFlag();
		x = pDoc->control->MP->GetPointx();
		y = pDoc->control->MP->GetPointy();
		//画我方战机
		CBrush *old_brush;
		if (pDoc->control->MP->GetBlood() > 3)
		{
			CBrush brush(RGB(63, 0, 0)); 
			old_brush = pDC->SelectObject(&brush); 
			pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth); 
			pDC->SelectObject(old_brush); 
		}
		else if(pDoc->control->MP->GetBlood() > 1)
		{
			CBrush brush(RGB(127, 0, 0));
			old_brush = pDC->SelectObject(&brush);
			pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth);
			pDC->SelectObject(old_brush);
		}
		else
		{
			CBrush brush(RGB(255, 0, 0));
			old_brush = pDC->SelectObject(&brush);
			pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth);
			pDC->SelectObject(old_brush);
		}
		//画敌方战机
		for (i = 0;i < EP_num;i++)
		{
			if (pDoc->control->EP[i] != NULL)
			{
				x = pDoc->control->EP[i]->GetPointx();
				y = pDoc->control->EP[i]->GetPointy();
				if (pDoc->control->EP[i]->GetBlood()>3)
				{
					CBrush brush1(RGB(0, 0, 63));
					old_brush = pDC->SelectObject(&brush1);
					pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth);
					pDC->SelectObject(old_brush);
					//这些指令放在if外面编译不通过或达不到变色的效果
				}
				else if (pDoc->control->EP[i]->GetBlood() > 1)
				{
					CBrush brush1(RGB(0, 0, 127));
					old_brush = pDC->SelectObject(&brush1);
					pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth);
					pDC->SelectObject(old_brush);
				}
				else
				{
					CBrush brush1(RGB(0, 0, 255));
					old_brush = pDC->SelectObject(&brush1);
					pDC->Rectangle(x, y, x + PixelWidth, y + PixelWidth);
					pDC->SelectObject(old_brush);
				}
			}
		}
		//画子弹
		CBrush brush2(RGB(0, 255, 255));
		old_brush = pDC->SelectObject(&brush2);
		for (i = 0;i < EPBomb_num;i++)
		{
			if (pDoc->control->EB[i] != NULL)
			{
				x = pDoc->control->EB[i]->GetPointx();
				y = pDoc->control->EB[i]->GetPointy();
				if (pDoc->control->EB[i]->GetVersion() == 14)
					pDC->Rectangle(x + PixelWidth / 4, y + PixelWidth / 4, x + PixelWidth / 4 * 3, y + PixelWidth / 4 * 3);
				else if (pDoc->control->EB[i]->GetVersion() == 15)
					pDC->Ellipse(x + PixelWidth / 4, y + PixelWidth / 4, x + PixelWidth / 4 * 3, y + PixelWidth / 4 * 3);
			}
		}
		pDC->SelectObject(old_brush);
		CBrush brush3(RGB(255, 255, 0));
		old_brush = pDC->SelectObject(&brush3);
		for (i = 0;i < MPBomb_num;i++)
		{
			if (pDoc->control->MB[i] != NULL)
			{
				x = pDoc->control->MB[i]->GetPointx();
				y = pDoc->control->MB[i]->GetPointy();
				if (pDoc->control->MB[i]->GetVersion() == 14)
					pDC->Rectangle(x + PixelWidth / 4, y + PixelWidth / 4, x + PixelWidth / 4 * 3, y + PixelWidth / 4 * 3);
				else if (pDoc->control->MB[i]->GetVersion() == 16)
					pDC->Ellipse(x, y, x + PixelWidth, y + PixelWidth);
			}
		}
		pDC->SelectObject(old_brush);
		//画战场的线框
		CPen pen(1, 2, RGB(0, 0, 0)), *old_pen;
		old_pen = pDC->SelectObject(&pen);
		pDC->MoveTo(0, (N + 1) * PixelWidth);
		pDC->LineTo((M + 1) * PixelWidth, (N + 1) * PixelWidth);
		pDC->MoveTo((M + 1) * PixelWidth, 0);
		pDC->LineTo((M + 1) * PixelWidth, (N + 1) * PixelWidth);
		pDC->SelectObject(old_pen);
		//画其他辅助
		COLORREF old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
		pDC->TextOut((M + 2) * PixelWidth, 0, L"分数：");
		pDC->TextOut((M + 2) * PixelWidth, PixelWidth, L"血量：");
		pDC->TextOut((M + 2) * PixelWidth, PixelWidth * 2, L"大招：");
		pDC->SetTextColor(old_text_color);
		old_text_color = pDC->SetTextColor(RGB(255, 0, 0));
		CString str;
		str.Format(_T("%d"), pDoc->control->GetScore());
		pDC->TextOut((M + 4) * PixelWidth, 0, str);
		str.Format(_T("%d"), pDoc->control->MP->GetBlood());
		pDC->TextOut((M + 4) * PixelWidth, PixelWidth, str);
		str.Format(_T("%d"), pDoc->control->GetUSN());
		pDC->TextOut((M + 4) * PixelWidth, PixelWidth * 2, str);
		pDC->SetTextColor(old_text_color);
		if (pDoc->control->GetGL())
		{
			old_text_color = pDC->SetTextColor(RGB(0, 0, 0));
			pDC->TextOut((M + 2) * PixelWidth, PixelWidth * 4, L"大招中！");
			pDC->SetTextColor(old_text_color);
		}
		if (pDoc->control->GetStage() == 3)
		{
			old_text_color = pDC->SetTextColor(RGB(0, 0, 0));
			pDC->TextOut(0, (N + 2)* PixelWidth, L"游戏结束，请按‘c’继续！");
			pDC->SetTextColor(old_text_color);
		}
	}

	else if (pDoc->control->GetStage() == 5)
	{
		
		if (pDoc->control->GetWin())
		{
			COLORREF old_text_color = pDC->SetTextColor(RGB(255, 0, 0));
			pDC->TextOut(0, 0, L"伟大的共和国战士，恭喜你赢得了这场空战的胜利！");
			pDC->TextOut(0, PixelWidth * 2, L"经过漫长的战争，无数人用鲜血和头颅使我们获得了这场共和国的自卫反击战争的胜利！");
			pDC->TextOut(0, PixelWidth * 4, L"人民会记住你！历史会记住你！");
			pDC->SetTextColor(old_text_color);
		}
		else
		{
			COLORREF old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
			pDC->TextOut(0, 0, L"出师未捷身先死");
			pDC->TextOut(0, PixelWidth, L"长使英雄泪满襟");
			pDC->TextOut(0, PixelWidth * 3, L"他人若得凌云志");
			pDC->TextOut(0, PixelWidth * 4, L"敢笑黄巢不丈夫");
			pDC->SetTextColor(old_text_color);
		}
		COLORREF old_text_color = pDC->SetTextColor(RGB(0, 255, 0));
		pDC->TextOut(0, PixelWidth * 8, L"按任意键重新开始游戏");
		pDC->SetTextColor(old_text_color);
	}
}


// CAircraftBattleView 打印

BOOL CAircraftBattleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CAircraftBattleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CAircraftBattleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CAircraftBattleView 诊断

#ifdef _DEBUG
void CAircraftBattleView::AssertValid() const
{
	CView::AssertValid();
}

void CAircraftBattleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAircraftBattleDoc* CAircraftBattleView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAircraftBattleDoc)));
	return (CAircraftBattleDoc*)m_pDocument;
}
#endif //_DEBUG


// CAircraftBattleView 消息处理程序


void CAircraftBattleView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CAircraftBattleDoc* pDoc = GetDocument();
	if (pDoc->control->GetStage() == 1)
	//选择状态时的键盘操作
	{
		pDoc->control->Choose_Fly(nChar);
		pDoc->UpdateAllViews(NULL);
		if (nChar == '1' || nChar == '2' || nChar == '3' || nChar == '4')
		{
			SetTimer(1, 1000, NULL);
			SetTimer(2, 500, NULL);
			SetTimer(3, 2000, NULL);
			SetTimer(4, 4000, NULL);
			SetTimer(5, 250, NULL);
			srand(time(0));
		}
	}

	else if (pDoc->control->GetStage() == 2)
	//游戏状态时的键盘操作
	{
		if (nChar == 'e' && !pDoc->control->GetGL())
		{
			if (pDoc->control->MP->GetVersion() != 4)
				SetTimer(6, 5000, NULL);
		}
		pDoc->control->KeyboardOperate(nChar);
		if (nChar == 'p')
		{
			KillTimer(1);
			KillTimer(2);
			KillTimer(3);
			KillTimer(4);
			KillTimer(5);
		}
		else
			pDoc->UpdateAllViews(NULL);
	}

	else if (pDoc->control->GetStage() == 3)
	//结束状态前的键盘操作
	{
		pDoc->control->To_End(nChar);
		pDoc->UpdateAllViews(NULL);
	}

	else if (pDoc->control->GetStage() == 4)
	//暂停状态的键盘操作
	{
		pDoc->control->In_Pause(nChar);
		pDoc->UpdateAllViews(NULL);
		if (nChar == 'p')
		{
			SetTimer(1, 1000, NULL);
			SetTimer(2, 500, NULL);
			SetTimer(3, 2000, NULL);
			SetTimer(4, 4000, NULL);
			SetTimer(5, 250, NULL);
		}
	}

	else if (pDoc->control->GetStage() == 5)
	//结束状态时的键盘操作
	{
		pDoc->control->The_End(nChar);
		pDoc->UpdateAllViews(NULL);
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CAircraftBattleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CAircraftBattleDoc* pDoc = GetDocument();
	if (pDoc->control->GetStage() == 2)
	{
		switch (nIDEvent)
		{
		case 1: {
			for (int i = 0;i < EP_num;i++)
			{
				if (pDoc->control->EP[i] != NULL)
					if (pDoc->control->EP[i]->GetFrequence() == 1000)
						pDoc->control->EP[i]->Move();
			}
		}break;//敌机满移动

		case 2: {
			for (int i = 0;i < EP_num;i++)
			{
				if (pDoc->control->EP[i] != NULL)
					if (pDoc->control->EP[i]->GetFrequence() == 500)
						pDoc->control->EP[i]->Move();
			}
		}break;//敌机快移动

		case 3: {
			//发射子弹
			pDoc->control->EnemyShoot(1);
		}break;//发射直子弹

		case 4: {
			int i = 0;
			while (i < EP_num)
			{
				if (pDoc->control->EP[i] != NULL)
					i++;
				else
				{
					pDoc->control->NewEP(i);
					break;
				}
			}
			//另一种子弹
			pDoc->control->EnemyShoot(2);
		}break;//每4s新建一架飞机,发射斜子弹

		case 5: {
			pDoc->control->BombMove();
		}break;//子弹移动

		case 6: {
			pDoc->control->End_US();
			KillTimer(6);
		}break;
		}
		pDoc->control->HitCheck();
		pDoc->control->ImpackCheck();
	}
	pDoc->UpdateAllViews(NULL);

	CView::OnTimer(nIDEvent);
}
