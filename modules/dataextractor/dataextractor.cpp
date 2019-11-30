#include "dataextractor.h"
namespace rtr{

void rtr::DataExtractor::_gateway(cv::Mat& mt){
	if (mt.channels() == 3) cv::cvtColor(mt, mt, cv::COLOR_BGR2GRAY);
}

DataExtractor::DataExtractor(const ImgTemplate* t) noexcept {
	imgparams = *t;
}

void rtr::DataExtractor::_shadow_remover(cv::Mat&){
	return;
}

void DataExtractor::_binarise(cv::Mat& t){
	cv::threshold(t, t, 40, 255, cv::THRESH_BINARY);
}

_corners DataExtractor::_corner_marker_pos_detector(const cv::Mat& g){
	_corners crn;

	cv::Mat dmat = g(cv::Rect2i(cv::Point2i(0,0), cv::Point2i(imgparams.MARKER_WHITESPACE_WIDTH_PIX, imgparams.MARKER_WHITESPACE_HEIGHT_PIX)));
	auto k = _mfinder(dmat);
	cv::circle(dmat, k, 3, cv::Scalar(255));
	cv::imshow("dfd", dmat);

	dmat = g(cv::Rect2i(cv::Point2i(0, g.rows - 1 - imgparams.MARKER_WHITESPACE_HEIGHT_PIX), cv::Point2i(imgparams.MARKER_WHITESPACE_WIDTH_PIX, g.rows-1)));
	k = _mfinder(dmat);
	cv::circle(dmat, k, 3, cv::Scalar(255));
	cv::imshow("dfd1", dmat);

	cv::waitKey();
	return crn;
}



cv::Point2i DataExtractor::_mfinder(const cv::Mat& k) {
	cv::Point2i rpt;

	auto sze = imgparams.MARKER_WIDTH_PIX;
	if (sze % 2 == 0) sze++;
	int bpy = sze / 2;

	int *rmt = new int[((int)(k.rows)) * k.cols];
	for (int i = 0; i < k.rows * k.cols; ++i) rmt[i] = 0;

	int ctrb = 0;
	for (int i = 0; i < sze; ++i) {
		for (int j = 0; j < sze; ++j) {
			if (k.at<uchar>(j, i) == 0) ++ctrb;
		}
	}

	for (int i = sze; i < k.rows;i++) {
		int bpx = sze / 2;
		int ctr = ctrb;
		
		for (int j = sze;j < k.cols; ++j) {
			 
			int bb = 0, be = 0;

			for (int ct_ = i - sze; ct_ < i; ++ct_) {
				if (k.at<uchar>(ct_, j) == 0) ++be;
				if (k.at<uchar>(ct_, j - sze) == 0) ++bb;
			}
			ctr = ctr - bb + be;
			rmt[bpy*k.cols + bpx] = ctr;
			++bpx;
		}

		int yb = 0, ye = 0;

		for (int ct_ = 0; ct_ < sze; ++ct_) {
			if (k.at<uchar>(i-sze, ct_) == 0) ++yb;
			if (k.at<uchar>(i, ct_) == 0) ++ye;
		}
		ctrb = ctrb - yb + ye;
		++bpy;
	}

	int max = 0;
	for (int i = 0; i < k.rows; ++i) {
		for (int j = 0; j < k.cols; ++j) {
			if (rmt[i * k.cols + j] > max) {
				max = rmt[i * k.cols + j];
			}
		}	
	}
	int spx = 0, spy = 0, maxescount = 0;
	for (int i = 0; i < k.rows; ++i) {
		for (int j = 0; j < k.cols; ++j) {
			if (rmt[i * k.cols + j] == max) {
				spx += j;
				spy += i;
				++maxescount;
			}
		}
	}

	rpt.x = spx/maxescount;
	rpt.y = spy/maxescount;
	delete[] rmt;
	return rpt;
}





std::vector<extrdata> rtr::DataExtractor::data_extract(const cv::Mat& t){
	cv::Mat vm = t;

	_gateway(vm); // using gateway to prepare image
	if (imgparams.IMAGE_TYPE != SCANED_IMAGE) _shadow_remover(vm); // if givven image is not scanned, using shadow remover for better quality
	_corner_marker_pos_detector(vm);

	return std::vector<extrdata>();
}



}