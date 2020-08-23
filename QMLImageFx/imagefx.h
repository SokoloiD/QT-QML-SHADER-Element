#ifndef IMAGEFX_H
#define IMAGEFX_H

#include <QQuickPaintedItem>
#include <QImage>
#include <qfuturewatcher.h>
#include "iterableimagerepresentation.h"

class ImageFx : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(ImageFx)

public:
    explicit ImageFx(QQuickItem *parent = nullptr);
    ~ImageFx() override;
    void paint(QPainter *painter) override;

    Q_INVOKABLE void loadImage(QUrl imageFile);
    Q_INVOKABLE void saveImage(QUrl saveFile);
    Q_INVOKABLE void startFx(int fxType, int matrixSize, int chunkSize);//!!!!!!!!!!!!!!
    Q_INVOKABLE void cancelFx();



public slots:


signals:


    //сигналы для QML
    void jobStarted();
    void setProgress(float newProgress);
    void jobDone(QString imageTmpPath);
    void errorOccured(QString errorDescript);

    //сигналы для QFutureWatcher
    void canceledComputation();

private slots:
    //сигналы от QFutureWatcher
    void onEndComputation();
    void onComputationCancelled();
    void onStartComputation();
    void onSetProgressRange(int,int);
    void onSetProgressValue(int);

private :

    void copySourToTagret_(void);

    QImage  *sourceImage_;
    QImage  *targetImage_;
    bool isSourceImageOk_;
    bool isTargetImageOk_;
    QFutureWatcher<void> futureWatcher_;
    int progressRangeStart_;
    int progressRangeEnd_;
    int progressValue_;
    IterableImageRepresentation iterImage_;


};

#endif // IMAGEFX_H
