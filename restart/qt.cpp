#include "qt.h"

using namespace std;
using namespace cv;

qtWindow::qtWindow(QWidget *parent):
    QWidget(parent){

    QWidget *TheWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(TheWidget);
    winDisp = new QLabel(this);
    layout->addWidget(winDisp);
    resize(800, 600);
        

        camera.open(0);
            if (!camera.isOpened()){
        cerr << "does not work be sad" << endl;
    return;
        }

    QTimer *timer = new QTimer(this); 
    connect(timer, QTimer::timeout, this, &qtWindow::distort);
    timer->start(30);
}

qtWindow::~qtWindow(){
    camera.release();
}

void qtWindow::distort(){
    Mat frame;
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
  channels[1] = (channels[1] + satval) *= 5; //oversaturate
  channels[2] = channels[2] / bright; channels[2] = channels[2] * bright; //posterize brightness
merge(channels, hsveffects); //voila
cvtColor(hsveffects, frame, COLOR_HSV2BGR);
cvtColor(frame, frame, COLOR_BGR2RGB);

QImage qImg((const unsigned char*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
winDisp->setPixmap(QPixmap::fromImage(qImg));
}

  //old ycrcb colourspace changing effect, might include later
 //int y; int cr; int cb; //tempvalues b4 gui
 //Mat ycrcb;
 //cvtColor(frame, ycrcb, COLOR_BGR2YCrCb);
 //vector<Mat> channels;
  //split(ycrcb, channels); //oh no they are all apart
  //channels[0] += y;
  //channels[1] += cr;
  //channels[2] += cb;
  //merge(channels, ycrcb); //the channels are all 2gether now ♥