#pragma once

#include <iostream> 
#include <QApplication>
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

private slots:
    void distort();

private:
    QLabel *winDisp;
    cv::VideoCapture camera;
};
