/*
 * BlackWhite Adjust
 *
 * Author: JoStudio
 */

#ifndef OPENCV2_PS_BLACKWHITE_HPP_
#define OPENCV2_PS_BLACKWHITE_HPP_

#include "opencv2/core.hpp"

namespace cv {

class BlackWhite {
public:
	float 	red;     //��ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]
	float 	yellow;  //��ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]
	float 	green;   //��ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]
	float 	cyan;    //��ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]
	float 	blue;    //��ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]
	float 	magenta; //���ɫ�ĻҶ�ϵ��ֵ��ȡֵ��Χ: [-1.0, 1.0]

	BlackWhite();
	virtual ~BlackWhite();

	int adjust(InputArray src, OutputArray dst);//ʵʩ�ڰ׵���
};

} /* namespace cv */

#endif /* OPENCV2_PS_BLACKWHITE_HPP_ */
