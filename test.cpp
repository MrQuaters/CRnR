#include "modules/dataextractor/dataextractor.h"

int main() {
	rtr::TestImgTemplate g;
	rtr::DataExtractor u(&g);
	auto r = cv::imread("imforproc/20190424-112126005-006.jpg");
	u.data_extract(r);

	int a = 0;
	return 0;
}