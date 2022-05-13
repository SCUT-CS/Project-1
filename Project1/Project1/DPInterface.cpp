#include "DPInterface.h"
#include "Calculate.h"

/** STC algorithm
  * @author CuiYuxin
  * @param String fileDir
  * @param String imgDir
  * @param int margin
  * @param int ratio
  * @return if success */
bool DPAlgo::DP(String fileDir, String imgDir, double margin, double ratio)
{
	Mat img;
	img = imread(fileDir, 0); //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
	if (!img.empty())
	{
		//����ͼƬ
		imwrite(imgDir + "ԭʼ�Ҷ�ͼ��.bmp", img);
		/*һ���ָ�ͬ��鼰����*/
		Size size = img.size();
		int height = size.height;
		int width = size.width;
		Mat markMatrix = Mat::zeros(size, img.type());
		Mat R = Mat::zeros(size, img.type());
		int num = 0;
		vector<ColorNode> colorList;
		vector<DoubleDots> locList;
		time_t begin, end;
		begin = clock();
		/*�ֿ�*/
		Algo::StartNamCut(img, markMatrix, R, colorList, locList, size, margin, num, ratio);
		/*�������*/
		vector<char> Q;
		Algo::EnCode(R, size, Q);
		end = clock();
		encodeTime = end - begin;
		/*������ԭͼ�����ͼ��*/
		Mat T = Mat::zeros(img.size(), img.type());
		begin = clock();
		Algo::Decode(T, size, Q);
		Mat newImg = Mat::zeros(img.size(), img.type());
		Algo::RestoreImage(newImg, markMatrix, T, colorList, size);
		end = clock();
		decodeTime = end - begin;
		blockNum = num;
		psnr = PSNR(img, newImg);
		bpp = Calculate::BPP(colorList, width, height, Q);
		cr = 8.0 / bpp;
		//����ͼƬ
		imwrite(imgDir + "ѹ��ͼ�Ҷ�ͼ��newImg.bmp", newImg);
		//imwrite(imgDir + "ѹ��ͼ�Ҷ�ͼ��img.bmp", img);
		/*�������ָ�ͼ*/
		Mat sketch;
		int xr, yr;
		int sketchXn, sketchYn;
		if (height >= 256 || width >= 256)
		{
			xr = 1, yr = 1, sketchXn = height, sketchYn = width;
			sketch = Mat::zeros(img.size(), img.type());
		}
		else
		{
			xr = 511 / (height - 1);
			yr = 511 / (width - 1);
			sketchXn = 512, sketchYn = 512;
			sketch = Mat::zeros(Size(512, 512), img.type());
		}
		for (int i = 0; i < sketchYn; i++)
		{
			uchar* ptrsketch = (uchar*)(sketch.data + i * sketch.step);
			for (int j = 0; j < sketchXn; j++)
			{
				ptrsketch[j] = 255;
			}
		}
		for (int i = 0; i < locList.size(); i++)
		{
			if (locList[i].dot1.first == 0 && locList[i].dot1.second == 0)
				rectangle(sketch, Point(locList[i].dot1.first, locList[i].dot1.second), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first == 0 && locList[i].dot1.second != 0)
				rectangle(sketch, Point(locList[i].dot1.first, locList[i].dot1.second - 1), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first != 0 && locList[i].dot1.second == 0)
				rectangle(sketch, Point(locList[i].dot1.first - 1, locList[i].dot1.second), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
			else   if (locList[i].dot1.first != 0 && locList[i].dot1.second != 0)
				rectangle(sketch, Point(locList[i].dot1.first - 1, locList[i].dot1.second - 1), Point(locList[i].dot2.first, locList[i].dot2.second), Scalar(0x00, 0x00, 0x00));
		}
		//����ͼƬ
		imwrite(imgDir + "�ָ�ʾ��ͼ.bmp", sketch);
	}
	return false;
}
