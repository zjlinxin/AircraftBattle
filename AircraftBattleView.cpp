
// AircraftBattleView.cpp : CAircraftBattleView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CAircraftBattleView ����/����

CAircraftBattleView::CAircraftBattleView()
{
	// TODO: �ڴ˴���ӹ������

}

CAircraftBattleView::~CAircraftBattleView()
{
}

BOOL CAircraftBattleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CAircraftBattleView ����

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
		pDC->TextOut(0, 0, L"��ӭ�����ɻ���Ϸ");
		pDC->TextOut(0, PixelWidth * 15, L"��Ϸ�У�a������d�����ң�w�����ϣ�s�����£�q�������ӵ���e�����У�p����ͣ/����");
		pDC->SetTextColor(old_text_color); 
		old_text_color = pDC->SetTextColor(RGB(0, 255, 0));
		pDC->TextOut(0, PixelWidth * 2, L"���ȣ�����Ҫ�˽�һ�¹��͹���ս��");
		pDC->TextOut(0, PixelWidth * 8, L"�����㻹��Ҫ�˽�һ���׵۹���ս��");
		pDC->TextOut(0, PixelWidth * 13, L"���ˣ��밴��1,2,3����4��ѡ���������ս����ף�������죡");
		pDC->SetTextColor(old_text_color);
		old_text_color = pDC->SetTextColor(RGB(255, 0, 0));
		pDC->TextOut(0, PixelWidth * 3, L"J-233���μ߻�����ӵ������������ս���ĵ÷ֲ����ܹ�������������5s��ͬ���ھ��ɣ�");
		pDC->TextOut(0, PixelWidth * 4, L"J-250��ս�߻�����ӵ������������ս����Ѫ�������ܹ���3���ӵ�������5s���ż����ż���");
		pDC->TextOut(0, PixelWidth * 5, L"J-666�ؿ�ǿ�߻���ӵ������������ս���������ӵ������ܹ��ٻ��޵���������ȫ��ȥ���ɣ�");
		pDC->TextOut(0, PixelWidth * 6, L"J-hhh��Ϊ���͹�������ķ�ս����������ս�����k�Ĵ�����Ϊ��������ĳ�߼�����¾���");
		pDC->SetTextColor(old_text_color);
		old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
		pDC->TextOut(0, PixelWidth * 9, L"F-999���޴��ķ���Աֻ������ֱ�߷��У�����ÿ��2s����һ���ӵ�,�����������õ��еȷ���");
		pDC->TextOut(0, PixelWidth * 10, L"F-998�����˶�ʹ�÷���Ա�����˷����ӵ������������ڻҵ�����ɡ������������õ���������");
		pDC->TextOut(0, PixelWidth * 11, L"F-997���ս�����״�Ӧ�ñ��ҷ����ţ�����Ϊʲô����һ�ж�����ģ������������õ���������");
		pDC->TextOut(0, PixelWidth * 12, L"����������ܹ�սʤ�׵�boss�Ļ���ֻ�����Ʒ���Ա��J-hhh�ļ�ʻԱ��,��ס������ͼ�����ս������ͬ���ھ�");
		pDC->SetTextColor(old_text_color);

	}

	else if (pDoc->control->GetStage() == 2 || pDoc->control->GetStage() == 3)
	{
		pDoc->SetModifiedFlag();
		x = pDoc->control->MP->GetPointx();
		y = pDoc->control->MP->GetPointy();
		//���ҷ�ս��
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
		//���з�ս��
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
					//��Щָ�����if������벻ͨ����ﲻ����ɫ��Ч��
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
		//���ӵ�
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
		//��ս�����߿�
		CPen pen(1, 2, RGB(0, 0, 0)), *old_pen;
		old_pen = pDC->SelectObject(&pen);
		pDC->MoveTo(0, (N + 1) * PixelWidth);
		pDC->LineTo((M + 1) * PixelWidth, (N + 1) * PixelWidth);
		pDC->MoveTo((M + 1) * PixelWidth, 0);
		pDC->LineTo((M + 1) * PixelWidth, (N + 1) * PixelWidth);
		pDC->SelectObject(old_pen);
		//����������
		COLORREF old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
		pDC->TextOut((M + 2) * PixelWidth, 0, L"������");
		pDC->TextOut((M + 2) * PixelWidth, PixelWidth, L"Ѫ����");
		pDC->TextOut((M + 2) * PixelWidth, PixelWidth * 2, L"���У�");
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
			pDC->TextOut((M + 2) * PixelWidth, PixelWidth * 4, L"�����У�");
			pDC->SetTextColor(old_text_color);
		}
		if (pDoc->control->GetStage() == 3)
		{
			old_text_color = pDC->SetTextColor(RGB(0, 0, 0));
			pDC->TextOut(0, (N + 2)* PixelWidth, L"��Ϸ�������밴��c��������");
			pDC->SetTextColor(old_text_color);
		}
	}

	else if (pDoc->control->GetStage() == 5)
	{
		
		if (pDoc->control->GetWin())
		{
			COLORREF old_text_color = pDC->SetTextColor(RGB(255, 0, 0));
			pDC->TextOut(0, 0, L"ΰ��Ĺ��͹�սʿ����ϲ��Ӯ�����ⳡ��ս��ʤ����");
			pDC->TextOut(0, PixelWidth * 2, L"����������ս��������������Ѫ��ͷ­ʹ���ǻ�����ⳡ���͹�����������ս����ʤ����");
			pDC->TextOut(0, PixelWidth * 4, L"������ס�㣡��ʷ���ס�㣡");
			pDC->SetTextColor(old_text_color);
		}
		else
		{
			COLORREF old_text_color = pDC->SetTextColor(RGB(0, 0, 255));
			pDC->TextOut(0, 0, L"��ʦδ��������");
			pDC->TextOut(0, PixelWidth, L"��ʹӢ��������");
			pDC->TextOut(0, PixelWidth * 3, L"������������־");
			pDC->TextOut(0, PixelWidth * 4, L"��Ц�Ƴ����ɷ�");
			pDC->SetTextColor(old_text_color);
		}
		COLORREF old_text_color = pDC->SetTextColor(RGB(0, 255, 0));
		pDC->TextOut(0, PixelWidth * 8, L"����������¿�ʼ��Ϸ");
		pDC->SetTextColor(old_text_color);
	}
}


// CAircraftBattleView ��ӡ

BOOL CAircraftBattleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CAircraftBattleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CAircraftBattleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CAircraftBattleView ���

#ifdef _DEBUG
void CAircraftBattleView::AssertValid() const
{
	CView::AssertValid();
}

void CAircraftBattleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAircraftBattleDoc* CAircraftBattleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAircraftBattleDoc)));
	return (CAircraftBattleDoc*)m_pDocument;
}
#endif //_DEBUG


// CAircraftBattleView ��Ϣ�������


void CAircraftBattleView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CAircraftBattleDoc* pDoc = GetDocument();
	if (pDoc->control->GetStage() == 1)
	//ѡ��״̬ʱ�ļ��̲���
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
	//��Ϸ״̬ʱ�ļ��̲���
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
	//����״̬ǰ�ļ��̲���
	{
		pDoc->control->To_End(nChar);
		pDoc->UpdateAllViews(NULL);
	}

	else if (pDoc->control->GetStage() == 4)
	//��ͣ״̬�ļ��̲���
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
	//����״̬ʱ�ļ��̲���
	{
		pDoc->control->The_End(nChar);
		pDoc->UpdateAllViews(NULL);
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CAircraftBattleView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
		}break;//�л����ƶ�

		case 2: {
			for (int i = 0;i < EP_num;i++)
			{
				if (pDoc->control->EP[i] != NULL)
					if (pDoc->control->EP[i]->GetFrequence() == 500)
						pDoc->control->EP[i]->Move();
			}
		}break;//�л����ƶ�

		case 3: {
			//�����ӵ�
			pDoc->control->EnemyShoot(1);
		}break;//����ֱ�ӵ�

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
			//��һ���ӵ�
			pDoc->control->EnemyShoot(2);
		}break;//ÿ4s�½�һ�ܷɻ�,����б�ӵ�

		case 5: {
			pDoc->control->BombMove();
		}break;//�ӵ��ƶ�

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
