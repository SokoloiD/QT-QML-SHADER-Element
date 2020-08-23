#include "imagefx.h"
#include "qdebug.h"
#include <QFutureWatcher>

#include <QtConcurrent/QtConcurrentMap>
#include <qpainter.h>
#include "filters.h"


ImageFx::ImageFx(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    //setFlag(ItemHasContents, true);
    sourceImage_ = new QImage();
    targetImage_ =new QImage();
    isSourceImageOk_=false;
    isTargetImageOk_=false;


    connect(&futureWatcher_, SIGNAL(finished()), this, SLOT(onEndComputation()));
    connect(&futureWatcher_, SIGNAL(canceled()), this, SLOT(onComputationCancelled()));
    connect(&futureWatcher_, SIGNAL(started()), this, SLOT(onStartComputation()));
    connect(this, SIGNAL(canceledComputation()), &futureWatcher_, SLOT(cancel()));
    connect(&futureWatcher_, SIGNAL(progressRangeChanged(int,int)),this, SLOT(onSetProgressRange(int,int)));
    connect(&futureWatcher_, SIGNAL(progressValueChanged(int)), this, SLOT(onSetProgressValue(int)));


}

ImageFx::~ImageFx()
{
    delete sourceImage_;
    delete targetImage_;
}

void ImageFx::paint(QPainter *painter)
{
    if(isTargetImageOk_)
    {
        painter->drawImage(boundingRect(), *targetImage_) ;

    }
    /*тестовый красный крук
      QBrush  brush(Qt::red);
    painter->setBrush(brush);
    painter->drawEllipse(boundingRect().adjusted(10,10,-10,-10));
*/
}


void ImageFx::loadImage(QUrl imageFile)
{
    isSourceImageOk_ = sourceImage_->load(imageFile.toLocalFile());
    isTargetImageOk_ = targetImage_->load(imageFile.toLocalFile());
    if( (!isSourceImageOk_)||(!isTargetImageOk_))
    {
        emit errorOccured("Ошибка загрузки изображения " +imageFile.toLocalFile());

    }
    else{
        update();
    }


  // qDebug() << imageFile.toLocalFile();
}

void ImageFx::saveImage(QUrl saveFile)
{
    if(isTargetImageOk_){
        if(!targetImage_->save(saveFile.toLocalFile())){
            emit errorOccured(" Ошибка сохранения изображения " + saveFile.toLocalFile());
        }
    }
   // qDebug() <<saveFile;
 }

void ImageFx::startFx(int fxType, int matrixSize, int chunkSize)
{
    qDebug() <<fxType<<matrixSize<<chunkSize;

    if(isSourceImageOk_&&isTargetImageOk_){
            copySourToTagret_();
            iterImage_.convertToIterable(sourceImage_, targetImage_,   chunkSize, matrixSize);


            if(fxType ==0){
                //размытие
                iterImage_.initMatrix(fillBlurMatrix501);
                futureWatcher_.setFuture(QtConcurrent::map(iterImage_.chunks, mapFilter501));
            }
            else{
                //медианный 511
                futureWatcher_.setFuture(QtConcurrent::map(iterImage_.chunks, mapFilter511));
            }
      }
    else{
        emit errorOccured("Ошибка в загруженных изображениях" );

    }

}
//передаем в FutureWatcher прерывание процесса
void ImageFx::cancelFx()
{
  emit canceledComputation();
}

//получаем от fututewatcher сигнал старта и передаем его дальше в QML
void ImageFx::onStartComputation()
{
   emit jobStarted();
   emit setProgress(0.0);

}
//получаем от fututewatcher сигнал завершения и передаем его дальше в QML
void ImageFx::onEndComputation()
{
    update();
    emit jobDone("ок");
}
//получаем от fututewatcher сигнал завершения и передаем его дальше в QML
void ImageFx::onComputationCancelled()
{   emit errorOccured("Вычисления прерваны");
    emit jobDone("cancel");

}
//получаем от fututewatcher границы области прогресса
void ImageFx::onSetProgressRange(int min,int max)
{
    progressRangeStart_ = min;
    progressRangeEnd_= max;

}
//получаем от futurewatcher новое значение прогресса
// конвертируем его и передаем дальше в QML
void ImageFx::onSetProgressValue(int progress)
{     progressValue_ = progress;
      update();
      emit setProgress(float(progressValue_)/float(progressRangeEnd_ - progressRangeStart_));

}
//для обновления изображения в окне . стираем следы старой работы
void ImageFx::copySourToTagret_(void){
    int width = sourceImage_->width();
    int height = sourceImage_->height();
    for(int i = 0; i < width; i ++){
        for(int j = 0; j < height; j++){
            targetImage_->setPixelColor(i, j, sourceImage_->pixelColor(i, j));
        }
    }


}

