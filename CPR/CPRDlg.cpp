
// CPRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CPR.h"
#include "CPRDlg.h"
#include "afxdialogex.h"

#include "BATCHDlg.h"

#include "PlateLocate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCPRDlg dialog




CCPRDlg::CCPRDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCPRDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCPRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCPRDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENIMAGE, &CCPRDlg::OnBnClickedButtonOpenimage)
	ON_BN_CLICKED(IDC_BUTTON_BATCHOPERATE, &CCPRDlg::OnBnClickedButtonBatchoperate)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION, &CCPRDlg::OnBnClickedButtonLocation)
END_MESSAGE_MAP()


// CCPRDlg message handlers

BOOL CCPRDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCPRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPRDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPRDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCPRDlg::OnBnClickedButtonOpenimage()
{
	// ���ù�����   
    TCHAR szFilter[] = _T("Image File(*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All File(*.*)|*.*||");   
    // ������ļ��Ի���   
    CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // ��ʾ���ļ��Ի���   
    if (IDOK == fileDlg.DoModal())   
    {   
        // ���������ļ��Ի����ϵġ��򿪡���ť����ѡ����ļ�·����ʾ���༭����   
        strFilePath = fileDlg.GetPathName();  
		//MessageBox(strFilePath);

		IplImage *image = NULL; //ԭʼͼ��
		if(image) cvReleaseImage(&image);
		image = cvLoadImage(strFilePath, 1); //��ʾͼƬ
		m_src = image;
		DrawPicToHDC(image, IDC_ORIGINALIMAGE);
    }   


}


void CCPRDlg::DrawPicToHDC(IplImage * img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf( img ); // ����ͼƬ
	cimg.DrawToHDC( hDC, &rect ); // ��ͼƬ���Ƶ���ʾ�ؼ���ָ��������
	ReleaseDC( pDC );
}


void CCPRDlg::OnBnClickedButtonBatchoperate()
{
	CBATCHDlg dlg;
	dlg.DoModal();
}


void CCPRDlg::OnBnClickedButtonLocation()
{
	UINT ids[] = {IDC_LOCATIONIMAGE1, IDC_LOCATIONIMAGE2, IDC_LOCATIONIMAGE3, 
		IDC_LOCATIONIMAGE4, IDC_LOCATIONIMAGE5, IDC_LOCATIONIMAGE6};

	vector<Mat> resultVec;
	CPlateLocate plate;
	plate.setDebug(1);
	plate.setGaussianBlurSize(5);
	plate.setMorphSizeWidth(17);

	int result = plate.plateLocate(m_src, resultVec);
	if (result == 0)
	{
		int num = resultVec.size();
		for (int j = 0; j < num && j < 6; j++)
		{
			Mat resultMat = resultVec[j];
			IplImage pImg = resultMat;
			DrawPicToHDC(&pImg, ids[j]);
			//imshow("plate_locate", resultMat);
			//waitKey(0);
		}
	}
	
}