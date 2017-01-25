#if !defined(AFX_EDIT_APPEND_H__96D70B2C_FB76_4025_B09E_97D97733C734__INCLUDED_)
#define AFX_EDIT_APPEND_H__96D70B2C_FB76_4025_B09E_97D97733C734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Edit_Append.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEdit_Append window

class CEdit_Append : public CEdit
{
// Construction
public:
	CEdit_Append();

// Attributes
public:

// Operations
public:

	Set(char*s);
	Set(CString&s);
	Append(char*s);
	Append(CString&s);

	int GetTextLength();
	SetSel_AtEnd();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEdit_Append)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEdit_Append();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEdit_Append)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDIT_APPEND_H__96D70B2C_FB76_4025_B09E_97D97733C734__INCLUDED_)
