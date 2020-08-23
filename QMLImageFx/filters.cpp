#include "filters.h"
#include <stdlib.h>
#include <QVector>


//медианный фильтр
void mapFilter511(ImageChunk  *imageChunk)
{  int size = imageChunk->getChunkSize();
   for (int i = 0; i <size; i++){
       for(int j = 0; j < size; j++){
           filter511(imageChunk, i,j);
       }
   }
}
//сравнение яркости пиеселей
bool colorCompare(QColor c1, QColor c2)
{
    return  c1.lightness() < c2.lightness();
}

//медианный фильтр по каналу яркости
void filter511(   ImageChunk  * imageChunk, int x, int y)
{

    int size = imageChunk->getMatrixSize();
    int halfSize = size/2;
    int N = size*size;
    int cnt = 0;

    std::vector<QColor> cVec(N);

    for (int i = -halfSize; i < halfSize; i++){
        for(int j = -halfSize; j< halfSize; j++){
            cVec[cnt++]  =QColor(imageChunk->getPixel(x + i , y + j ));
        }
    }

    std::sort(cVec.begin(),cVec.end(),colorCompare);

    imageChunk->setPixel(x,y, cVec[N/2]);
}

//размытие
void mapFilter501(ImageChunk  *imageChunk)
{  int size = imageChunk->getChunkSize();
   for (int i = 0; i <size; i++){
       for(int j = 0; j < size; j++){
            filter501(imageChunk, i,j);
       }
   }
}
//инициализация матрицы размытия
void fillBlurMatrix501(float **matrix,int matrixSize)
{
    float norm;
    norm = 1./float(matrixSize*matrixSize);
    for (int i =0; i < matrixSize; i++){
        for(int j=0; j < matrixSize; j++){

            matrix[i][j] = norm;
         }
    }
}
//размытие по каждому каналу отдельно для одного пикселя
void  filter501(   ImageChunk  *imageChunk,  int x, int y)
{
    int size = imageChunk->getMatrixSize();
    int halfSize = size/2;
    float r = 0, g = 0, b = 0, mul;
    QColor col;

    for (int i = -halfSize; i <halfSize; i++){
        for(int j = -halfSize; j<halfSize; j++){
            col = imageChunk->getPixel(x +i,y+j);
            mul = imageChunk->matrix(halfSize + i, halfSize + j);
            r += col.red() * mul;
            g += col.green() *mul;
            b += col.blue() * mul;
        }
     }
   imageChunk->setPixel(x,y, QColor(int(r),int(g),int(b)));
}






