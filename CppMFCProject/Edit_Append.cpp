// Edit_Append.cpp : implementation file
//

#include "stdafx.h"
#include "RosterMaker.h"
#include "Edit_Append.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEdit_Append

CEdit_Append::CEdit_Append()
{
}

CEdit_Append::~CEdit_Append()
{
}

CEdit_Append::Set(char*s)
{
	SetSel(0,-1),
	Clear();
	SetSel_AtEnd();
	ReplaceSel(s,false);

	SetSel_AtEnd();
}

CEdit_Append::Set(CString&s)
{
	Set(s.GetBuffer(0));
}

CEdit_Append::Append(char*s)
{
	SetSel_AtEnd();
	ReplaceSel(s,false);
	SetSel_AtEnd();
}

CEdit_Append::Append(CString&s)
{
	Append(s.GetBuffer(0));
}

int CEdit_Append::GetTextLength()
{
	int textLength=0;
	int numLines=GetLineCount(),li;

	li=0;

	while(li<numLines)
	{
		textLength+=LineLength(li);				
		++li;
	}

	return(textLength);

}

CEdit_Append::SetSel_AtEnd()
{
	#if 0
		//int textLength=GetTextLength();

		//SetSel(textLength,textLength);
	#endif

	SetSel(-1,-1);

}

BEGIN_MESSAGE_MAP(CEdit_Append, CEdit)
	//{{AFX_MSG_MAP(CEdit_Append)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEdit_Append message handlers
