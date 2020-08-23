#include "iterableimagerepresentation.h"
#include "imagechunk.h"

IterableImageRepresentation::IterableImageRepresentation()
{  chunkSize_=0;
   matrixSize_ =0;
   matrix_ = nullptr;
}

IterableImageRepresentation::~IterableImageRepresentation()
{
    clear_();
    freeMatrix_();
};
void IterableImageRepresentation::convertToIterable(QImage *sourceImage,
                                                    QImage *targetImage, int chunkSize, int matrixSize)
{
    int width = sourceImage->width();
    int height = sourceImage->height();
    chunkSize_ = chunkSize;


   clear_();
   freeMatrix_();
   matrixSize_ = matrixSize;
   allocMatrix_();
    for(int x = 0; x < width; x += chunkSize_ )
        for(int y = 0; y < height; y += chunkSize_){
            chunks.append(new ImageChunk(sourceImage, targetImage,
                                         x, y, width, height,
                                         chunkSize_, matrix_, matrixSize_));
        }
}
//освобождает память от элементов
void IterableImageRepresentation::clear_()
{
   ImageChunk *ic;
   while(chunks.count()){
        ic = chunks.takeAt(0);
        delete ic;
    }
}

//освобождает память от матрицы
void IterableImageRepresentation::freeMatrix_()
{
    if(matrixSize_){
            for (int i=0; i < matrixSize_ ; i++){
               delete [] matrix_[i];
        }
        delete [] matrix_;
        matrixSize_=0;
    }
}
//выделяет  память  матрицы
void IterableImageRepresentation::allocMatrix_()
{

    matrix_ = new float * [matrixSize_];

    for (int i=0; i < matrixSize_ ; i++){
            matrix_[i] = new float[matrixSize_];

    }
}
//инициализация матрицы в соответствии с логикой фильтра
void IterableImageRepresentation::initMatrix(void(*fillMatrix)(float ** matrix, int N))
{
    fillMatrix(matrix_,matrixSize_);
}


