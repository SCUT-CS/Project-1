#pragma once
#include "Headers.h"
#include "Algo.h"

class DPAlgo
{
public:
	DPAlgo() {}
	DPAlgo(String fDir, String iDir, double m, double r) :fileDir(fDir), imgDir(iDir), margin(m), ratio(r) {}
	bool DP(String fileDir, String imgDir, double margin, double ratio);
	bool DP()
	{
		return DP(fileDir, imgDir, margin, ratio);
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

	//�����Ϣ
	//��������ʱ��
	time_t encodeTime;
	//��������ʱ��
	time_t decodeTime;
	//����
	int blockNum;
	//PSNR
	double psnr;
	//BPP
	double bpp;
	//CR
	double cr;
};

