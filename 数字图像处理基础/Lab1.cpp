/**
 * @brief : 数字图像处理基础第一次实验
 * @date  : 2023.10.13
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

/**
 * @brief 绘制直方图
 * @param 原始图像(灰度)
 */
void drawHistogram(cv::Mat& img) {
    //获取图像直方图
	int histsize = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
    cv::Mat hist; // 直方图
	cv::calcHist(&img, 1, 0, cv::Mat(), hist, 1, &histsize, &histRanges, true, false); // 计算直方图函数
	//创建直方图显示图像
	int hist_h = 300;//直方图的图像的高
	int hist_w = 512; //直方图的图像的宽
	int bin_w = hist_w / histsize;//直方图的等级
	cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));//绘制直方图显示的图像
	//绘制并显示直方图
	normalize(hist, hist, 0, hist_h, cv::NORM_MINMAX, -1, cv::Mat()); // 归一化直方图
	for (int i = 1; i < histsize; i ++) {
		line(histImage, cv::Point((i - 1) * bin_w, hist_h - cvRound(hist.at<float>(i - 1))),
			cv::Point((i)*bin_w, hist_h - cvRound(hist.at<float>(i))), cv::Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("histImage", histImage);
	cv::waitKey(0);  //暂停，保持图像显示，等待按键结束
}

/**
 * @brief 直方图均衡化(自己编写版)
 * @param 原始图像(灰度)
 */
void performHistogramEqualization(cv::Mat& img) {
    // 计算直方图
    int hist[256] = {0};
    int cdf[256] = {0};
    int totalPixels = img.rows * img.cols;
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            hist[img.at<uchar>(i, j)]++;
        }
    }
    cdf[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }
    cv::Mat equalizedImage = img.clone();
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            equalizedImage.at<uchar>(i, j) = (uchar)((cdf[img.at<uchar>(i, j)] * 255) / totalPixels);
        }
    }
    img = equalizedImage;
}


/**
 * @brief 直方图均衡化(OpenCV自带函数)
 * @param 原始图像(灰读/彩色)
 */
void performColorHistogramEqualization(cv::Mat& img) {
    if (img.channels() == 1) {
        // 如果是单通道图像（灰度图像），则直接进行直方图均衡化
        cv::equalizeHist(img, img);
    } else if (img.channels() == 3) {
        // 如果是三通道图像（彩色图像），则分别对每个通道进行直方图均衡化
        cv::Mat channels[3];
        cv::split(img, channels); // 分离通道
        for (int i = 0; i < 3; i++) {
            cv::equalizeHist(channels[i], channels[i]); // 对每个通道进行直方图均衡化
        }
        cv::merge(channels, 3, img); // 合并通道
    }
}


/**
 * @brief 添加椒盐噪声
 * @param img: 原始噪音图像
 * @param cnt: 椒盐数量
 */
void AddSaltPepperNoisy(cv::Mat& img, int cnt = 2000) {
    // salt
    for(int k = 0; k < cnt; k ++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;
 
		if(img.channels() == 1) {
			img.at<uchar>(j, i) = 255;
		}
		else if(img.channels() == 3) {
			img.at<cv::Vec3b>(j,i)[0] = 255;
			img.at<cv::Vec3b>(j,i)[1] = 255;
			img.at<cv::Vec3b>(j,i)[2] = 255;
		}
	}
    // pepper
    for(int k = 0; k < cnt; k ++) {
		int i = rand() % img.cols;
		int j = rand() % img.rows;
		if(img.channels() == 1) {
			img.at<uchar>(j,i) = 0;
		}
		else if(img.channels() == 3) {
			img.at<cv::Vec3b>(j,i)[0] = 0;
			img.at<cv::Vec3b>(j,i)[1] = 0;
			img.at<cv::Vec3b>(j,i)[2] = 0;
		}
	}
}

/**
 * @brief 添加高斯噪声
 * @param img: 原始图像
 * @param noiseimg: 得到的噪声图像
 */
void AddGaussianNoisy(cv::Mat& img, cv::Mat& noiseimg) {
    cv::Mat noise = cv::Mat::zeros(img.size(), img.type());
    randn(noise, 1, 15); // randn(a,b,c)产生高斯噪声，其中a为输出矩阵，b为均值，c为方差
    noiseimg = cv::Mat::zeros(img.size(), img.type());
    add(img, noise, noiseimg, cv::Mat(), -1); // 将灰度图与噪声矩阵相加得到噪声图像
}

/**
 * @brief 均值滤波
 * @param wsize: 滤波器大小
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void ArithmeticMeanFilter(cv::Size wsize, cv::Mat& img_input, cv::Mat& img_output) {
	//判断矩阵的行列数为奇数
	if (wsize.height % 2 == 0 || wsize.width % 2 == 0) {
		fprintf(stderr, "Please enter odd size!");
		exit(-1);
	}
	int hh = (wsize.height - 1) / 2;
	int hw = (wsize.width - 1) / 2;
	cv::Mat Newsrc;
	copyMakeBorder(img_input, Newsrc, hh, hh, hw, hw, cv::BORDER_REFLECT_101); // 以边缘为轴
	img_output = cv::Mat::zeros(img_input.size(), img_input.type());
	// 三通道彩色图片处理
	if (Newsrc.channels() == 3) {
		// 定义每个通道的核的总数和平均值
		int sumR = 0, sumG = 0, sumB = 0;
		int averageR = 0, averageG = 0, averageB = 0;
		for (int i = hh; i < img_input.rows + hh; i ++) {
			for (int j = hw; j < img_input.cols + hw; j ++) {
				for (int r = i - hh; r <= i + hh; r ++) {
					cv::Vec3b* data_New = Newsrc.ptr<cv::Vec3b>(r);
					// 求核的总数
					for (int k = j - hh; k <= j + hh; k ++) {
						sumR += data_New[k][0];
						sumG += data_New[k][1];
						sumB += data_New[k][2];
					}
				}
				// 求平均数
				averageR = sumR / (wsize.area());
				averageG = sumG / (wsize.area());
				averageB = sumB / (wsize.area());
				// 写入目标图像
				cv::Vec3b* dataDst = img_output.ptr<cv::Vec3b>(i - hh);
				dataDst[j - hw][0] = averageR;
				dataDst[j - hw][1] = averageG;
				dataDst[j - hw][2] = averageB;
				sumR = 0; sumG = 0; sumB = 0;
				averageR = 0; averageG = 0; averageB = 0;
			}
        }
	}
	// 单通道图片处理
	else if (Newsrc.channels() == 1) {
		int sum = 0, average = 0;
		for (int i = hh; i < img_input.rows + hh; i ++) {
			for (int j = hw; j < img_input.cols + hw; j ++) {
				for (int r = i - hh; r <= i + hh; r ++) {
					uchar* data = Newsrc.ptr<uchar>(r);
					for (int k = j - hh; k <= j + hh; k ++) {
						sum += data[k];
					}
				}
				average = sum / (wsize.area());
				uchar* data_dst = img_output.ptr<uchar>(i - hh);
				data_dst[j - hw] = average;
				sum = 0, average = 0;
			}
		}
	}
}

/**
 * @brief 中值滤波
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 * @param kernelSize: 滤波器大小
 */
void MedianFilter(cv::Mat& img_input, cv::Mat& img_output, int kernelSize) {
    CV_Assert(img_input.channels() == 3);  // 确保图像有3个通道
    img_output = img_input.clone();
    int pad = kernelSize / 2;

    for(int i = 0; i < img_input.rows; ++i) {
        for(int j = 0; j < img_input.cols; ++j) {
            std::vector<int> neighborhoodR, neighborhoodG, neighborhoodB;

            for(int m = -pad; m <= pad; ++m) {
                for(int n = -pad; n <= pad; ++n) {
                    int x = std::max(0, std::min(img_input.rows - 1, i + m));
                    int y = std::max(0, std::min(img_input.cols - 1, j + n));
                    cv::Vec3b color = img_input.at<cv::Vec3b>(x, y);
                    neighborhoodR.push_back(color[0]);
                    neighborhoodG.push_back(color[1]);
                    neighborhoodB.push_back(color[2]);
                }
            }

            std::nth_element(neighborhoodR.begin(), neighborhoodR.begin() + neighborhoodR.size()/2, neighborhoodR.end());
            std::nth_element(neighborhoodG.begin(), neighborhoodG.begin() + neighborhoodG.size()/2, neighborhoodG.end());
            std::nth_element(neighborhoodB.begin(), neighborhoodB.begin() + neighborhoodB.size()/2, neighborhoodB.end());

            img_output.at<cv::Vec3b>(i, j) = cv::Vec3b(neighborhoodR[neighborhoodR.size()/2], neighborhoodG[neighborhoodG.size()/2], neighborhoodB[neighborhoodB.size()/2]);
        }
    }

}

/**
 * @brief 高斯滤波
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 * @param kernelSize: 滤波器大小
 * @param sigma: 高斯滤波器的标准差
 */
// 创建高斯核
cv::Mat createGaussianKernel(int kernelSize, double sigma) {
    cv::Mat kernel(kernelSize, kernelSize, CV_64F);
    double mean = kernelSize / 2;
    double sum = 0.0; // For accumulating the kernel values

    for (int x = 0; x < kernelSize; ++x)
        for (int y = 0; y < kernelSize; ++y) {
            kernel.at<double>(x, y) = std::exp(-0.5 * (std::pow((x - mean) / sigma, 2.0) + std::pow((y - mean) / sigma, 2.0)))
                                      / (2 * M_PI * sigma * sigma);

            // Accumulate the kernel values
            sum += kernel.at<double>(x, y);
        }

    // Normalize the kernel
    for (int x = 0; x < kernelSize; ++x)
        for (int y = 0; y < kernelSize; ++y)
            kernel.at<double>(x, y) /= sum;

    return kernel;
}
// 高斯滤波
void gaussianFilter(cv::Mat& img_input, cv::Mat& img_output, int kernelSize, double sigma) {
    CV_Assert(img_input.channels() == 3);  // 确保图像有3个通道
    img_output = img_input.clone();
    cv::Mat kernel = createGaussianKernel(kernelSize, sigma);
    int pad = kernelSize / 2;

    for(int i = 0; i < img_input.rows; ++i) {
        for(int j = 0; j < img_input.cols; ++j) {
            double sumR = 0, sumG = 0, sumB = 0;

            for(int m = -pad; m <= pad; ++m) {
                for(int n = -pad; n <= pad; ++n) {
                    int x = std::max(0, std::min(img_input.rows - 1, i + m));
                    int y = std::max(0, std::min(img_input.cols - 1, j + n));
                    cv::Vec3b color = img_input.at<cv::Vec3b>(x, y);
                    double w = kernel.at<double>(m + pad, n + pad);
                    sumR += color[0] * w;
                    sumG += color[1] * w;
                    sumB += color[2] * w;
                }
            }

            img_output.at<cv::Vec3b>(i, j) = cv::Vec3b(cv::saturate_cast<uchar>(sumR), cv::saturate_cast<uchar>(sumG), cv::saturate_cast<uchar>(sumB));
        }
    }
}


/* 边缘增强和锐化 */
/**
 * @brief 边缘增强
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void sharpenImage(const cv::Mat& img_input, cv::Mat& img_output) {
    // Create the sharpening kernel
    cv::Mat kernel = (cv::Mat_<float>(3,3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);

    // Apply the kernel to the image
    cv::filter2D(img_input, img_output, img_input.depth(), kernel);
}

/**
 * @brief 锐化(Roberts算子)
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void enhanceEdges_Roberts(const cv::Mat& img_input, cv::Mat& img_output) {
    // Define the Sobel operator kernels
    cv::Mat sobel_x = (cv::Mat_<float>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::Mat sobel_y = (cv::Mat_<float>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    // Apply the Sobel operators
    cv::Mat sobel_x_dst, sobel_y_dst;
    cv::filter2D(img_input, sobel_x_dst, img_input.depth(), sobel_x);
    cv::filter2D(img_input, sobel_y_dst, img_input.depth(), sobel_y);

    // Combine the results
    img_output = sobel_x_dst + sobel_y_dst;
}

/**
 * @brief 锐化(Laplace算子)
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void enhanceEdges_Laplace(const cv::Mat& img_input, cv::Mat& img_output) {
cv::Mat kernel = (cv::Mat_<float>(3,3) << 0, -1, 0, -1, 4, -1, 0, -1, 0);

    // Create a new image to store the result
    img_output = cv::Mat::zeros(img_input.size(), img_input.type());

    // Apply the Laplace operator
    for (int y = 1; y < img_input.rows - 1; y++) {
        for (int x = 1; x < img_input.cols - 1; x++) {
            for (int c = 0; c < img_input.channels(); c++) {
                float sum = 0.0;

                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        int pixel = img_input.at<cv::Vec3b>(y + ky, x + kx)[c];
                        float coeff = kernel.at<float>(ky + 1, kx + 1);

                        sum += pixel * coeff;
                    }
                }

                img_output.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum);
            }
        }
    }

}

/**
 * @brief 锐化(Sobel算子)
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void enhanceEdges_Sobel(const cv::Mat& img_input, cv::Mat& img_output) {
    // Define the Sobel kernels
    cv::Mat kernel_x = (cv::Mat_<float>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
    cv::Mat kernel_y = (cv::Mat_<float>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

    // Create new images to store the result
    cv::Mat result_x = cv::Mat::zeros(img_input.size(), img_input.type());
    cv::Mat result_y = cv::Mat::zeros(img_input.size(), img_input.type());

    // Apply the Sobel operator
    for (int y = 1; y < img_input.rows - 1; y++) {
        for (int x = 1; x < img_input.cols - 1; x++) {
            for (int c = 0; c < img_input.channels(); c++) {
                float sum_x = 0.0;
                float sum_y = 0.0;

                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        int pixel = img_input.at<cv::Vec3b>(y + ky, x + kx)[c];
                        float coeff_x = kernel_x.at<float>(ky + 1, kx + 1);
                        float coeff_y = kernel_y.at<float>(ky + 1, kx + 1);

                        sum_x += pixel * coeff_x;
                        sum_y += pixel * coeff_y;
                    }
                }

                result_x.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum_x);
                result_y.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum_y);
            }
        }
    }
    // Combine gradients
    cv::addWeighted(result_x, 0.5, result_y, 0.5, 0, img_output);
}

/**
 * @brief 锐化(Priwitt算子)
 * @param img_input: 原始图像
 * @param img_output: 得到过滤后的图像
 */
void enhanceEdges_Priwitt(const cv::Mat& img_input, cv::Mat& img_output) {
    // Define the Prewitt kernels
    cv::Mat kernel_x = (cv::Mat_<float>(3,3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
    cv::Mat kernel_y = (cv::Mat_<float>(3,3) << -1, -1, -1, 0, 0, 0, 1, 1, 1);

    // Create new images to store the result
    cv::Mat result_x = cv::Mat::zeros(img_input.size(), img_input.type());
    cv::Mat result_y = cv::Mat::zeros(img_input.size(), img_input.type());

    // Apply the Prewitt operator
    for (int y = 1; y < img_input.rows - 1; y++) {
        for (int x = 1; x < img_input.cols - 1; x++) {
            for (int c = 0; c < img_input.channels(); c++) {
                float sum_x = 0.0;
                float sum_y = 0.0;

                for (int ky = -1; ky <= 1; ky++) {
                    for (int kx = -1; kx <= 1; kx++) {
                        int pixel = img_input.at<cv::Vec3b>(y + ky, x + kx)[c];
                        float coeff_x = kernel_x.at<float>(ky + 1, kx + 1);
                        float coeff_y = kernel_y.at<float>(ky + 1, kx + 1);

                        sum_x += pixel * coeff_x;
                        sum_y += pixel * coeff_y;
                    }
                }

                result_x.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum_x);
                result_y.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(sum_y);
            }
        }
    }
    // Combine gradients
    cv::addWeighted(result_x, 0.5, result_y, 0.5, 0, img_output);
}

int main() {
    // 读入彩色图像
    cv::Mat colorImage = cv::imread("cat.png");
    if (colorImage.empty()) {
        std::cout << "无法读取图像." << std::endl;
        return -1;
    }
    // 显示原始图像
    imshow("Color Image", colorImage);
    // 将彩色图像转换为灰度图像
    cv::Mat grayImage;
    cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
    // 显示灰度图像
    imshow("Gray Image", grayImage);
    // 绘制直方图
    drawHistogram(grayImage);
    // 进行均衡化
    performHistogramEqualization(grayImage);
    // 显示均衡化后的图像
    imshow("Equalized Image", grayImage);
    // 绘制均衡化后的直方图
    drawHistogram(grayImage);
    cv::waitKey(0);
    // 将彩色图像均衡化
    // 显示原始彩色图像
    imshow("Color Image", colorImage);
    performColorHistogramEqualization(colorImage); // 彩色图像均衡化
    // 显示均衡化后的彩色图像
    imshow("Equalized Image", colorImage);
    /*----------------------------------*/
    /* 添加噪声 */
    cv::Mat noiseImage = colorImage.clone(); // 这里在彩色图像里添加
    // 添加高斯噪声
    AddGaussianNoisy(colorImage, noiseImage);
    imshow("Noisy Image (Gaussian)", noiseImage);
    // 添加椒盐噪声
    AddSaltPepperNoisy(noiseImage, 1000);
    imshow("Noisy Image (Salt and Pepper)", noiseImage);
    cv::waitKey(0);

    /* 滤波 */
    // 均值滤波
    cv::Mat filterImage1, filterImage2;
    // 自己编写的均值滤波
    ArithmeticMeanFilter(cv::Size(7, 7), noiseImage, filterImage1);
    imshow("filterImage(7x7)", filterImage1);
    // ArithmeticMeanFilter(cv::Size(5, 5), noiseImage, filterImage1);
    // imshow("filterImage(5x5)", filterImage1);
    // opencv 自带均值滤波
	// blur(noiseImage, filterImage2, cv::Size(7, 7));
    // imshow("filterImage(opencv)", filterImage2);

    // 中值滤波
    cv::Mat MedianFilterImage, medianBlurImage;
    // 自己编写的中值滤波
    MedianFilter(noiseImage, MedianFilterImage, 7);
	imshow("MedianFilter(7x7)", MedianFilterImage);
    // MedianFilter(noiseImage, MedianFilterImage, 5);
	// imshow("MedianFilter(5x5)", MedianFilterImage);
	// opencv 自带中值滤波
	// cv::medianBlur(noiseImage, medianBlurImage, 7);
	// imshow("medianBlur", medianBlurImage);

    // 高斯滤波
    cv::Mat GaussImage1, GaussImage2;
    // 自己编写的高斯滤波
    gaussianFilter(noiseImage, GaussImage1, 7, 1.2);
    imshow("GaussImage(7x7)", GaussImage1);
    // gaussianFilter(noiseImage, GaussImage1, 5, 1.2);
    // imshow("GaussImage1(5x5)", GaussImage1);
    // opencv 自带的高斯滤波
    // cv::GaussianBlur(noiseImage, GaussImage2, cv::Size(5, 5), 0);
    // imshow("GaussImage2", GaussImage2);

    cv::waitKey(0);

    /* 
     * 读入另外一副图像，对其采取不同的 roberts/laplace/sobel/priwitt 边缘锐化算子进行边缘增强和锐化
     */
    // 读入新的图像
    cv::Mat girlImage = cv::imread("girl.png");
    if (girlImage.empty()) {
        std::cout << "无法读取图像(2)." << std::endl;
        return -1;
    }
    // 显示原始图像
    imshow("Girl Image", girlImage);
    // 对原始图像加入噪声
    cv::Mat GirlNoiseImage = girlImage.clone();
    // 添加椒盐噪声
    AddSaltPepperNoisy(GirlNoiseImage, 200);
    imshow("GirlNoiseImage", GirlNoiseImage);
    cv::waitKey(0);
    /* 增强和锐化 */
    // 原始图像
    cv::Mat sharpened, enhanced1, enhanced2, enhanced3, enhanced4;
    sharpenImage(girlImage, sharpened);
    enhanceEdges_Roberts(girlImage, enhanced1);
    enhanceEdges_Laplace(girlImage, enhanced2);
    enhanceEdges_Sobel(girlImage, enhanced3);
    enhanceEdges_Priwitt(girlImage, enhanced4);
    imshow("sharpened1", sharpened);
    imshow("enhanced(Roberts)", enhanced1);
    imshow("enhanced(Laplace)", enhanced2);
    imshow("enhanced(Sobel)", enhanced3);
    imshow("enhanced(Priwitt)", enhanced4);
    cv::waitKey(0);
    // 噪声图像
    sharpenImage(GirlNoiseImage, sharpened);
    enhanceEdges_Roberts(GirlNoiseImage, enhanced1);
    enhanceEdges_Laplace(GirlNoiseImage, enhanced2);
    enhanceEdges_Sobel(GirlNoiseImage, enhanced3);
    enhanceEdges_Priwitt(GirlNoiseImage, enhanced4);
    imshow("sharpened(noise)", sharpened);
    imshow("enhanced(Roberts)(noise)", enhanced1);
    imshow("enhanced(Laplace)(noise)", enhanced2);
    imshow("enhanced(Sobel)(noise)", enhanced3);
    imshow("enhanced(Priwitt)(noise)", enhanced4);
    cv::waitKey(0);
    return 0;
}