#pragma once

#include <iostream> 
#include <QApplication>
#include <QGroupBox>
#include <QSlider>
#include <QTimer>
#include <QLabel>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <opencv2/opencv.hpp>

class qtWindow: public QWidget
{
    Q_OBJECT

public:
    explicit qtWindow(QWidget *parent = nullptr);
    ~qtWindow();

private slots:
    void distort(); //effects function
    //slider functions for tweaking //im gonna tweak
        //colourspace slider functions
    void satSliderMoved(int satval);
    void satMultSliderMoved(int satmult);
    void brightSliderMoved(int bright);
    void hueSliderMoved(int hue);
        //noise slider functions
    void noiseInpSliderMoved(int inputArray);
    void noiseOutSliderMoved(int outputArray);
    void noiseThreshSliderMoved(int thresh);
    void noiseMaxValSliderMoved(int maxval);
private:
//colourspace sliders
    QSlider *satSlider;
    int global_satval = 0;
    QSlider *satMultSlider;
    int global_satmult = 5;
    QSlider *brightSlider;
    int global_bright = 64;
    QSlider *hueSlider;
    int global_hue = 30;
//noise effect sliders
    QSlider *noiseInpSlider;
    int global_inputArray = 0;
    QSlider *noiseOutSlider;
    int global_outputArray = 255;
    QSlider *noiseThreshSlider;
    int global_thresh = 250;
    QSlider *noiseMaxValSlider;
    int global_maxval = 255;
    QLabel *winDisp;
    cv::VideoCapture camera;
};
