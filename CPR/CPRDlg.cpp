
// CPRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CPR.h"
#include "CPRDlg.h"
#include "afxdialogex.h"

#include "BATCHDlg.h"

#include "PlateLocate.h"
#include "PlateJudge.h"
#include "PlateDetect.h"

#include "prep.h"

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
	ON_BN_CLICKED(IDC_BUTTON_JUDGE, &CCPRDlg::OnBnClickedButtonJudge)
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CCPRDlg::OnBnClickedButtonDetect)
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
	// 设置过滤器   
    TCHAR szFilter[] = _T("Image File(*.jpg;*.jpeg;*.png;*.bmp)|*.jpg;*.jpeg;*.png;*.bmp|All File(*.*)|*.*||");   
    // 构造打开文件对话框   
    CFileDialog fileDlg(TRUE, NULL, NULL, 0, szFilter, this);   
    CString strFilePath;   
  
    // 显示打开文件对话框   
    if (IDOK == fileDlg.DoModal())   
    {   
        // 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
        strFilePath = fileDlg.GetPathName();  
		//MessageBox(strFilePath);

		IplImage *image = NULL; //原始图像
		if(image) cvReleaseImage(&image);
		image = cvLoadImage(strFilePath, 1); //显示图片
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
	cimg.CopyOf( img ); // 复制图片
	cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
	ReleaseDC( pDC );
}

UINT ids[] = {IDC_LOCATIONIMAGE1, IDC_LOCATIONIMAGE2, IDC_LOCATIONIMAGE3, 
	IDC_LOCATIONIMAGE4, IDC_LOCATIONIMAGE5, IDC_LOCATIONIMAGE6};

void CCPRDlg::ResetDisImg()
{

	IplImage *defaultImg = cvCreateImage(cvSize(1,1), 8, 1);
	CvScalar scalar = cvGet2D(defaultImg, 0, 0);
	scalar.val[0] = 105;
	cvSet2D(defaultImg, 0, 0, scalar);

	for(int i = 0; i < 6; ++i)
	{
		CDC *pDC = GetDlgItem(ids[i])->GetDC();
		HDC hDC= pDC->GetSafeHdc();
		CRect rect;
		GetDlgItem(ids[i])->GetClientRect(&rect);
		CvvImage cimg;
		cimg.CopyOf( defaultImg ); // 复制图片
		cimg.DrawToHDC( hDC, &rect ); // 将图片绘制到显示控件的指定区域内
		ReleaseDC( pDC );
	}

}


void CCPRDlg::OnBnClickedButtonBatchoperate()
{
	CBATCHDlg dlg;
	dlg.DoModal();
}



void CCPRDlg::OnBnClickedButtonLocation()
{

	m_locs.clear();
	CPlateLocate plate;
	plate.setDebug(1);
	plate.setGaussianBlurSize(5);
	plate.setMorphSizeWidth(17);

	int result = plate.plateLocate(m_src, m_locs);
	if (0 == result)
	{
		for (int j = 0; j < m_locs.size() && j < 6; j++)
		{
			Mat resultMat = m_locs[j];
			IplImage pImg = resultMat;
			DrawPicToHDC(&pImg, ids[j]);
		}
	}
	
}


void CCPRDlg::OnBnClickedButtonJudge()
{

	//经过SVM判断后得到的图块集合
	m_jdgs.clear();

	CPlateJudge ju;
	ju.setDebug(1);
	int resultJu = ju.plateJudge(m_locs, m_jdgs);
	
	ResetDisImg();
	if (0 == resultJu)
	{
		for (int j = 0; j < m_jdgs.size() && j < 6; j++)
		{
			Mat resultMat = m_jdgs[j];
			IplImage pImg = resultMat;
			DrawPicToHDC(&pImg, ids[j]);
		}
	}

	return;
}


void CCPRDlg::OnBnClickedButtonDetect()
{
	// TODO: 
	m_dtts.clear();

	CPlateDetect pd;

	int result = pd.plateDetect(m_src, m_dtts);

	if (0 == result)
	{
		for (int j = 0; j < m_dtts.size() && j < 6; j++)
		{
			Mat resultMat = m_dtts[j];
			IplImage pImg = resultMat;
			DrawPicToHDC(&pImg, ids[j]);
		}
	}

	return;
}
