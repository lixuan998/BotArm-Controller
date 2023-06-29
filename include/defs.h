#ifndef __DEFS_H__
#define __DEFS_H__
#include <thread>
#include <iostream>
#include <QMutex>
#include <QImage>

#include "opencv_headers.h"

#define CARGO_SIZE 230512

static QMutex qmutex;

typedef struct _Cargo{
    int height;
    int width;
    int type;
    char data[CARGO_SIZE];

}Cargo;

void matToQImage(cv::Mat &src_mat, QImage &des_qimg);

#endif