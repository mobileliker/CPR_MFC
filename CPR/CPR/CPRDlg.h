
// CPRDlg.h : header file
//

#pragma once


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
	afx_msg void OnBnClickedButtonBatchoperate();
};
