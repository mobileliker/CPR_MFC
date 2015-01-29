
// CPRDlg.h : header file
//

#pragma once
#include "d:\program files\opencv2.4.8\build\include\opencv2\core\core.hpp"

#include <highgui.h>

// CCPRDlg dialog
class CCPRDlg : public CDialogEx
{
// Construction
public:
	CCPRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CPR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenimage();
	void DrawPicToHDC(IplImage * img, UINT ID);
	void ResetDisImg();
	afx_msg void OnBnClickedButtonBatchoperate();
	afx_msg void OnBnClickedButtonLocation();
	cv::Mat m_src;
	std::vector<cv::Mat> m_locs;
	std::vector<cv::Mat> m_jdgs;
	std::vector<cv::Mat> m_dtts;
	afx_msg void OnBnClickedButtonJudge();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonSegment();
};
