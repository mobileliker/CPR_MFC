// BATCHDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CPR.h"
#include "BATCHDlg.h"
#include "afxdialogex.h"

#include "PlateLocate.h"
#include "PlateJudge.h"
#include "PlateDetect.h"
#include "CharsIdentify.h"
#include "CharsSegment.h"
#include "CharsRecognise.h"
#include "PlateRecognize.h"

#include <fstream>
#include <direct.h>

#include <time.h>

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
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CBATCHDlg::OnBnClickedButtonDetect)
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT, &CBATCHDlg::OnBnClickedButtonSegment)
	ON_BN_CLICKED(IDC_BUTTON_IDENTIFY, &CBATCHDlg::OnBnClickedButtonIdentify)
	ON_BN_CLICKED(IDC_BUTTON_RECOGNISE, &CBATCHDlg::OnBnClickedButtonRecognise)
	ON_BN_CLICKED(IDC_BUTTON_IDENTIFYOTHERS, &CBATCHDlg::OnBnClickedButtonRecogniseothers)
	ON_BN_CLICKED(IDC_BUTTON_PLATERECOGNIZE, &CBATCHDlg::OnBnClickedButtonPlaterecognize)
	ON_BN_CLICKED(IDC_BUTTON_BINARY, &CBATCHDlg::OnBnClickedButtonBinary)
	ON_BN_CLICKED(IDC_BUTTON_LOCATION2, &CBATCHDlg::OnBnClickedButtonLocation2)
	ON_BN_CLICKED(IDC_BUTTON_SEGMENT2, &CBATCHDlg::OnBnClickedButtonSegment2)
	ON_BN_CLICKED(IDC_BUTTON_Resize, &CBATCHDlg::OnBnClickedButtonResize)
	ON_BN_CLICKED(IDC_BUTTON_PLATERECOGNIZE2, &CBATCHDlg::OnBnClickedButtonPlaterecognize2)
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
	plate.setMorphSizeHeight(10);
	plate.setVerifyMin(8);
	plate.setVerifyMax(80);


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
			/*if((*it)[2] > 100) tmp = 0;
			if(abs((*it)[2] - (*it)[1]) > 70) tmp = 0;*/
			(*it)[0] = (*it)[1] = (*it)[2] = tmp;
		}  

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << v_i << "_channel1" << ".jpg";
		imwrite(ss.str(), src);

	}

	MessageBox("Finish");
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


void CBATCHDlg::OnBnClickedButtonDetect()
{
	// TODO: 
	CPlateDetect plate;


	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.plateDetect(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			for (int j = 0; j < num; j++)
			{
				Mat resultMat = resultVec[j];
				//IplImage pImg = resultMat;
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << v_i << "_detect" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}


void CBATCHDlg::OnBnClickedButtonSegment()
{	
	_mkdir(m_savepath + "\\chinese");
	_mkdir(m_savepath + "\\others");

	CCharsSegment plate;

	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 1);
		int result = plate.charsSegment(src, resultVec);
		if (0 == result)
		{
			for (int j = 0; j < resultVec.size(); j++)
			{
				Mat resultMat = resultVec[j];
				stringstream ss(stringstream::in | stringstream::out);
				if(0 == j)	ss << m_savepath << "\\chinese\\" << v_i << "_segment" << j << ".jpg";
				else ss << m_savepath << "\\others\\" << v_i << "_segment" << j << ".jpg";
				imwrite(ss.str(), resultMat);
			}
		}
	}
}


void CBATCHDlg::OnBnClickedButtonIdentify()
{
	CCharsIdentify plate;
	string res_str = "";
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";

		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 0);
			
		string str_cr = plate.charsIdentify(src, true);
		if ("" != str_cr)
		{
			res_str += str_cr;
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\identify_chinese.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonRecognise()
{	
	CCharsRecognise plate;
	string res_str = "";
	
	int num_char = 0;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";

		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);
		
		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 1);
		string str_cr;
		int result = plate.charsRecognise(src, str_cr);
		if (result == 0)
		{
			res_str += str_cr;
			res_str += "\r\n";
			for(int j = 2; j < str_cr.size() && j < 8; ++j)
			{
				if(str_cr[j] == name[j]) ++num_char;
			}
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	res_str += "Char accuracy rate:";
	char buffer[50];
	sprintf(buffer,"%f\0",1.0 * num_char / (m_images.size() * 6));
	res_str += buffer;
	res_str += "\r\n";


	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\recognise.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonRecogniseothers()
{		
	CCharsIdentify plate;
	string res_str = "";
	
	int num_char = 0;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		res_str += m_images[v_i];
		res_str += " Result: ";
		string str = m_images[v_i].GetBuffer(0);		
		
		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 0);
				
		Mat src_resize;
		src_resize.create(20, 20, 16);

		resize(src, src_resize, src_resize.size(), 0, 0, INTER_CUBIC);

		string str_cr = plate.charsIdentify(src_resize, false);
		if ("" != str_cr)
		{
			res_str += str_cr;
			res_str += "\r\n";
			if(name[0] == str_cr[0]) ++num_char;
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	res_str += "Char accuracy rate:";
	char buffer[50];
	sprintf(buffer,"%f\0",1.0 * num_char / m_images.size());
	res_str += buffer;
	res_str += "\r\n";

	m_res = res_str.c_str();
	UpdateData(FALSE);

	
	CString filePath = this->m_savepath + "\\identify_others.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();

}


void CBATCHDlg::OnBnClickedButtonPlaterecognize()
{	
	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	pr.setGaussianBlurSize(5);
	pr.setMorphSizeWidth(17);

	pr.setVerifyMin(3);
	pr.setVerifyMax(20);

	pr.setLiuDingSize(7);
	pr.setColorThreshold(150);

	string res_str = "";
	
	int num_char = 0;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<string> plateVec;

		res_str += m_images[v_i];
		res_str += " Result: ";

		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 1);
		string str_cr;

		int result = pr.plateRecognize(src, plateVec);
		if (result == 0)
		{

			for(int i = 0; i < plateVec.size(); ++i) 
			{ 
				res_str += " ";
				res_str += plateVec[i]; 
				for(int j = 2; j < plateVec[i].size() && j < 8; ++j)
				{
					if(plateVec[i][j] == name[j]) ++num_char;
				}
			}
			res_str += "\r\n";
		}
		else
		{
			res_str += "No Answer\r\n";
		}
	}
	res_str += "Char accuracy rate:";
	res_str += (1.0 * num_char / (m_images.size() * 6));
	res_str += "\r\n";

	m_res = res_str.c_str();
	UpdateData(FALSE);

	CString filePath = this->m_savepath + "\\plate_recognize.txt";
	std::ofstream resfile(filePath);
	resfile << res_str.c_str();
	resfile.close();
}


void CBATCHDlg::OnBnClickedButtonBinary()
{
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		string str = m_images[v_i].GetBuffer(0);
		Mat src = imread(str, 0);

		Mat img_threshold;
		//threshold(src, img_threshold, 0, 255, CV_THRESH_OTSU+CV_THRESH_BINARY);
		threshold(src, img_threshold, 100, 255, CV_THRESH_BINARY);

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << v_i << "_binary" << ".jpg";
		imwrite(ss.str(), img_threshold);

	}

	MessageBox("Finish.");
}


void CBATCHDlg::OnBnClickedButtonLocation2()
{

	CPlateLocate plate;	plate.setDebug(1);
	//plate.setVerifyMax(500);
	//plate.setVerifyMin(50);
	
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{			
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		vector<Mat> resultVec;
		Mat src = imread(str, 1);
		int result = plate.plateLocate2(src, resultVec);
		if (result == 0)
		{
			int num = resultVec.size();
			if(1 == num)
			{
				Mat resultMat = resultVec[0];
				stringstream ss(stringstream::in | stringstream::out);
				ss << this->m_savepath << "\\" << name << ".jpg";
				imwrite(ss.str(), resultMat);
			}
			else
			{
				for (int j = 0; j < num; j++)
				{
					Mat resultMat = resultVec[j];
					stringstream ss(stringstream::in | stringstream::out);
					ss << this->m_savepath << "\\" << name << "_" << j << ".jpg";
					imwrite(ss.str(), resultMat);
				}
			}

		}
	}
	
	MessageBox("Finish.");
}


void CBATCHDlg::OnBnClickedButtonSegment2()
{
	string str_idx_sf[] = 
	{ "冀","豫","云","辽","黑",
		"湘","皖","鲁","新","苏","浙","赣","鄂",
		"桂","甘","晋","蒙","陕","吉","闽",
		"贵","粤","青","藏","川","宁","琼",
		"渝","京","津","沪"};

	string str_sf[] = {
		"zh_ji", /*冀*/
		"zh_yu", /*豫*/
		"zh_yun",/*云*/
		"zh_liao",/*辽*/
		"zh_hei",/*黑*/
		"zh_xiang",/*湘*/
		"zh_wan",/*皖*/
		"zh_lu",/*鲁*/
		"zh_xin",/*新*/
		"zh_su",/*苏*/
		"zh_zhe",/*浙*/
		"zh_gan",/*赣*/
		"zh_e",/*鄂*/
		"zh_gui",/*桂*/
		"zh_gan2",/*甘*/
		"zh_sx",/*晋*/
		"zh_meng",/*蒙*/
		"zh_shan",/*陕*/
		"zh_jl",/*吉*/
		"zh_min",/*闽*/
		"zh_gui2",/*贵*/
		"zh_yue",/*粤*/
		"zh_qing",/*青*/
		"zh_zan",/*藏*/
		"zh_cuan",/*川*/
		"zh_ning",/*宁*/
		"zh_qiong",/*琼*/
		"zh_yu2",/*渝*/
		"zh_jing",/*京*/
		"zh_jin",/*津*/
		"zh_hu"/*沪*/
		};

	_mkdir(m_savepath + "\\charsChinese");
	_mkdir(m_savepath + "\\chars2");
	_mkdir(m_savepath + "\\allchars");
	_mkdir(m_savepath + "\\allchinese");

	int i;
	for(i = 0; i < 10; ++i) _mkdir(m_savepath + "\\chars2\\" + (char)(i + '0'));
	for(i = (int)'A'; i <= (int)'Z'; ++i) _mkdir(m_savepath + "\\chars2\\" + (char)i);
	for(i = 0; i < 31; ++i) _mkdir(m_savepath + "\\charsChinese\\" + str_sf[i].c_str());

	CCharsSegment plate;

	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);
		CString cstr = str.c_str();

		Mat src = imread(str, 1);
		int result = plate.charsSegment2(src, resultVec);
		if (0 == result)
		{
			for (int j = 0; j < resultVec.size(); j++)
			{
				time_t rawtime;
				time ( &rawtime );
				Mat resultMat = resultVec[j];
				stringstream ss(stringstream::in | stringstream::out);
				stringstream ss2(stringstream::in | stringstream::out);
				if(0 == j)
				{
					string sf = name.substr(0, 2);
					for(i = 0; i < 31; ++i)
					{
						if(sf == str_idx_sf[i]) break;
					}
					ss << m_savepath << "\\charsChinese\\" << str_sf[i] << "\\" << str_sf[i] << "_" << v_i <<"_" << rawtime <<".jpg";
					ss2 << m_savepath << "\\allchinese\\" << str_sf[i] << "_" << v_i <<"_" << rawtime <<".jpg";
				}
				else
				{
					ss << m_savepath << "\\chars2\\" << name[j + 1] << "\\" << name[j + 1] << "_" << v_i << "_" << j << "_" << rawtime <<".jpg";
					ss2 << m_savepath << "\\allchars\\" << name[j + 1] << "_" << v_i << "_" << j << "_" << rawtime <<".jpg";
				}
				
				imwrite(ss.str(), resultMat);
				imwrite(ss2.str(), resultMat);			
			}
		}
	}
	
	MessageBox("Finish.");
}


void CBATCHDlg::OnBnClickedButtonResize()
{
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{			
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		vector<Mat> resultVec;
		Mat src = imread(str, 0);
						
		Mat src_resize;
		src_resize.create(20, 20, 16);

		resize(src, src_resize, src_resize.size(), 0, 0, INTER_CUBIC);

		stringstream ss(stringstream::in | stringstream::out);
		ss << this->m_savepath << "\\" << name << ".jpg";
		imwrite(ss.str(), src_resize);

	}
	MessageBox("Finish.");

}


void CBATCHDlg::OnBnClickedButtonPlaterecognize2()
{
	int i;
	
	CPlateRecognize pr;
	pr.LoadANN("model/ann.xml");
	pr.LoadSVM("model/svm.xml");

	//pr.setGaussianBlurSize(5);
	//pr.setMorphSizeWidth(17);

	//pr.setVerifyMin(3);
	//pr.setVerifyMax(20);

	//pr.setLiuDingSize(7);
	pr.setColorThreshold(150);

	stringstream ss(stringstream::in | stringstream::out);
	
	int num_char = 0;
	int num_plate = 0;
	for(vector<CString>::size_type v_i = 0; v_i < m_images.size(); ++v_i)
	{	
		vector<string> plateVec;

		ss << m_images[v_i] << " Result: ";

		vector<Mat> resultVec;
		string str = m_images[v_i].GetBuffer(0);

		int index1 = str.find_last_of("\\");
		int index2 = str.find_last_of(".");
		string name = str.substr(index1 + 1,index2 - index1 - 1);

		Mat src = imread(str, 1);
		string str_cr;

		int result = pr.plateRecognize2(src, plateVec);
		int max_tmp;
		int num_tmp;
		if (result == 0)
		{
			num_tmp = 0;
			max_tmp = 0;
			for(i = 0; i < plateVec.size(); ++i) 
			{ 
				num_tmp = 0;
				ss << " " << plateVec[i];
				if(2 <= plateVec[i].size() && plateVec[i][0] == name[0]) ++num_tmp;
				for(int j = 2; j < plateVec[i].size() && j <= 8; ++j)
				{
					if(plateVec[i][j] == name[j]) ++num_tmp;
				}
				if(num_tmp > max_tmp) max_tmp = num_tmp;
			}
			if(max_tmp == 7) ++num_plate;
			num_char += max_tmp;
			ss << "\r\n";
		}
		else
		{
			ss << "No Answer\r\n";
		}
	}

	ss << "Char accuracy rate:" << (1.0 * num_char / (m_images.size() * 7)) << "\r\n";
	ss << "Plate accuracy rate:" << (1.0 * num_plate / m_images.size()) << "\r\n";

	m_res = ss.str().c_str();
	UpdateData(FALSE);

	CString filePath = this->m_savepath + "\\plate_recognize.txt";
	std::ofstream resfile(filePath);
	resfile << ss.str().c_str();
	resfile.close();
}
