#ifndef FILTERS_H
#define FILTERS_H

#include <QImage>
#include <QColor>
#include "imagechunk.h"

/*
 * фильтры обработки изображения для обработки только одного элемента изображения
 * размер матрицы фильтра - параметр chunkSizе  в элементе
 *
 */

//фильтр размытие
void mapFilter501(  ImageChunk  *imageChunk);//размытие для всего куска
void filter501(   ImageChunk  * imageChunk, int x, int y);//применение фильтра только к одному пиеселю
void fillBlurMatrix501(float **matrix,int matrixSize);//матрица размытия (можно было бы для гаусса сделать)

//медианный фильтр
void mapFilter511(  ImageChunk *imageChunk);//медианный фильтр для всего куска
void filter511(   ImageChunk  * imageChunk, int x, int y);//применение фильтра только к одному пиеселю



#endif // FILTERS_H
