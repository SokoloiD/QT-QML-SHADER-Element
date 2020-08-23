#ifndef IMAGECHUNK_H
#define IMAGECHUNK_H
#include "QImage"

/* представляет собой кусок изображения для обработки
 * каждый элемент ссылается на исходное изображение для чтения и
 * другое изображение для записи
 * заодно с помощью getPixel и setPixel закрыается вопрос с расширением поля изображения для обработки краев
 * т.е getPixel для значений за пределами изображения выдает пиксель с границы.
 */
class ImageChunk
{
public:
    ImageChunk(QImage *sourceImage, QImage *targetImage,
               int xOffset, int yOffset,
               int xSize, int ySize, int chunkSize_, float **matrix, int matrixSize);
    ~ImageChunk();
    QColor getPixel(int x, int y);// цвет точки source изображения и
    void setPixel(int x, int y, QColor color);// установка цвета точкт target изображения
    int getMatrixSize();
    int getChunkSize();
    float matrix(int i,int j);

private:
    QImage * sourceImage_;
    QImage *targetImage_;
    int xOffset_;//смещение по оси х
    int yOffset_;//смещение по оси х
    int xSize_;// размеры target  и source изображения
    int ySize_;
    int chunkSize_; //размер области, которую представляет элемент. нужен только для передачи в функцию- обработчик
    int matrixSize_; //размер области, которую представляет элемент. нужен только для передачи в функцию- обработчик

    float **matrixPtr_;

};

#endif // IMAGECHUNK_H
