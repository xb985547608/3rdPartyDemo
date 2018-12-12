/*
 * Adjust Selective Colors
 *
 * Author: JoStudio
 */

#ifndef OPENCV2_PS_SELECTIVECOLOR_HPP_
#define OPENCV2_PS_SELECTIVECOLOR_HPP_

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

namespace cv {

typedef enum select_color {
	SELECT_RED,
	SELECT_YELLOW,
	SELECT_GREEN,
	SELECT_CYAN,
	SELECT_BLUE,
	SELECT_MAGENTA,
	SELECT_WHITE,
	SELECT_MIDDLE,
	SELECT_BLACK
}  select_color_t;

/**
 * Class of Adjustment for One Select Color
 */
class SelectiveColorAdjust{
public:
	float cyan;       //��ɫ����ֵ��ȡֵ��Χ�� [-1, 1]
	float magenta;    //ȡֵ��Χ�� [-1, 1]
	float yellow;     //ȡֵ��Χ�� [-1, 1]
	float black;      //ȡֵ��Χ�� [-1, 1]


	bool  defined;

	SelectiveColorAdjust();
	virtual ~SelectiveColorAdjust();
    void reset();
    void calcDefined();
};

/**
 * Class of Selective Color
 */
class SelectiveColor {
public:
	bool isAbsolute;  //�Ƿ���þ��Է���
	SelectiveColorAdjust colors[ SELECT_BLACK + 1 ]; //9�ֿ�ѡ��ɫͨ��

	SelectiveColor();
	virtual ~SelectiveColor();

	int adjust(InputArray src, OutputArray dst); //ʵʩ��ѡ��ɫ����
    void reset();
};

} /* namespace cv */

#endif /* OPENCV2_PS_SELECTIVECOLOR_HPP_ */
