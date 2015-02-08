
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
#include "CharsSegment.h"
#include "CharsIdentify.h"
#include "CharsRecognise.h"
#include "PlateRecognize.h"

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
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT, &CCPRDlg::OnBnClickedButtonSegment)
	ON_BN_CLICKED(IDC_BUTTON_IDENTIFY, &CCPRDlg::OnBnClickedButtonIdentify)
	ON_BN_CLICKED(IDC_BUTTON_RECOGNISE, &CCPRDlg::OnBnClickedButtonRecognise)
	ON_BN_CLICKED(IDC_BUTTON_PLATERECOGNIZE, &CCPRDlg::OnBnClickedButtonPlaterecognize)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL1, &CCPRDlg::OnBnClickedButtonChannel1)
	ON_BN_CLICKED(IDC_BUTTON_BINARY, &CCPRDlg::OnBnClickedButtonBinary)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION2, &CCPRDlg::OnBnClickedButtonLocation2)
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT2, &CCPRDlg::OnBnClickedButtonSegment2)
	ON_BN_CLICKED(IDC_BUTTON_JUDGE2, &CCPRDlg::OnBnClickedButtonJudge2)
	ON_BN_CLICKED(IDC_BUTTON_RECOGNISE2, &CCPRDlg::OnBnClickedButtonRecognise2)
	ON_BN_CLICKED(IDC_BUTTON_PLATERECOGNIZE2, &CCPRDlg::OnBnClickedButtonPlaterecognize2)
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
	//plate.setMorphSizeWidth(17);
	plate.setMorphSizeWidth(17);
	plate.setMorphSizeHeight(10);
	plate.setVerifyMin(8);
	plate.setVerifyMax(80);

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


UINT idss[][7] = 
{
	{IDC_SEGMENT11, IDC_SEGMENT12, IDC_SEGMENT13, IDC_SEGMENT14, IDC_SEGMENT15, IDC_SEGMENT16, IDC_SEGMENT17},
	{IDC_SEGMENT21, IDC_SEGMENT22, IDC_SEGMENT23, IDC_SEGMENT24, IDC_SEGMENT25, IDC_SEGMENT26, IDC_SEGMENT27},
	{IDC_SEGMENT31, IDC_SEGMENT32, IDC_SEGMENT33, IDC_SEGMENT34, IDC_SEGMENT35, IDC_SEGMENT36, IDC_SEGMENT37},
	{IDC_SEGMENT41, IDC_SEGMENT42, IDC_SEGMENT43, IDC_SEGMENT44, IDC_SEGMENT45, IDC_SEGMENT46, IDC_SEGMENT47},
	{IDC_SEGMENT51, IDC_SEGMENT52, IDC_SEGMENT53, IDC_SEGMENT54, IDC_SEGMENT55, IDC_SEGMENT56, IDC_SEGMENT57},
	{IDC_SEGMENT61, IDC_SEGMENT62, IDC_SEGMENT63, IDC_SEGMENT64, IDC_SEGMENT65, IDC_SEGMENT66, IDC_SEGMENT67}
}
;

void CCPRDlg::OnBnClickedButtonSegment()
{
	m_sgms.clear();
	CCharsSegment plate;
	plate.setDebug(1);

	
	for(vector<Mat>::size_type v_i = 0; v_i != m_jdgs.size(); ++v_i)
	{
		vector<Mat> v_dst;
		int result = plate.charsSegment(m_jdgs[v_i], v_dst);
		if(0 == result)
		{
			m_sgms.push_back(v_dst);
			if(v_i < 6)
			{
				for(int i = 0; i < 7 && i < v_dst.size(); ++i)
				{
					IplImage pImg = v_dst[i];
					DrawPicToHDC(&pImg, idss[v_i][i]);
				}
			}
		}

	}
}

UINT res_ids[] = {IDC_RES1, IDC_RES2, IDC_RES3, IDC_RES4, IDC_RES5, IDC_RES6};

void CCPRDlg::ResetResStr()
{
	for(int i = 0; i < 6; ++i)
	{
		GetDlgItem(res_ids[i])->SetWindowTextA("");
	}
}

void CCPRDlg::OnBnClickedButtonIdentify()
{
	CCharsIdentify ci;

	ResetResStr();

	for(int i = 0; i < m_sgms.size(); ++i)
	{
		string plateIdentify = "";
		for(int j = 0; j < m_sgms[i].size(); ++j)
		{
			bool isChinses = (0 == j) ? true : false;
			string characater = ci.charsIdentify(m_sgms[i][j], isChinses);
			plateIdentify += characater;
		}
		if(i < 6)
		{
			GetDlgItem(res_ids[i])->SetWindowTextA(plateIdentify.c_str());
		}
	}
}


void CCPRDlg::OnBnClickedButtonRecognise()
{
	ResetResStr();

	CCharsRecognise cr;
	string charsRecognise = "";

	for(int i = 0; i < m_dtts.size(); ++i)
	{
		int result = cr.charsRecognise(m_dtts[i], charsRecognise);
		if (0 == result)
		{
			//MessageBox(charsRecognise.c_str());		
			if(i < 6)
			{
				GetDlgItem(res_ids[i])->SetWindowTextA(charsRecognise.c_str());
			}
		}
	}
}


void CCPRDlg::OnBnClickedButtonPlaterecognize()
{
	ResetResStr();

	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	pr.setGaussianBlurSize(5);
	pr.setMorphSizeWidth(17);

	pr.setVerifyMin(3);
	pr.setVerifyMax(20);

	pr.setLiuDingSize(7);
	pr.setColorThreshold(150);

	vector<string> plateVec;

	int result = pr.plateRecognize(m_src, plateVec);
	if (result == 0)
	{
		int num = plateVec.size();
		for (int j = 0; j < num; j++)
		{
			if(j < 6)
			{
				GetDlgItem(res_ids[j])->SetWindowTextA(plateVec[j].c_str());
			}
		}
	}

}


void CCPRDlg::OnBnClickedButtonChannel1()
{

	m_channel;
	m_src.copyTo(m_channel);

	for (cv::Mat_<cv::Vec3b>::iterator it= m_channel.begin<cv::Vec3b>() ; it!= m_channel.end<cv::Vec3b>(); ++it) {  
		int tmp = (int)(((*it)[0] - (*it)[2]) * 2 + ((*it)[1] - (*it)[2]));
		if(tmp > 255) tmp = 255;
		if(tmp < 0) tmp = 0;
		(*it)[0] = (*it)[1] = (*it)[2] = tmp;
	}
	
	IplImage pImg = m_channel;
	DrawPicToHDC(&pImg, IDC_ORIGINALIMAGE);

}


void CCPRDlg::OnBnClickedButtonBinary()
{
	Mat src_gray;

	//Convert it to gray
	cvtColor(this->m_channel, src_gray, CV_RGB2GRAY );

	Mat img_threshold;
	//threshold(m_channel, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	//threshold(src_gray, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
	threshold(src_gray, img_threshold, 90, 255, CV_THRESH_BINARY);
	
	IplImage pImg = img_threshold;
	DrawPicToHDC(&pImg, IDC_ORIGINALIMAGE);
}


void CCPRDlg::OnBnClickedButtonLocation2()
{
	m_locs.clear();
	CPlateLocate plate;
	plate.setDebug(1);
	//plate.setVerifyMax(500);
	//plate.setVerifyMin(50);

	int result = plate.plateLocate2(m_src, m_locs);
	
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


void CCPRDlg::OnBnClickedButtonSegment2()
{
	m_sgms.clear();
	CCharsSegment plate;
	plate.setDebug(1);

	
	for(vector<Mat>::size_type v_i = 0; v_i != m_locs.size(); ++v_i)
	{
		vector<Mat> v_dst;
		int result = plate.charsSegment2(m_locs[v_i], v_dst);
		if(0 == result)
		{
			m_sgms.push_back(v_dst);
			if(v_i < 6)
			{
				for(int i = 0; i < 7 && i < v_dst.size(); ++i)
				{
					IplImage pImg = v_dst[i];
					DrawPicToHDC(&pImg, idss[v_i][i]);
				}
			}
		}

	}
}


void CCPRDlg::OnBnClickedButtonJudge2()
{
	m_jdgs.clear();

	for(int i = 0; i < m_locs.size(); ++i)
	{
		Mat tmp;
		m_locs[i].copyTo(tmp);
		m_jdgs.push_back(tmp);
	}
	
	ResetDisImg();

	for (int j = 0; j < m_jdgs.size() && j < 6; j++)
	{
		Mat resultMat = m_jdgs[j];
		IplImage pImg = resultMat;
		DrawPicToHDC(&pImg, ids[j]);
	}
	
}


void CCPRDlg::OnBnClickedButtonRecognise2()
{
	ResetResStr();

	CCharsRecognise cr;
	string charsRecognise = "";

	for(int i = 0; i < m_locs.size(); ++i)
	{
		int result = cr.charsRecognise2(m_locs[i], charsRecognise);
		if (0 == result)
		{
			//MessageBox(charsRecognise.c_str());		
			if(i < 6)
			{
				GetDlgItem(res_ids[i])->SetWindowTextA(charsRecognise.c_str());
			}
		}
	}
}


void CCPRDlg::OnBnClickedButtonPlaterecognize2()
{
	ResetResStr();

	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	pr.setGaussianBlurSize(5);
	//pr.setMorphSizeWidth(17);

	//pr.setVerifyMin(3);
	//pr.setVerifyMax(20);

	//pr.setLiuDingSize(7);
	pr.setColorThreshold(150);

	vector<string> plateVec;

	int result = pr.plateRecognize2(m_src, plateVec);
	if (result == 0)
	{
		int num = plateVec.size();
		for (int j = 0; j < num; j++)
		{
			if(j < 6)
			{
				GetDlgItem(res_ids[j])->SetWindowTextA(plateVec[j].c_str());
			}
		}
	}

}
