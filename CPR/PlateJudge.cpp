#include "StdAfx.h"
#include "PlateJudge.h"

#include "prep.h"

CPlateJudge::CPlateJudge()
{
	//cout << "CPlateJudge" << endl;
	m_path = "model/svm.xml";
	LoadModel();

	m_debug = DEFAULT_DEBUG;
}

void CPlateJudge::LoadModel()
{
	svm.clear();
	svm.load(m_path.c_str(), "svm");
}

void CPlateJudge::LoadModel(string s)
{
	svm.clear();
	svm.load(s.c_str(), "svm");
}

//! 直方图均衡
Mat CPlateJudge::histeq(Mat in,int index)
{
	Mat out(in.size(), in.type());
	if(in.channels()==3)
	{
		Mat hsv;
		vector<Mat> hsvSplit;
		cvtColor(in, hsv, CV_BGR2HSV);
		split(hsv, hsvSplit);
		equalizeHist(hsvSplit[2], hsvSplit[2]);
		merge(hsvSplit, hsv);
		cvtColor(hsv, out, CV_HSV2BGR);
	}
	else if(in.channels()==1)
	{
		equalizeHist(in, out);
	}

	if(m_debug)
	{ 
		stringstream ss(stringstream::in | stringstream::out);
		ss << "tmp/debug_histeq_" << index << ".jpg";
		imwrite(ss.str(), out);
	}

	return out;
}


//! 使用色彩图进行SVM判断
int CPlateJudge::plateJudge(Mat src)
{
	//通过色彩直方图进行预测
	Mat p = histeq(src).reshape(1, 1);

	if(m_debug)
	{ 
		stringstream ss(stringstream::in | stringstream::out);
		ss << "tmp/debug_reshape_0" << ".jpg";
		imwrite(ss.str(), p);
	}

	p.convertTo(p, CV_32FC1);
	int response = (int)svm.predict(p);
	return response;
}

//! 使用色彩图进行SVM判断
int CPlateJudge::plateJudge(const vector<Mat>& inVec,
								  vector<Mat>& resultVec)
{
	int num = inVec.size();
	for (int j = 0; j < num; j++)
	{
		Mat inMat = inVec[j];

		//通过色彩直方图进行预测
		Mat p = histeq(inMat, j).reshape(1, 1);

		if(m_debug)
		{ 
			stringstream ss(stringstream::in | stringstream::out);
			ss << "tmp/debug_reshape_" << j << ".jpg";
			imwrite(ss.str(), p);
		}

		p.convertTo(p, CV_32FC1);
		int response = (int)svm.predict(p);
		if (response == 1)
		{
			resultVec.push_back(inMat);
		}
	}
	return 0;
}

