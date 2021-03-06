// F135.hpp

#ifndef _F135_h_
#define _F135_h_

#include "EyeF/_EyeF.hpp"
#include "_opencv2.hpp"

namespace f135 {
	const int l_x = 1280;
	const int l_y =  960;
	const int l = l_x*l_y;

	const int m_x = 1136;
	const int m_y =  640;
	const int m = m_x*m_y;

	const int n_x =  640;
	const int n_y =  640;
	const int n = n_x*n_y;

	const float u = _dr * 135;
	const float v = _dr * 120;
	const float w = _dr *  60;

	const int view_count = 7;
	const float view_x[view_count] = {
		-w/2 * 3,
		-w/2 * 2,
		-w/2,
		0,
		+w/2,
		+w/2 * 2,
		+w/2 * 3,
	};
	const float view_y[view_count] = {
		-w / 2 * 3,
		-w / 2 * 2,
		-w / 2,
		0,
		+w / 2,
		+w / 2 * 2,
		+w / 2 * 3,
	};

	extern Fisheye fisheye_a;
	extern Fisheye fisheye_f;
	extern Fisheye fisheye_g;
	extern Fisheye fisheye_h[view_count][view_count];
}

bool F135_init()
;
bool F135_fg(cv::Mat& f, cv::Mat& g, Fisheye& fisheye_f = f135::fisheye_f, Fisheye& fisheye_g = f135::fisheye_g)
;
bool F135_fh(cv::Mat& f, cv::Mat& h, Fisheye& fisheye_f = f135::fisheye_f, Fisheye& fisheye_h = f135::fisheye_h[3][3])
;
bool F135_fa(cv::Mat& f, cv::Mat& a, Fisheye& fisheye_f = f135::fisheye_f, Fisheye& fisheye_a = f135::fisheye_a)
;
bool F135_ag(cv::Mat& a, cv::Mat& g, Fisheye& fisheye_a = f135::fisheye_a, Fisheye& fisheye_g = f135::fisheye_g)
;
bool F135_ah(cv::Mat& a, cv::Mat& h, Fisheye& fisheye_a = f135::fisheye_a, Fisheye& fisheye_h = f135::fisheye_h[3][3])
;

#endif // !_F135_h_
