// RosterMaker.h : main header file for the ROSTERMAKER application
//

#if !defined(AFX_ROSTERMAKER_H__4A843297_E1EF_4B3F_8514_561E396E1593__INCLUDED_)
#define AFX_ROSTERMAKER_H__4A843297_E1EF_4B3F_8514_561E396E1593__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRosterMakerApp:
// See RosterMaker.cpp for the implementation of this class
//

class CRosterMakerApp : public CWinApp
{
public:
	CRosterMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRosterMakerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRosterMakerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROSTERMAKER_H__4A843297_E1EF_4B3F_8514_561E396E1593__INCLUDED_)
