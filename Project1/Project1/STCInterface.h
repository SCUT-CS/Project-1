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
    bool STC(String fileDir, String imgDir, int margin, int ratio, int variance, int cutMethod);

    //������Ϣ
    //1.ԭ��ͼ Ҫ��������ļ����ļ���
    String fileDir;
    //2.ת���Ҷ�ͼ�ļ��� img����·��
    String grayDir;
    //3.ת��RNAMC�ļ��� newimg����·��
    String imgDir;
    //4.ͬ��췧ֵ margin��ֵ
    int margin;
    //5.��ֵ��ֵ ratio��ֵ
    int ratio;
    //6.���ֵ
    int variance;
    //7.�з� 1 ˮƽ 0��ֱ
    int cutMethod;
	
	//�����Ϣ+�����б���ͼ�񲿷�
	//��������ʱ��
    time_t codeTime;
    //��������ʱ��
    //time_t decodeTime;
	//����
    int blockNum;
	//BPP
    int bpp;
	//CR
    int cr;
	//Converage time of QSC
    time_t cverTime;
	//2*2������
    int blockNum_2;
	//PSNR
    double psnr;
	//��������
    int areaNum;
};

