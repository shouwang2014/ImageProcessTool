#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"

#include "About.h"

#include <QSettings>
#include <QFileDialog>

#include "opencv2/opencv.hpp"

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void updateGraphicView(QGraphicsScene* scene, QGraphicsView* viewer);

private slots:
    void on_openAction_triggered();
    void on_aboutAction_triggered();

    void on_linearTranAction_triggered();
    void on_gammaTranAction_triggered();
    void on_logTranAction_triggered();

public:
    QSettings settings;
    QGraphicsScene* scene;

    cv::Mat _img;

private:
    QLabel* labelCurFile;
    
private:
    Ui::ImageProcessClass ui;
    About* about;
};
