#pragma once
#include "Headers.h"
#include "Tree.h"
#include "Algo.h"
#include "Calculate.h"
#include "Segment.h"
#include "Region.h"
class STCAlgo
{
public:
    STCAlgo() {}
    STCAlgo(String fDir, String iDir, double m, double r, double v, int c) :fileDir(fDir), imgDir(iDir), margin(m), ratio(r), variance(v), cutMethod(c) {}
    bool STC(String fileDir, String imgDir, double margin, double ratio, double variance, int cutMethod);
    bool STC()
    {
        return STC(fileDir, imgDir, margin, ratio, variance, cutMethod);
    }

    //������Ϣ
    //1.ԭ��ͼ Ҫ��������ļ�·��
    String fileDir;
    //2.newimg����·��
    String imgDir;
    //3.ͬ��췧ֵ margin��ֵ
    double margin;
    //4.��ֵ��ֵ ratio��ֵ
    double ratio;
    //5.���ֵ
    double variance;
    //6.�з� 1 ˮƽ 0��ֱ
    int cutMethod;

    //�����Ϣ+�����б���ͼ�񲿷�
    //��������ʱ��
    time_t codeTime;
    //��������ʱ��
    //time_t decodeTime;
    //����
    int blockNum;
    //BPP
    double bpp;
    //CR
    double cr;
    //Converage time of QSC
    time_t cverTime;
    //2*2������
    int blockNum_2;
    //PSNR
    double psnr;
    //��������
    int areaNum;
};

