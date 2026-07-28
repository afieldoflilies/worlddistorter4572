#include "qt.h"

using namespace std;
using namespace cv;

qtWindow::qtWindow(QWidget *parent):
    QWidget(parent){
    
    QWidget *TheWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(TheWidget);
    winDisp = new QLabel(this);
    winDisp->setWindowTitle(QApplication::translate("WorldDistorter", "World Distorter"));
    winDisp->setMinimumSize(640, 480);
    winDisp->setScaledContents(true);
    winDisp->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    layout->addWidget(winDisp);
    resize(1280, 600);

    //sliders mmm yummy
        //colourspace sliders
    QSlider *satSlider = new QSlider(Qt::Horizontal, this);
        satSlider->setRange(-255, 255);
        satSlider->setValue(0);
        connect(satSlider, &QSlider::valueChanged, this, &qtWindow::satSliderMoved);
        layout->addWidget(satSlider);
    QSlider *satMultSlider = new QSlider(Qt::Horizontal, this);
        satMultSlider->setRange(-10, 15);
        satMultSlider->setValue(5);
        connect(satMultSlider, &QSlider::valueChanged, this, &qtWindow::satMultSliderMoved);
        layout->addWidget(satMultSlider);
    QSlider *brightSlider = new QSlider(Qt::Horizontal, this);
        brightSlider->setRange(-255, 255);
        brightSlider->setValue(64);
        connect(brightSlider, &QSlider::valueChanged, this, &qtWindow::brightSliderMoved);
        layout->addWidget(brightSlider);
    QSlider *hueSlider = new QSlider(Qt::Horizontal, this);
        hueSlider->setRange(-255, 255);
        hueSlider->setValue(30);
        connect(hueSlider, &QSlider::valueChanged, this, &qtWindow::hueSliderMoved);
        layout->addWidget(hueSlider);
        //noise effect sliders
    QSlider *noiseInpSlider = new QSlider(Qt::Horizontal, this);
        noiseInpSlider->setRange(-10, 255);
        noiseInpSlider->setValue(0);
        connect(noiseInpSlider, &QSlider::valueChanged, this, &qtWindow::noiseInpSliderMoved);
        layout->addWidget(noiseInpSlider);
    QSlider *noiseOutSlider = new QSlider(Qt::Horizontal, this);
        noiseOutSlider->setRange(0, 255);
        noiseOutSlider->setValue(255);
        connect(noiseOutSlider, &QSlider::valueChanged, this, &qtWindow::noiseOutSliderMoved);
        layout->addWidget(noiseOutSlider);
    QSlider *noiseThreshSlider = new QSlider(Qt::Horizontal, this);
        noiseThreshSlider->setRange(0, 255);
        noiseThreshSlider->setValue(250);
        connect(noiseThreshSlider, &QSlider::valueChanged, this, &qtWindow::noiseThreshSliderMoved);
        layout->addWidget(noiseThreshSlider);
    QSlider *noiseMaxValSlider = new QSlider(Qt::Horizontal, this);
        noiseMaxValSlider->setRange(0, 255);
        noiseMaxValSlider->setValue(255);
        connect(noiseMaxValSlider, &QSlider::valueChanged, this, &qtWindow::noiseMaxValSliderMoved);
        layout->addWidget(noiseMaxValSlider);

        //fix for uh something i dont really remember
        qputenv("OPENCV_VIDEOIO_PRIORITY_GSTREAMER", "0"); 

        camera.open(0, cv::CAP_DSHOW);
            if (!camera.isOpened()){
        cerr << "does not work be sad" << endl;
    return;
        }
        //screw this tiny image
    camera.set(CAP_PROP_FRAME_WIDTH, 1280); 
    camera.set(CAP_PROP_FRAME_HEIGHT, 720);

    QTimer *timer = new QTimer(this); 
    connect(timer, QTimer::timeout, this, &qtWindow::distort);
    timer->start(30);
}

qtWindow::~qtWindow(){
    camera.release();
}

//slider functions,i think im gonna make sliders when im done these
    //colourspace slider functions
void qtWindow::satSliderMoved(int satval){
    global_satval = satval;
}
void qtWindow::satMultSliderMoved(int satmult){
    global_satmult = satmult;
}
void qtWindow::brightSliderMoved(int bright){
    global_bright = bright;
}
void qtWindow::hueSliderMoved(int hue){
    global_hue = hue;
}
    //noise effect slider functions
void qtWindow::noiseInpSliderMoved(int inputArray){
    global_inputArray = inputArray;
}
void qtWindow::noiseOutSliderMoved(int outputArray){
    global_outputArray = outputArray;
}
void qtWindow::noiseThreshSliderMoved(int thresh){
    global_thresh = thresh;
}
void qtWindow::noiseMaxValSliderMoved(int maxval){
    global_maxval = maxval;
}

void qtWindow::distort(){
    Mat frame;
    camera >> frame;

  //noise effect
 Mat noisemaker;
 Mat uniform = Mat::zeros(frame.rows, frame.cols, CV_8UC1);
 randu(uniform, global_inputArray, global_outputArray);
 threshold(uniform, noisemaker, global_thresh, global_maxval, THRESH_BINARY);

  //image sharpen effect
 Mat sharpener;
 Mat kernel = (Mat_<double>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
 filter2D(frame, sharpener, -1, kernel, Point(-1,-1), 0, BORDER_DEFAULT);
 
 frame.setTo(Scalar(255, 255, 255), noisemaker);

 //more effects, colorspace value changes
 Mat hsveffects;
 cvtColor(frame, hsveffects, COLOR_BGR2HSV);
 vector<Mat> channels;
 split(hsveffects, channels);
  channels[0] = channels[0] / global_hue; channels[0] = channels[0] * global_hue; //posterize hues
  channels[1] = (channels[1] + global_satval) *= global_satmult; //oversaturate
  channels[2] = channels[2] / global_bright; channels[2] = channels[2] * global_bright; //posterize brightness
merge(channels, hsveffects); //voila
cvtColor(hsveffects, frame, COLOR_HSV2BGR); //are tehse cvtColors redundant? i dont know but im keeping it
cvtColor(frame, frame, COLOR_BGR2RGB);

QImage qImg((const unsigned char*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
winDisp->setPixmap(QPixmap::fromImage(qImg)); //convert so qt can display
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