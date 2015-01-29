#pragma once

#include <highgui.h>

using namespace cv;

class CPlateLocate
{
public:
	CPlateLocate();

	//! ���ƶ�λ
	int plateLocate(Mat, vector<Mat>& );

	//! ���Ƶĳߴ���֤
	bool verifySizes(RotatedRect mr);

	//! ���������ʾ
	Mat showResultMat(Mat src, Size rect_size, Point2f center, int index);

	//! �������ȡ����
	inline void setGaussianBlurSize(int param){ m_GaussianBlurSize = param;}
	inline int getGaussianBlurSize() const{ return m_GaussianBlurSize;}

	inline void setMorphSizeWidth(int param){ m_MorphSizeWidth = param;}
	inline int getMorphSizeWidth() const{ return m_MorphSizeWidth;}

	inline void setMorphSizeHeight(int param){ m_MorphSizeHeight = param;}
	inline int getMorphSizeHeight() const{ return m_MorphSizeHeight;}

	inline void setVerifyError(float param){ m_error = param;}
	inline float getVerifyError() const { return m_error;}
	inline void setVerifyAspect(float param){ m_aspect = param;}
	inline float getVerifyAspect() const { return m_aspect;}

	inline void setVerifyMin(int param){ m_verifyMin = param;}
	inline void setVerifyMax(int param){ m_verifyMax = param;}

	inline void setJudgeAngle(int param){ m_angle = param;}

	inline void setDebug(int param){ m_debug = param;}

	//! PlateLocate���ó���
	static const int DEFAULT_GAUSSIANBLUR_SIZE = 5;
	static const int SOBEL_SCALE = 1;
	static const int SOBEL_DELTA = 0;
	static const int SOBEL_DDEPTH = CV_16S;
	static const int SOBEL_X_WEIGHT = 1;
	static const int SOBEL_Y_WEIGHT = 0 ;
	static const int DEFAULT_MORPH_SIZE_WIDTH = 17;
	static const int DEFAULT_MORPH_SIZE_HEIGHT = 3;

	//! showResultMat���ó���
	static const int WIDTH = 136;
	static const int HEIGHT = 36;
	static const int TYPE = CV_8UC3;
	
	//! verifySize���ó���
	static const int DEFAULT_VERIFY_MIN = 3;
	static const int DEFAULT_VERIFY_MAX = 20;

	//! �Ƕ��ж����ó���
	static const int DEFAULT_ANGLE = 30;

	//! �Ƿ�������ģʽ������Ĭ��0�����ر�
	static const int DEFAULT_DEBUG = 0;

protected:
	//! ��˹ģ�����ñ���
	int m_GaussianBlurSize;

	//! ���Ӳ������ñ���
	int m_MorphSizeWidth;
	int m_MorphSizeHeight;

	//! verifySize���ñ���
	float m_error;
	float m_aspect;
	int m_verifyMin;
	int m_verifyMax;

	//! �Ƕ��ж����ñ���
	int m_angle;

	//! �Ƿ�������ģʽ��0�رգ���0����
	int m_debug;
};
