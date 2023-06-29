#include "defs.h"

void matToQImage(cv::Mat &src_mat, QImage &des_qimg)
{
    switch (src_mat.type())
    {
        // 8位4通道
        case CV_8UC4:
        {
            des_qimg = QImage(src_mat.data, src_mat.cols, src_mat.rows, src_mat.step, QImage::Format_RGB32);

            break;
        }

        // 8位3通道
        case CV_8UC3:
        {
            des_qimg = QImage(src_mat.data, src_mat.cols, src_mat.rows, src_mat.step, QImage::Format_RGB888);
            des_qimg = des_qimg.rgbSwapped();
            break;
        }

        // 8位单通道
        case CV_8UC1:
        {
            static QVector<QRgb>  sColorTable;
            // only create our color table once
            if (sColorTable.isEmpty())
            {
                for (int i = 0; i < 256; ++i) sColorTable.push_back(qRgb(i, i, i));
            }
            des_qimg = QImage(src_mat.data, src_mat.cols, src_mat.rows, src_mat.step, QImage::Format_Indexed8);
            des_qimg.setColorTable(sColorTable);
            break;
        }

        default:
            break;
    }
}