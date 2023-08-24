#include "ImageProcess.h"
#include <QDir>
#include <QGraphicsItem>
#include "ImageProcessCore.h"

ImageProcess::ImageProcess(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);

    scene = new QGraphicsScene();
    about = new About();

    labelCurFile = new QLabel();
    labelCurFile->setMinimumWidth(150);
    labelCurFile->setText("当前文件: ");
    ui.statusBar->addWidget(labelCurFile);
}

ImageProcess::~ImageProcess()
{
    delete scene;
    delete about;
}

void ImageProcess::resizeEvent(QResizeEvent * event)
{
    QRectF boundRect = scene->sceneRect();
    ui.ImageGraphView->fitInView(boundRect, Qt::KeepAspectRatio);
}

void ImageProcess::updateGraphicView(QGraphicsScene* scene, QGraphicsView* viewer)
{
    if (!_img.empty())
    {
        QImage qImg;
        if (1 == _img.channels())
        {
            qImg = QImage(_img.data, _img.cols, _img.rows, _img.step, QImage::Format_Grayscale8);
        }
        else if (3 == _img.channels())
        {
            qImg = QImage(_img.data, _img.cols, _img.rows, _img.step, QImage::Format_BGR888);
        }

        QPixmap pImg = QPixmap::fromImage(qImg);

        if (!pImg.isNull())
        {
            scene->clear();

            //创建QGraphicsPixmapItem对象,并添加到场景中
            QGraphicsPixmapItem* item = scene->addPixmap(pImg);

            //更新scene的sceneRect
            QRectF itemBoundRect = item->boundingRect();
            scene->setSceneRect(itemBoundRect);

            //将场景设置为视图的场景
            viewer->setScene(scene);

            QRectF boundRect = scene->sceneRect();
            ui.ImageGraphView->fitInView(boundRect, Qt::KeepAspectRatio);

            //设置视图属性
            viewer->setRenderHint(QPainter::Antialiasing); //抗锯齿
            viewer->setDragMode(QGraphicsView::ScrollHandDrag); //拖拽模式
            viewer->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //视口更新模式
            
            viewer->show();
        }
    }
}

void ImageProcess::on_openAction_triggered()
{
    QString curPath = settings.value("LastPath").toString();
    if (curPath.isEmpty())
    {
        curPath = QDir::currentPath();
    }

    QString dlgTitle = "加载文件";
    QString filter = "图像数据(*.jpg;*.jpeg;*.png;*.bmp);;所有文件(*.*)";
    QString fileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (fileName.isEmpty())
    {
        return;
    }

    //保存当前打开的路径
    QString filePath = QFileInfo(fileName).dir().absolutePath();
    settings.setValue("LastPath", filePath);

    std::string filepath = fileName.toStdString();

    _img = LoadImage(filepath);

    if (!_img.empty())
    {
        QImage qImg;
        if (1 == _img.channels())
        {
            qImg = QImage(_img.data, _img.cols, _img.rows, _img.step, QImage::Format_Grayscale8);
        }
        else if (3 == _img.channels())
        {
            qImg = QImage(_img.data, _img.cols, _img.rows, _img.step, QImage::Format_BGR888);
        }

        QPixmap pImg = QPixmap::fromImage(qImg);

        if (!pImg.isNull())
        {
            scene->clear();

            //创建QGraphicsPixmapItem对象,并添加到场景中
            QGraphicsPixmapItem* item = scene->addPixmap(pImg);

            //更新scene的sceneRect
            QRectF itemBoundRect = item->boundingRect();
            scene->setSceneRect(itemBoundRect);

            //将场景设置为视图的场景
            ui.ImageGraphView->setScene(scene);

            QRectF boundRect = scene->sceneRect();
            ui.ImageGraphView->fitInView(boundRect, Qt::KeepAspectRatio);

            //设置视图属性
            ui.ImageGraphView->setRenderHint(QPainter::Antialiasing); //抗锯齿
            ui.ImageGraphView->setDragMode(QGraphicsView::ScrollHandDrag); //拖拽模式
            ui.ImageGraphView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate); //视口更新模式

            ui.ImageGraphView->show();
        }
    }

    labelCurFile->setText(QString::fromStdString("当前文件: " + filepath));
}

void ImageProcess::on_aboutAction_triggered()
{
    about->setWindowFlags(Qt::WindowCloseButtonHint);
    about->show();
    
}

void ImageProcess::on_linearTranAction_triggered()
{
    int lowGray = 0, highGray = 255;
    cv::Mat dst;
    //dst = linearTran();
}

void ImageProcess::on_gammaTranAction_triggered()
{
    
}

void ImageProcess::on_logTranAction_triggered()
{
    
}
