#ifndef ITERABLEIMAGEREPRESENTATION_H
#define ITERABLEIMAGEREPRESENTATION_H
#include <QImage>

/*
 * Класс позволяет представить изображение в виде списка кусочков в списке типа Qlist
 * (итерируемый объект) для обработки функцией map
 * дополнительно экземпляр класса хранит в себе матрицу преобразований и осуществляет ее инициализацию
 */

#include "qlist.h"
#include "imagechunk.h"

class IterableImageRepresentation
{
public:
    IterableImageRepresentation();
    ~IterableImageRepresentation();
    void convertToIterable(QImage *sourceImage, QImage *targetImage, int chunkSize, int matrixSize);

    QList<ImageChunk*> chunks;
    //функция инициализации матрицы
    void initMatrix(void(*fillMatrix)(float **matrix, int N));
private:
    float **matrix_; //матрица преобразования
    void freeMatrix_(); //освобождение памати под матрицу
    void allocMatrix_();//выделение памяти под матрицу

    void clear_();//очищает список и освобождает память

    //void initMatrixTo511Median_();

    int xSize_;// размеры target  и source изображения
    int ySize_;
    int chunkSize_; //размер области, которую представляет элемент. нужен только для передачи в функцию- обработчик
    int matrixSize_; //размер области, которую представляет элемент. нужен только для передачи в функцию- обработчик


};

#endif // ITERABLEIMAGEREPRESENTATION_H
