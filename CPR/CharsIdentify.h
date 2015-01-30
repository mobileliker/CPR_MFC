#pragma once
//////////////////////////////////////////////////////////////////////////
// Name:	    chars_identify Header
// Version:		1.1
// Date:	    2014-09-25
// MData:		2015-01-30
// Author:	    liuruoze
// MAuthor:		WayneWu
// Copyright:   liuruoze
// Reference:	Mastering OpenCV with Practical Computer Vision Projects
// Reference:	CSDN Bloger taotao1233
// Desciption:
// Defines CCharsIdentify 
//////////////////////////////////////////////////////////////////////////
#ifndef __CHARS_IDENTIFY_H__
#define __CHARS_IDENTIFY_H__

#include <highgui.h>
#include <map>

using namespace cv;
	
class CCharsIdentify 
{
public:
	CCharsIdentify();

	//! 字符分割
	string charsIdentify(Mat, bool);

	//! 字符分类
	int classify(Mat, bool);

	//create the accumulation histograms,img is a binary image, t is 水平或垂直
	Mat ProjectedHistogram(Mat img, int t);

	//! 获得字符的特征图
	Mat features(Mat in, int sizeData);

	//! 装载ANN模型
	void LoadModel();

	//! 装载ANN模型
	void LoadModel(string s);

	//! 设置与读取模型路径
	inline void setModelPath(string path){	m_path = path;	}
	inline string getModelPath() const{	 return m_path;	}

private:
	//！使用的SVM模型
	CvANN_MLP ann;

	//! 模型存储路径
	string m_path;

	//! 特征尺寸
	int m_predictSize;

	//! 省份对应map
	std::map<string, string> m_map;
};

#endif /* endif __CHARS_IDENTIFY_H__ */