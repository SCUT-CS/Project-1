#include "STCInterface.h"

/** STC algorithm
  * @author CuiYuxin */
bool STCAlgo::STC(String fileDir, String imgDir, int margin, int ratio, int variance, int cutMethod)
{
	Varialbes vars;
	int nmb = 0;
	Mat img;
	img = imread(fileDir, 0); //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
	if (!img.empty())
	{
		time_t start, end, time, convergeStart, convergeEnd; //��ʱ����
		Mat imggest = Mat::zeros(img.size(), img.type());
		int num = cutMethod;
		int M = img.rows; //ͼ��߶�
		int N = img.cols; //ͼ����
		double epsilon = margin;
		vector<char> Q; //������������
		Tree tree;
		treeIterator it(tree);
		vars.thresU =ratio;
		vars.thresVar = variance;
		Mat sketch(img.size(), CV_8UC1);  //��������ͼ��
		
		start = clock(); //Start building tree
		Algo::BuildTree(img, it, vars.P, vars.C, num, epsilon, DoubleDots(0, 0, M - 1, N - 1));
		Tree::LevelOrder(Q, it); //Ѱ��ͬ��飬��������������ɫ��,�����
		end = clock();
		codeTime = end - start;
		blockNum = vars.P.size();
		bpp = Calculate::BPP(vars.P, img.size(), Q) ;
		cr =  8.0 / bpp;
		
		convergeStart = clock();
		Region** all_region = new Region * [vars.P.size()];
		Segment* UpperLeft = new Segment;
		Segment* Upper = new Segment;
		UpperLeft->Length = M;
		UpperLeft->ActiveELink = nullptr;
		UpperLeft->PreLink = nullptr;
		UpperLeft->SucLink = Upper;
		Upper->Length = M;
		Upper->ActiveELink = nullptr;
		Upper->PreLink = UpperLeft;
		Upper->SucLink = nullptr;
		Segment* UpperRight = nullptr;
		Segment* PreLowerLeft = nullptr;
		num = variance;
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI(0, 0, M, N), all_region, Q, num, vars);
		convergeEnd = clock();
		cverTime = convergeEnd - convergeStart;
		
		Region** pixel_region = new Region * [M * N];
		Mat seg = Mat::zeros(img.size(), img.type());
		for (unsigned int i = 0; i < vars.P.size(); i++)
		{
			int x1 = vars.C[i].dot1.first, x2 = vars.C[i].dot2.first;
			int y1 = vars.C[i].dot1.second, y2 = vars.C[i].dot2.second;
			for (int y = y1; y <= y2; y++)
			{
				uchar* ptrsketch = (uchar*)(seg.data + y * seg.step);
				for (int x = x1; x <= x2; x++)
				{
					ptrsketch[x] = Region::FindParent(all_region[i])->Mean;
					pixel_region[y * N + x] = Region::FindParent(all_region[i]);
				}
			}
		}
		Mat segLine = Mat::zeros(img.size(), img.type());
		for (int y = 0; y < M; y++)
		{
			uchar* ptrsketch = (uchar*)(segLine.data + y * segLine.step);
			for (int x = 0; x < N; x++)
			{
				if (x == N - 1 || y == M - 1)
				{
					ptrsketch[x] = 0;
					break;
				}
				ptrsketch[x] = (pixel_region[y * N + x] != pixel_region[y * N + x + 1] || pixel_region[y * N + x] != pixel_region[(y + 1) * N + x]) ? 0 : 255;
			}
		}
		for (int y = 0; y < M; y++)
		{
			uchar* ptrsketch = (uchar*)(segLine.data + y * segLine.step);
			for (int x = 0; x < N; x++)
			{
				if ((y == 0) || (y == M - 1))
					ptrsketch[x] = 0;
				else if ((x == 0))
					ptrsketch[x] = 0;
			}
		}
		Algo::MakeImggest(imggest, vars.P, vars.C);
		psnr = PSNR(img, imggest);
		
		//����ͼ��
		imwrite(imgDir + "ԭʼ�Ҷ�ͼ��.bmp", img);
		//imwrite(imgDir + "����ָ���ͼ��.bmp", imggest);
		imwrite(imgDir + "����ϲ�ʾ��ͼ1.bmp", seg);
		imwrite(imgDir + "����ϲ�ʾ��ͼ2.bmp", segLine);

		//��ʾ��ͼ
		if (N >= 256 || M >= 256)
		{
			//��������ͼ��
			Mat sketch = Mat::zeros(img.size(), img.type());
			for (int y = 0; y < M; y++)
			{
				uchar* ptrsketch = (uchar*)(sketch.data + y * sketch.step);

				for (int x = 0; x < N; x++)
				{
					ptrsketch[x] = 255;
				}
			}
			//����ͼ���ʼ�����
			//��ԭʼͼ���мӾ���ʱ��ֻ�轫cvRectangle��cvShowImage("�ָ�ʾ��ͼ",sketch512��sketch);�е�sketch��sketch512��Ϊimg1���ɣ����������޸ģ�
			for (int i = 0; i < vars.C.size(); i++)
			{
				if (vars.C[i].dot1.first == 0 && vars.C[i].dot1.second == 0)
				{
					rectangle(img, Point(vars.C[i].dot1.first, vars.C[i].dot1.second), Point(vars.C[i].dot2.first, vars.C[i].dot2.second), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first == 0 && vars.C[i].dot1.second != 0)
				{
					rectangle(img, Point(vars.C[i].dot1.first, vars.C[i].dot1.second - 1), Point(vars.C[i].dot2.first, vars.C[i].dot2.second), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first != 0 && vars.C[i].dot1.second == 0) {
					rectangle(img, Point(vars.C[i].dot1.first - 1, vars.C[i].dot1.second), Point(vars.C[i].dot2.first, vars.C[i].dot2.second), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first != 0 && vars.C[i].dot1.second != 0) {
					rectangle(img, Point(vars.C[i].dot1.first - 1, vars.C[i].dot1.second - 1), Point(vars.C[i].dot2.first, vars.C[i].dot2.second), Scalar(0x00, 0x00, 0x00));
				}
			}
		}
		else
		{
			//��������ͼ��
			Mat sketch512 = Mat::zeros(Size(512, 512), img.type());
			int xr = 511 / (N - 1);
			int yr = 511 / (M - 1);
			for (int y = 0; y < 512; y++)
			{
				uchar* ptrsketch = (uchar*)(sketch512.data + y * sketch512.step);

				for (int x = 0; x < 512; x++)
				{
					ptrsketch[x] = 255;
				}
			}
			//����ͼ���ʼ�����
			for (int i = 0; i < vars.C.size(); i++)
			{
				if (vars.C[i].dot1.first == 0 && vars.C[i].dot1.second == 0)
				{
					rectangle(img, Point(vars.C[i].dot1.first * xr, vars.C[i].dot1.second * yr), Point(vars.C[i].dot2.first * xr, vars.C[i].dot2.second * yr), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first == 0 && vars.C[i].dot1.second != 0)
				{
					rectangle(img, Point(vars.C[i].dot1.first * xr, (vars.C[i].dot1.second - 1) * yr), Point(vars.C[i].dot2.first * xr, vars.C[i].dot2.second * yr), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first != 0 && vars.C[i].dot1.second == 0)
				{
					rectangle(img, Point((vars.C[i].dot1.first - 1) * xr, vars.C[i].dot1.second * yr), Point(vars.C[i].dot2.first * xr, vars.C[i].dot2.second * yr), Scalar(0x00, 0x00, 0x00));
				}
				else if (vars.C[i].dot1.first != 0 && vars.C[i].dot1.second != 0)
				{
					rectangle(img, Point((vars.C[i].dot1.first - 1) * xr, (vars.C[i].dot1.second - 1) * yr), Point(vars.C[i].dot2.first * xr, vars.C[i].dot2.second * yr), Scalar(0x00, 0x00, 0x00));
				}
			}
		}
		//����ͼ��
		imwrite(imgDir + "��Ԫ���ָ�ʾ��ͼ.bmp",img);
		//imwrite(imgDir + "��Ԫ������ָ���ͼ��.bmp", imggest);
		//imwrite(imgDir + "��Ԫ������ϲ�ʾ��ͼ1.bmp", seg);
		//imwrite(imgDir + "��Ԫ������ϲ�ʾ��ͼ2.bmp", segLine);
		for (int i = 0; i < vars.C.size(); i++)
		{
			if (vars.C[i].dot2.first - vars.C[i].dot1.first == 1)
				nmb++;
		}
		blockNum_2 = nmb ;
		areaNum = vars.reg_num ;
		return true;
	}
	else
	{
		return false;
	}
}
