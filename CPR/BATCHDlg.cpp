// BATCHDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CPR.h"
#include "BATCHDlg.h"
#include "afxdialogex.h"

#include "PlateLocate.h"
#include "PlateJudge.h"

#include "prep.h"



// CBATCHDlg 对话框

IMPLEMENT_DYNAMIC(CBATCHDlg, CDialogEx)

CBATCHDlg::CBATCHDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBATCHDlg::IDD, pParent)
{
	m_path = _T("");
	m_res = _T("");
	m_savepath = _T("");
}

CBATCHDlg::~CBATCHDlg()
{
}

void CBATCHDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_path);
	DDX_Text(pDX, IDC_EDIT_RES, m_res);
	DDX_Control(pDX, IDC_EDIT_PATH, m_ctr_path);
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_savepath);
}


BEGIN_MESSAGE_MAP(CBATCHDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SELETEPATH, &CBATCHDlg::OnBnClickedButtonSeletepath)
	ON_BN_CLICKED(IDC_BUTTON_SAVEPATH, &CBATCHDlg::OnBnClickedButtonSavepath)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION, &CBATCHDlg::OnBnClickedButtonLocation)
	ON_BN_CLICKED(IDC_BUTTON_CHANNEL1, &CBATCHDlg::OnBnClickedButtonChannel1)
	ON_BN_CLICKED(IDC_BUTTON_JUDGE, &CBATCHDlg::OnBnClickedButtonJudge)
END_MESSAGE_MAP()


// CBATCHDlg 消息处理程序


void CBATCHDlg::OnBnClickedButtonSeletepath()
{
	TCHAR			szFolderPath[MAX_PATH] = {0};
	CString			strFolderPath = TEXT("");
		
	BROWSEINFO		sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot   = 0;
	sInfo.lpszTitle   = _T("请选择一个文件夹：");
	sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn     = NULL;

	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
		{
			strFolderPath = szFolderPath;
			m_path = strFolderPath;
			
			CString str_file = strFolderPath;
			
			CString res_str;
			m_images.clear();

			CString suffixs[] = {"\\*.jpg","\\*.jpeg","\\*.bmp","\\*.png"};
			for(int i = 0; i < 4; ++i)
			{
				CFileFind finder;
				CString filepathname;
				BOOL YesNo=finder.FindFile(str_file + suffixs[i]);
				while (YesNo)
				{
					YesNo=finder.FindNextFile();
					filepathname=finder.GetFilePath();
					m_images.push_back(filepathname);
				}
			}

			for(vector<CString>::size_type v_i = 0; v_i != m_images.size(); ++v_i)
			{
				res_str += m_images[v_i];
				res_str += "\r\n";
			}

			m_res = res_str;

			UpdateData(FALSE);
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}




}


void CBATCHDlg::OnBnClickedButtonSavepath()
{
	TCHAR			szFolderPath[MAX_PATH] = {0};
	CString			strFolderPath = TEXT("");
		
	BROWSEINFO		sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot   = 0;
	sInfo.lpszTitle   = _T("请选择一个文件夹：");
	sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	sInfo.lpfn     = NULL;

	// 显示文件夹选择对话框
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名
		if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
		{
			strFolderPath = szFolderPath;
			this->m_savepath = strFolderPath;
			
			UpdateData(FALSE);
			
		}
	}
	if(lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
}


void CBATCHDlg::OnBnClickedButtonLocation()
{

	CPlateLocate plate;
	plate.setDebug(0);
	plate.setGaussianBlurSize(5);
	plate.setMorphSizeWidth(17);


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateLocate(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			for (int j = 0; j < num; j++)
			{
				Mat resultMat = resultVec[j];
				//IplImage pImg = resultMat;
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << v_i << "_location" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}

}


void CBATCHDlg::OnBnClickedButtonChannel1()
{
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);

		for (cv::Mat_<cv::Vec3b>::iterator it= src.begin<cv::Vec3b>() ; it!= src.end<cv::Vec3b>(); ++it) {  
			int tmp = (abs((*it)[0] - (*it)[1]) + abs((*it)[0] - (*it)[2]));
			if(tmp > 255) tmp = 255;
			(*it)[0] = (*it)[1] = (*it)[2] = tmp;
		}  

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << v_i << "_channel1" << ".jpg";
		imwrite(ss.str(), src);

	}
}


void CBATCHDlg::OnBnClickedButtonJudge()
{
	// TODO:
	CPlateJudge plate;
	plate.setDebug(0);


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateJudge(src);
		if (result == 1)
		{
			stringstream ss(stringstream::in | stringstream::out);
			ss << this->m_savepath << "\\" << v_i << "_judge" << ".jpg";
			imwrite(ss.str(), src);
		}
	}
}
