#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <vector>
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
	void _shadow_remover(cv::Mat&); //takes Mat with shadows and trying to remove it
	_corners _corner_marker_pos_detector(cv::Mat&); //returning corner markers positions

public:
	DataExtractor() = delete;
	DataExtractor(DataExtractor&&) = default;
	DataExtractor(DataExtractor&) = default;
	DataExtractor(const ImgTemplate&) noexcept;

	std::vector<extrdata> data_extract(const cv::Mat&);
};

}