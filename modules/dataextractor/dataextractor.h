#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include "imgtemplate.h"

namespace rtr{

struct _corners {
	cv::Point2i lt, lb, rt, rb; // corner marker positions
};

struct extrdata {
	int dtype;
	std::vector<cv::Mat> imgs;
};


class DataExtractor {
	ImgTemplate imgparams;
	
	void _gateway(cv::Mat&); //takes Mat and convert it to format that DataExtractor takes 
	void _binarise(cv::Mat&); // binarise image set 2 vals 0 and 255 
	void _geom_restore(cv::Mat&); //find geometrical marker and restores true document position
	_corners _corner_marker_pos_detector(const  cv::Mat&); //returning corner markers positions
	cv::Point2i _mfinder(const cv::Mat&, int* ct = nullptr); // function for _corner_marker_pos_detector finding center mass max black pixelex in given mat(optimal alhorithm)
	void _geom_wrap_prespective(cv::Mat&, _corners); // wraping perspective based on finded markers
	void _final_binarisation(cv::Mat&);

public:
	DataExtractor() = delete;
	DataExtractor(DataExtractor&&) = default;
	DataExtractor(DataExtractor&) = default;
	DataExtractor(const ImgTemplate*) noexcept;

	std::vector<extrdata> data_extract(const cv::Mat&);
};

}