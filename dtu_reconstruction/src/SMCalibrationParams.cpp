#include "SMCalibrationParams.h"

#include <QFileInfo>
#include <QString>
#include <QDateTime>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <opencv2/calib3d/calib3d.hpp>


bool SMCalibrationParams::load(const QString& filename){
    QFileInfo info(filename);
  //  QString type = info.suffix();

    if(info.exists() && info.suffix()=="yml")
        return loadYML(filename);
    else
    {
        std::cerr << "SMCalibrationParams error: no such .yml file: " << filename.toStdString() << std::endl;
        return false;
    }
}

bool SMCalibrationParams::save(const QString& filename){
    QFileInfo info(filename);
    QString type = info.suffix();

    if (type=="slcalib") {return saveSLCALIB(filename);}
    if (type=="yml") {return saveYML(filename);}
    if (type=="m") {return saveMatlab(filename);}

    return false;
}

bool SMCalibrationParams::loadYML(const QString& filename){
    cv::FileStorage fs(filename.toStdString(), cv::FileStorage::READ); //
    if (!fs.isOpened())
    {
        std::cerr << "SMCalibrationParams error: could not open file " << filename.toStdString() << std::endl;
        return false;
    }

    cv::Mat temp;
    fs["Kc"] >> temp; Kc = temp;
    fs["kc"] >> temp; kc = temp;
    fs["Kp"] >> temp; Kp = temp;
    fs["kp"] >> temp; kp = temp;
    fs["Rp"] >> temp; Rp = temp;
    fs["Tp"] >> temp; Tp = temp;

    fs["cam_error"] >> cam_error;
    fs["proj_error"] >> proj_error;
    fs["stereo_error"] >> stereo_error;

    fs.release();

    return true;
}

bool SMCalibrationParams::saveSLCALIB(const QString& filename){


    FILE * fp = fopen(qPrintable(filename), "w");
    if (!fp)
        return false;

    fprintf(fp, "#V1.0 SLStudio calibration\n");
    fprintf(fp, "#Calibration time: %s\n\n", calibrationDateTime.c_str());
    fprintf(fp, "Kc\n%f %f %f\n%f %f %f\n%f %f %f\n\n", Kc(0,0), Kc(0,1), Kc(0,2), Kc(1,0), Kc(1,1), Kc(1,2), Kc(2,0), Kc(2,1), Kc(2,2));
    fprintf(fp, "kc\n%f %f %f %f %f\n\n", kc(0), kc(1), kc(2), kc(3), kc(4));
    fprintf(fp, "Kp\n%f %f %f\n%f %f %f\n%f %f %f\n\n", Kp(0,0), Kp(0,1), Kp(0,2), Kp(1,0), Kp(1,1), Kp(1,2), Kp(2,0), Kp(2,1), Kp(2,2));
    fprintf(fp, "kp\n%f %f %f %f %f\n\n", kp(0), kp(1), kp(2), kp(3), kp(4));
    fprintf(fp, "Rp\n%f %f %f\n%f %f %f\n%f %f %f\n\n", Rp(0,0), Rp(0,1), Rp(0,2), Rp(1,0), Rp(1,1), Rp(1,2), Rp(2,0), Rp(2,1), Rp(2,2));
    fprintf(fp, "Tp\n%f %f %f\n\n", Tp(0), Tp(1), Tp(2));

    fprintf(fp, "cam_error: %f\n\n", cam_error);
    fprintf(fp, "proj_error: %f\n\n", proj_error);
    fprintf(fp, "stereo_error: %f\n\n", stereo_error);

    fclose(fp);

    return true;

}

bool SMCalibrationParams::saveYML(const QString& filename){
    cv::FileStorage fs(filename.toStdString(), cv::FileStorage::WRITE);
    if (!fs.isOpened())
        return false;

    fs << "Kc" << cv::Mat(Kc) << "kc" << cv::Mat(kc)
       << "Kp" << cv::Mat(Kp) << "kp" << cv::Mat(kp)
       << "Rp" << cv::Mat(Rp) << "Tp" << cv::Mat(Tp)
       << "cam_error" << cam_error
       << "proj_error" << proj_error
       << "stereo_error" << stereo_error;
    fs.release();

    return true;
}

bool SMCalibrationParams::saveMatlab(const QString& filename){

    std::ofstream file(qPrintable(filename));
    if (!file)
        return false;

    file << "%%SLStudio calibration"  << std::endl;
    file << "Kc = " << Kc << ";" << std::endl;
    file << "kc = " << kc << ";" << std::endl;
    file << "Kp = " << Kp << ";" << std::endl;
    file << "kp = " << kp << ";" << std::endl;
    file << "Rp = " << Rp << ";" << std::endl;
    file << "Tp = " << Tp << ";" << std::endl;

    file.close();

    return true;

}

void SMCalibrationParams::print(std::ostream &stream){

    stream  << std::setw(5) << std::setprecision(4)
            << "========================================\n"
            << "Camera Calibration: \n"
            << "- cam_error:\n" << cam_error << "\n"
            << "- Kc:\n" << Kc << "\n"
            << "- kc:\n" << kc << "\n"
            << "Projector Calibration: " << "\n"
            << "- proj_error: \n" << proj_error << "\n"
            << "- Kp: \n" << Kp << "\n"
            << "- kp: \n" << kp << "\n"
            << "Stereo Calibration: \n"
            << "- stereo_error:\n" << stereo_error << "\n"
            << "- Rp:\n" << Rp << "\n"
            << "- Tp:\n" << Tp << std::endl;
}
