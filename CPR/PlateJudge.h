#pragma once
//////////////////////////////////////////////////////////////////////////
// Name:	    plate_judge Header
// Version:		1.1
// Date:	    2014-09-22
// MData:		2015-01-29
// Author:	    liuruoze
// MAuthor:		WayneWu
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:  
// Defines CPlateLocate
//////////////////////////////////////////////////////////////////////////
#ifndef __PLATE_JUDGE_H__
#define __PLATE_JUDGE_H__

#include <highgui.h>

using namespace cv;

class CPlateJudge 
{
public:
	CPlateJudge();

	//! 车牌判断
	int plateJudge(const vector<Mat>&, vector<Mat>&);
	int plateJudge(Mat src);

	//! 直方图均衡
	Mat histeq(Mat, int = 0);

	//! 装载SVM模型
	void LoadModel();

	//! 装载SVM模型
	void LoadModel(string s);

	//! 设置与读取模型路径
	inline void setModelPath(string path){	m_path = path;	}
	inline string getModelPath() const{	 return m_path;	}

	inline void setDebug(int param){ m_debug = param;}

	//! 是否开启调试模式常量，默认0代表关闭
	static const int DEFAULT_DEBUG = 0;

private:
	//！使用的SVM模型
	CvSVM svm;

	//! 模型存储路径
	string m_path;

protected:
	//! 是否开启调试模式，0关闭，非0开启
	int m_debug;
};

#endif /* endif __PLATE_JUDGE_H__ */