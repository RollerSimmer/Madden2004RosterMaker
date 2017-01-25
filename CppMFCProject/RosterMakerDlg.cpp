// RosterMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RosterMaker.h"
#include "RosterMakerDlg.h"
#include<direct.h>

#include"../tdbaccess/c++ include/tdbAccess.h"

#include"roster2csv.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRosterMakerDlg dialog

CRosterMakerDlg::CRosterMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRosterMakerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRosterMakerDlg)
	rosName = _T("");
	csvName = _T("");
	delimChar = _T("");
	createdTeamsOnly = FALSE;
	unkTeamField = _T("");
	ageType = -1;
	useTemplate = FALSE;
	templateName = _T("");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRosterMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRosterMakerDlg)
	DDX_Control(pDX, IDC_OUTPUT, outEdit);
	DDX_Text(pDX, IDC__ROS_NAME, rosName);
	DDV_MaxChars(pDX, rosName, 512);
	DDX_Text(pDX, IDC__CSV_NAME, csvName);
	DDV_MaxChars(pDX, csvName, 512);
	DDX_Text(pDX, IDC_DELIM, delimChar);
	DDV_MaxChars(pDX, delimChar, 1);
	//DDX_Text(pDX, IDC__EDIT__UNK_TEAM_FIELD, unkTeamField);
	DDV_MaxChars(pDX, unkTeamField, 4);
	//DDX_CBIndex(pDX, IDC__ROSTER_AGE_TYPE, ageType);
	DDX_Check(pDX, IDC__CHECK__USE_TEMPLATE, useTemplate);
	DDX_Text(pDX, IDC__TEMPLATE_NAME, templateName);
	DDV_MaxChars(pDX, templateName, 512);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRosterMakerDlg, CDialog)
	//{{AFX_MSG_MAP(CRosterMakerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC__ROS_BROWSE, OnRosBrowse)
	ON_BN_CLICKED(IDC__CSV_BROWSE, OnCsvBrowse)
	ON_BN_CLICKED(IDC__IMPORT_TO_ROS, OnImportToRos)
	ON_BN_CLICKED(IDC__EXPORT_TO_CSV, OnExportToCsv)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC__AUTO_ROSTER, OnAutoRoster)
	ON_BN_CLICKED(IDC__TEMPLATE_BROWSE, OnTemplateBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRosterMakerDlg message handlers

BOOL CRosterMakerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	ReadSettings();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRosterMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRosterMakerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CRosterMakerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRosterMakerDlg::OnRosBrowse() 
{
	// TODO: Add your control notification handler code here

	DataGet();

	GetSaveFileName_SuperQuick(ad.ros,"ROS");
	DataSet();
}

void CRosterMakerDlg::OnCsvBrowse() 
{
	// TODO: Add your control notification handler code here
	
	DataGet();
	GetSaveFileName_SuperQuick(ad.csv,"CSV");
	DataSet();
}

void CRosterMakerDlg::OnImportToRos() 
{
	// TODO: Add your control notification handler code here
	
}


void CRosterMakerDlg::OnExportToCsv() 
{
	// TODO: Add your control notification handler code here

	DataGet();
	Ros2Csv(~ad.ros,~ad.csv,this->outEdit);
	DataSet();
	
}

const bool
	DX_SET=false,
	DX_GET=!DX_SET;

CRosterMakerDlg::DataSet()
{
	csvName=~ad.csv;
	rosName=~ad.ros;
	templateName=~ad.tmplt;
	useTemplate=ad.useTemplate;
	delimChar=ad.delim;
	UpdateData(DX_SET);
}

CRosterMakerDlg::DataGet()
{
	UpdateData(DX_GET);
	ad.csv=csvName.GetBuffer(0);
	ad.ros=rosName.GetBuffer(0);
	ad.tmplt=templateName.GetBuffer(0);
	ad.useTemplate=useTemplate;
	ad.delim=delimChar[0];
}

CRosterMakerDlg::ReadSettings()
{
	FILE*setF;
	_getcwd(~settingsFileNm,sz(settingsFileNm));
	settingsFileNm>>"rosMak_settings.bin";
	setF=fopen(~settingsFileNm,"r+b");
	if(setF!=NULL)
	{
		fread(&ad,sz(ad),1,setF);
		fclose(setF);
	}
	else
		memset(&ad,0,sz(ad));
	DataSet();
}

CRosterMakerDlg::WriteSettings()
{
	FILE*setF;
	DataGet();
	setF=fopen(~settingsFileNm,"w+b");
	if(setF!=NULL)
	{
		fwrite(&ad,sz(ad),1,setF);
		fclose(setF);
	}
}

void CRosterMakerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	WriteSettings();
	
}

void CRosterMakerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	WriteSettings();


	CDialog::OnClose();
}


//******* Functions *******


void CRosterMakerDlg::OnAutoRoster() 
{
	// TODO: Add your control notification handler code here

	DataGet();

	short ageType=3;

	AutoRos
	(	
		~ad.ros,this->outEdit,createdTeamsOnly
		,unkTeamField,ageType,useTemplate
		,~ad.tmplt
	);

	DataSet();

	
}

void CRosterMakerDlg::OnTemplateBrowse() 
{
	// TODO: Add your control notification handler code here

	DataGet();

	GetSaveFileName_SuperQuick(ad.tmplt,"TXT");
	DataSet();
	
}
