#include "Headers.h"
#include "Tree.h"
#include "Algo.h"
#include "Calculate.h"
#include "Segment.h"
#include "Region.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;
vector<doubleCoordinate> C; //���������
vector<colorListStandard> P; //������ɫ��

/** Main Function
  * @author CuiYuxin
  * @input 1.�����ַ
  * @input 2.ԭ��ͼ
  * @input 3.ת���Ҷ�ͼ�ļ���
  * @input 4.ת��RNAMC�ļ���
  * @input 5.ͬ��췧ֵ
  * @input 6.��ֵ��ֵ
  * @input 7.���ֵ
  * @input 8.�з� 1 ˮƽ 0��ֱ
  */
int main(int argc, char** argv)
{
	int nmb = 0;
	Mat img;
	string imagePath = samples::findFile(argv[1]);
	img = imread(imagePath, 0); //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
	if (argc == 8 && !img.empty())
	{
		time_t start, end, time, convergeStart, convergeEnd, convergeTime; //��ʱ����
		Mat imggest = Mat::zeros(img.size(), img.type());
		int num = atoi(argv[7]);
		int M = img.rows; //ͼ��߶�
		int N = img.cols; //ͼ����
		double epsilon = atof(argv[4]);
		C.clear();
		P.clear();
		vector<char> Q; //������������
		Tree tree;
		treeIterator it(tree);
		thresU = atof(argv[5]);
		thresVar = atof(argv[6]);
		Mat sketch(img.size(), CV_8UC1);  //��������ͼ��
		start = clock(); //Start building tree
		Algo::BuildTree(img, it, P, C, num, epsilon, doubleCoordinate(0, 0, M - 1, N - 1));
		Tree::LevelOrder(Q, it); //Ѱ��ͬ��飬��������������ɫ��,�����
		end = clock();
		time = end - start;
		cout << "��������ʱ��:" << time << "ms" << endl;
		start = clock();
		end = clock();
		time = end - start;
		cout << "��������ʱ��:  " << time << "  ms" << endl << endl;
		cout << "epsilon =  " << epsilon << endl << endl;
		cout << "����:  " << P.size() << endl << endl;
		cout << fixed << setprecision(4) << "BPP:" << Calculate::BPP(P, img.size(), Q) << endl << endl;
		//cout << fixed << setprecision(4) << "CR:  " << 8.0 / BPP(P, img.size(), Q) << endl << endl;
		convergeStart = clock();
		Region** all_region = new Region * [P.size()];
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
		num = atoi(argv[7]);
		Segment::regionSegm(UpperLeft, UpperRight, PreLowerLeft, SegmentParamI( 0, 0, M, N), all_region, Q, num);
		convergeEnd = clock();
		convergeTime = convergeEnd - convergeStart;
		cout << "converge_time of QSC:  " << convergeTime << "  ms" << endl << endl;
		Region** pixel_region = new Region * [M * N];
		Mat seg = Mat::zeros(img.size(), img.type());
		for (unsigned int i = 0; i < P.size(); i++)
		{
			int x1 = C[i].dot1.first, x2 = C[i].dot2.first;
			int y1 = C[i].dot1.second, y2 = C[i].dot2.second;
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

		//cvShowImage("����ϲ�ʾ��ͼ1", seg);
		//cvShowImage("����ϲ�ʾ��ͼ2", seg_line);

		Algo::MakeImggest(imggest, P, C);
		cout << "PSNR of recontructured:  " << PSNR(img, imggest) << endl << endl;
		//cvNamedWindow("�ҶȻ�ͼ��", CV_WINDOW_AUTOSIZE);
		//cvShowImage("�ҶȻ�ͼ��", img1); //��ʾԭʼ�Ҷ�ͼ��
		//cvNamedWindow("QSC����ָ���ͼ��", CV_WINDOW_AUTOSIZE);     //����ָ���ͼ��
		//cvShowImage("QSC����ָ���ͼ��", imggest);//����ת����ĻҶ�ͼ��   //����ָ���ͼ��
		//cvSaveImage(argv[2], img1, 0);//��ͼ��д���ļ�
		//cvSaveImage(argv[3], imggest, 0);//��ͼ��д���ļ�
		// //��ʾ��ͼ
		//cvNamedWindow("�ָ�ʾ��ͼ", CV_WINDOW_AUTOSIZE);
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
			// ��ԭʼͼ���мӾ���ʱ��ֻ�轫cvRectangle��cvShowImage("�ָ�ʾ��ͼ",sketch512��sketch);�е�sketch��sketch512��Ϊimg1���ɣ����������޸ģ�
			
			/*for (int i = 0; i < C.size(); i++)
			{
				if (C[i].x1 == 0 && C[i].y1 == 0)
					cvRectangle(img1, cvPoint(C[i].x1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 == 0 && C[i].y1 != 0)
					cvRectangle(img1, cvPoint(C[i].x1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 != 0 && C[i].y1 == 0)
					cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));
				else   if (C[i].x1 != 0 && C[i].y1 != 0)
					cvRectangle(img1, cvPoint(C[i].x1 - 1, C[i].y1 - 1), cvPoint(C[i].x2, C[i].y2), cvScalar(0x00, 0x00, 0x00));

			}
			cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ�� */
			//��ʾ��ͼ����
		}
		else //�Ŵ�ͼ��
		{
			////��������ͼ��
			//IplImage* sketch512 = cvCreateImage(cvSize(512, 512), IPL_DEPTH_8U, 1);
			//int xr = 511 / (N - 1);
			//int yr = 511 / (M - 1);
			//for (int y = 0; y < 512; y++)
			//{
			//	uchar* ptrsketch = (uchar*)(sketch512->imageData + y * sketch512->widthStep);

			//	for (int x = 0; x < 512; x++)
			//	{
			//		ptrsketch[x] = 255;
			//	}
			//}
			////����ͼ���ʼ�����
			//for (int i = 0; i < C.size(); i++)
			//{
			//	if (C[i].x1 == 0 && C[i].y1 == 0)
			//		cvRectangle(img1, cvPoint(C[i].x1 * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 == 0 && C[i].y1 != 0)
			//		cvRectangle(img1, cvPoint(C[i].x1 * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 != 0 && C[i].y1 == 0)
			//		cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, C[i].y1 * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));
			//	else   if (C[i].x1 != 0 && C[i].y1 != 0)
			//		cvRectangle(img1, cvPoint((C[i].x1 - 1) * xr, (C[i].y1 - 1) * yr), cvPoint(C[i].x2 * xr, C[i].y2 * yr), cvScalar(0x00, 0x00, 0x00));

			//}
			//cvShowImage("�ָ�ʾ��ͼ", img1);//����ת����ĻҶ�ͼ�� 
		 //    //��ʾ��ͼ����
		}
		//cvSaveImage("��Ԫ���ָ�ʾ��ͼ.bmp", img1, 0);//��ͼ��д���ļ� , added by zyp
		//cvSaveImage("��Ԫ������ָ���ͼ��.bmp", imggest, 0);//��ͼ��д���ļ� , added by zyp �ؽ����ͼ��
		//cvSaveImage("��Ԫ������ϲ�ʾ��ͼ1.bmp", seg, 0);//��ͼ��д���ļ� , added by zyp  ����ϲ����þ�ֵ�����ͼ��
		//cvSaveImage("��Ԫ������ϲ�ʾ��ͼ2.bmp", seg_line, 0);//��ͼ��д���ļ� , added by zyp
		//for (int i = 0; i < C.size(); i++)
		//{
		//	if (C[i].x2 - C[i].x1 == 1)
		//		nmb++;
		//}
		////cout << "2*2��������"<< nmb << endl;
		//cout << "����������  " << reg_num << endl << endl;
		//cvWaitKey(0); //�ȴ�����
		//cvReleaseImage(&img1);
		//cvReleaseImage(&imggest);
		//cvDestroyAllWindows();//�ر�
		return 0;

	}
	else
	{
		return -1;
	}
}


	
