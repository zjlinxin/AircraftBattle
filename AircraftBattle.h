
// AircraftBattle.h : AircraftBattle Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CAircraftBattleApp:
// �йش����ʵ�֣������ AircraftBattle.cpp
//

class CAircraftBattleApp : public CWinApp
{
public:
	CAircraftBattleApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CAircraftBattleApp theApp;
