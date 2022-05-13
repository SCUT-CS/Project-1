#include "DPInterface.h"
#include "STCInterface.h"

void demoSTC();
void demoDP();

int main(int argc, char** argv)
{
	//demoSTC();
	//demoDP();
}

/** STC Algorithm demo
  * @author CuiYuxin */
void demoSTC()
{
	STCAlgo demo;
	demo.STC("D:/gray_images/lena512.bmp",  "D:/out/", 10, 30, 225, 1); // TODO ��֤����ļ��д���&�����ļ���
	cout << "��������ʱ��" << demo.codeTime;
	cout << "����" << demo.blockNum;
	cout << "BPP" << demo.bpp;
	cout << "CR" << demo.cr;
	cout << "Converage time of QSC" << demo.cverTime;
	cout << "2*2������" << demo.blockNum_2;
	cout << "PSNR"; demo.psnr;
	cout << "��������" << demo.areaNum;
}

/** DP Algorithm demo
  * @author CuiYuxin */
void demoDP()
{
	DPAlgo demo;
	demo.DP("D:/gray_images/lena512.bmp", "D:/out/", 10, 0);
	cout << "��������ʱ��"
		<< demo.encodeTime
		<< "��������ʱ��"
		<< demo.decodeTime
		<< "����"
		<< demo.blockNum
		<< "PSNR"
		<< demo.psnr
		<< "BPP"
		<< demo.bpp
		<< "CR"
		<< demo.cr;
}