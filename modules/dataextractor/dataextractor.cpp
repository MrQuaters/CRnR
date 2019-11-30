#include "dataextractor.h"
namespace rtr{

void rtr::DataExtractor::_gateway(cv::Mat& mt){
	if (mt.channels() == 3) cv::cvtColor(mt, mt, cv::COLOR_BGR2GRAY);
}

void rtr::DataExtractor::_shadow_remover(cv::Mat&){
	return;
}

_corners DataExtractor::_corner_marker_pos_detector(cv::Mat&){
	_corners crn;
}

DataExtractor::DataExtractor(const ImgTemplate& t) noexcept{
	imgparams = t;
}


std::vector<extrdata> rtr::DataExtractor::data_extract(const cv::Mat& t){
	cv::Mat vm = t;

	_gateway(vm); // using gateway to prepare image
	if (imgparams.IMAGE_TYPE != SCANED_IMAGE) _shadow_remover(vm); // if givven image is not scanned, using shadow remover for better quality

	return std::vector<extrdata>();
}

}