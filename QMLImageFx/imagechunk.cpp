#include "imagechunk.h"

ImageChunk::ImageChunk(QImage *sourceImage, QImage *targetImage,
                       int xOffset, int yOffset,
                       int xSize,int ySize , int chunkSize,
                       float ** matrix ,int matrixSize)
{
    sourceImage_ = sourceImage;
    targetImage_ = targetImage;
    xOffset_ = xOffset;
    yOffset_ = yOffset;
    xSize_ = xSize;
    ySize_ = ySize;

    chunkSize_ = chunkSize;

    matrixPtr_  =matrix;
    matrixSize_ = matrixSize;

}
ImageChunk::~ImageChunk(){}
QColor ImageChunk::getPixel(int x, int y) // цвет точки source изображения и
{
    int newX = x + xOffset_;
    int newY = y + yOffset_;
    return sourceImage_->pixelColor((newX < 0)?0:( newX >= xSize_)?xSize_-1:newX,//проверка на выход за границы
                               (newY < 0)?0:( newY >= ySize_)?ySize_-1:newY);

}
void ImageChunk::setPixel(int x, int y, QColor color) // установка цвета точкт target изображения
{
    int newX = x + xOffset_;
    int newY = y + yOffset_;
    if (newX >=0 && newX < xSize_ && newY >=0 && newY < ySize_ ){
        targetImage_->setPixelColor(newX, newY, color);
    }
}
int ImageChunk::getMatrixSize()
{
    return matrixSize_;
}
int ImageChunk::getChunkSize()
{
    return chunkSize_;
}
float ImageChunk::matrix(int i, int j)
{
    return matrixPtr_[i][j];
}


