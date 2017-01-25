// RosterMakerDlg.h : header file
//

#if !defined(AFX_ROSTERMAKERDLG_H__A7E6FA32_9257_4149_A360_FB4E73111E80__INCLUDED_)
#define AFX_ROSTERMAKERDLG_H__A7E6FA32_9257_4149_A360_FB4E73111E80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRosterMakerDlg dialog

#include<fileio2.h>
#include"Edit_Append.h"

class CRosterMakerDlg : public CDialog
{
// Construction
public:

	FILENAME settingsFileNm;

	union
	{
		struct
		{
			FILENAME ros;
			FILENAME csv;
			FILENAME tmplt;
			bool useTemplate;
			char delim;
		};
	}
	appData,ad;

	DataGet();
	DataSet();

	ReadSettings();
	WriteSettings();

public:
	CRosterMakerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRosterMakerDlg)
	enum { IDD = IDD_ROSTERMAKER_DIALOG };
	CEdit_Append	outEdit;
	CString	rosName;
	CString	csvName;
	CString	delimChar;
	BOOL	createdTeamsOnly;
	CString	unkTeamField;
	int		ageType;
	BOOL	useTemplate;
	CString	templateName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRosterMakerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRosterMakerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRosBrowse();
	afx_msg void OnCsvBrowse();
	afx_msg void OnImportToRos();
	afx_msg void OnExportToCsv();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnAutoRoster();
	afx_msg void OnTemplateBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROSTERMAKERDLG_H__A7E6FA32_9257_4149_A360_FB4E73111E80__INCLUDED_)
