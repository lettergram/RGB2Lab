#include <stdio.h>
#include <iostream>

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>

/* version 2.4 of openCV */
using namespace cv;

/**
 * Takes in a RGB image and outputs
 * a Lab space image.
 **/
Mat BGR2LAB(Mat const &imgRGB){
	Mat imgLab;
	cvtColor(imgRGB, imgLab, CV_RGB2Lab);
	return imgLab;
}

/**
 * Takes in image in the lab space and splits 
 * out the alpha stream. Returning it as a matrix,
 * to be saved out to file or manipulated
 **/
Mat alphaLAB(Mat const &imgLab){

	Mat alphaLab;
	cvtColor(imgLab, alphaLab, CV_Lab2RGB);
	Size s = alphaLab.size();

	int steps = imgLab.step;
	int channels = imgLab.channels();

	for(int y = 0; y < s.height; y++){
		for(int x = 0; x < s.width; x++){
			(*alphaLab.ptr<Point3_<uchar> >(y,x)).x = imgLab.data[steps*y + channels * x + 1];
			(*alphaLab.ptr<Point3_<uchar> >(y,x)).y = imgLab.data[steps*y + channels * x + 1];
			(*alphaLab.ptr<Point3_<uchar> >(y,x)).z = imgLab.data[steps*y + channels * x + 1];
		}
	}
	return alphaLab;
}

/**
 * Takes in image in the lab space and splits 
 * out the beta stream. Returning it as a matrix,
 * to be saved out to file or manipulated
 **/
Mat betaLAB(Mat &imgLab){
	Mat betaLab;
	cvtColor(imgLab, betaLab, CV_Lab2RGB);
	Size s = betaLab.size();
	int steps = imgLab.step;
	int channels = imgLab.channels();
	for(int y = 0; y < s.height; y++){
		for(int x = 0; x < s.width; x++){
			(*betaLab.ptr<Point3_<uchar> >(y,x)).x = imgLab.data[steps*y + channels * x + 2];
			(*betaLab.ptr<Point3_<uchar> >(y,x)).y = imgLab.data[steps*y + channels * x + 2];
			(*betaLab.ptr<Point3_<uchar> >(y,x)).z = imgLab.data[steps*y + channels * x + 2];
		}
	}
	return betaLab;
}

int main(int argc, const char* argv[]){

  Mat imgLab =  BGR2LAB(imread(argv[1], CV_LOAD_IMAGE_COLOR)); 

	char filename[60];

	sprintf(filename, "output/%s-rgb_2_lab.jpg", argv[1]);
  imwrite(filename, imgLab);
	sprintf(filename, "output/%s-alphaLab.jpg", argv[1]);
	imwrite(filename, alphaLAB(imgLab));
	sprintf(filename, "output/%s-betaLab.jpg", argv[1]);
	imwrite(filename, betaLAB(imgLab));

    return 0;
}
