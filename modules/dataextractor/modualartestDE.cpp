#include "dataextractor.h"

#ifdef MODULAR_TEST_DATAEXTRACTOR
static int g = 0;
void rtr::DataExtractor::modular_test_callback() {
	cv::imwrite(std::to_string(g++) + ".jpg", modular_test_matrix);
}
#endif