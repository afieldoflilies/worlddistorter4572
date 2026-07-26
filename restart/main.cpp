#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/videoio.hpp>

//redundant i know
using namespace cv;
using namespace std;



int main() {
//capture webcam frames
  VideoCapture camera(0);
  if (!camera.isOpened()){
    cerr << "does not work be sad" << endl;
    return 1;
  }
  namedWindow("Camera", WINDOW_AUTOSIZE); 
  Mat frame;

  while (1) {
    camera >> frame;

  //noise effect
 int InpArry = 0; int OutpArry; 
 int thresh; int maxval; 
 Mat noisemaker;
 Mat uniform = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
 randu(uniform, 0 + InpArry, 255 + OutpArry);
 threshold(uniform, noisemaker, 250 + thresh, 255 + maxval, THRESH_BINARY);

  //image sharpen effect
 Mat sharpener;
 Mat kernel = (Mat_<double>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
 filter2D(frame, sharpener, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT);
 
 frame.setTo(Scalar(255, 255, 255), noisemaker);

 //more effects
 int hueval = 0; int hue = 30 + hueval;
 int brightval = 0; int bright = 64 + brightval;
 int satval = 0;
 Mat hsveffects;
 cvtColor(frame, hsveffects, COLOR_BGR2HSV);
 vector<Mat> channels;
 split(hsveffects, channels);
  channels[0] = channels[0] / hue; channels[0] = channels[0] * hue; //posterize hues
  channels[1] + channels[1] + satval *= 5; //oversaturate
  channels[2] = channels[2] / bright; channels[2] = channels[2] * bright; //posterize brightness
merge(channels, hsveffects); //voila
cvtColor(hsveffects, frame, COLOR_HSV2BGR);

  //old ycrcb colourspace changing effect
 //int y; int cr; int cb; //tempvalues b4 gui
 //Mat ycrcb;
 //cvtColor(frame, ycrcb, COLOR_BGR2YCrCb);
 //vector<Mat> channels;
  //split(ycrcb, channels); //oh no they are all apart
  //channels[0] += y;
  //channels[1] += cr;
  //channels[2] += cb;
  //merge(channels, ycrcb); //the channels are all 2gether now ♥
 
 imshow("Camera", frame); //lets see the final product

  if (waitKey(30) == 27) //esc key to exit
    break;
  }

return 0;
}
//67
//the 67 wards away my past compilation errors