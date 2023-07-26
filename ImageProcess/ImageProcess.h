#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcess.h"

#include "About.h"

#include <QSettings>
#include <QFileDialog>

class ImageProcess : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcess(QWidget *parent = nullptr);
    ~ImageProcess();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void on_openAction_triggered();
    void on_aboutAction_triggered();

public:
    QSettings settings;
    QGraphicsScene* scene;

private:
    QLabel* labelCurFile;
    
private:
    Ui::ImageProcessClass ui;
    About* about;
};
