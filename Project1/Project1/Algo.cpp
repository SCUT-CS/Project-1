#include "Algo.h"

/** Judge if blocks are the same for STC algorithm
  * @author CuiYuxin
  * @param double epsilon
  * @param Mat img
  * @param doubleCoordinate dots
  * @return bool isSame */
bool Algo::JudgeSameBlock(double epsilon, Mat img, doubleCoordinate dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptrtemp = (uchar*)(img.data + y1 * img.step);
	uchar g1 = ptrtemp[x1];
	uchar g2 = ptrtemp[x2];
	ptrtemp = (uchar*)(img.data + y2 * img.step);
	uchar g3 = ptrtemp[x1];
	uchar g4 = ptrtemp[x2];
	for (int y = y1; y <= y2; y++)
	{
		uchar* ptr = (uchar*)(img.data + y * img.step);
		for (int x = x1; x <= x2; x++)
		{
			uchar g = ptr[x];
			double i1 = (double)(y - y1) / (y2 - y1);
			double i2 = (double)(x - x1) / (x2 - x1);
			double g5 = g1 + (g2 - g1) * i2;
			double g6 = g3 + (g4 - g3) * i2;
			double gest = g5 + (g6 - g5) * i1;
			if (g - gest >= -epsilon && g - gest <= epsilon)
			{
				continue;
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

/** Bulid tree for STC algorithm
  * @author CuiYuxin
  * @param Mat img
  * @param treeIterator it
  * @param vector<colorListStandard>& P
  * @param vector<doubleCoordinate>& C
  * @param int& num
  * @param double epsilon
  * @param doubleCoordinate dots */
void Algo::BuildTree(Mat img, treeIterator it, vector<colorListStandard>& P, vector<doubleCoordinate>& C, int& num, double epsilon, doubleCoordinate dots)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* ptr = (uchar*)(img.data);
	colorListStandard temp;
	doubleCoordinate tempc;
	Tree::addchild(it, nw);
	Tree::addchild(it, ne);
	if (num % 2 == 1) //num��Ϊ2����������ˮƽ�ָ�
	{
		num = 0;
		if (y1 == y2)
		{
			Tree::setConfirm(it, '1');
			Tree::deleteChildNode(it, nw);
			Tree::deleteChildNode(it, ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, y2);
			C.push_back(tempc);
			return;
		}
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, y1, x2, (y1 + y2 - 1) / 2)))
		{
			Tree::setChildConfirm(it, '1', nw);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + (y1 + y2 - 1) / 2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, (y1 + y2 - 1) / 2);
			C.push_back(tempc);
		}
		else //����ͬ�����ݹ����
		{
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, doubleCoordinate(x1, y1, x2, (y1 + y2 - 1) / 2));
		}
		num = 0;
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2))) //�ж��°벿��:nechild
		{
			Tree::setChildConfirm(it, '1', ne);
			ptr = (uchar*)(img.data + (y1 + y2 + 1) / 2 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2);
			C.push_back(tempc);
		}
		else //�ݹ����
		{
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, doubleCoordinate(x1, (y1 + y2 + 1) / 2, x2, y2));
		}
	}
	else if (num % 2 == 0)  //num��2������������ֱ�ָ�
	{
		num = 1;
		int vx2 = 0;
		if (x1 == x2)
		{
			Tree::setConfirm(it, '1');
			Tree::deleteChildNode(it, nw);
			Tree::deleteChildNode(it, ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, x2, y2);
			C.push_back(tempc);
			return;
		}
		if (JudgeSameBlock(epsilon, img, doubleCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2)))  //�ж���벿��:nwchild
		{
			Tree::setChildConfirm(it, '1', nw);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[x1], ptr[(x1 + x2 - 1) / 2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[x1], ptr[(x1 + x2 - 1) / 2]);
			P.push_back(temp);
			tempc.setCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2);
			C.push_back(tempc);
		}
		else //����ͬ�����ݹ����
		{
			BuildTree(img, it.getNwChild(), P, C, num, epsilon, doubleCoordinate(x1, y1, (x1 + x2 - 1) / 2, y2));
		}
		num = 1;
		if (JudgeSameBlock(epsilon, img, doubleCoordinate((x1 + x2 + 1) / 2, y1, x2, y2))) //�ж��Ұ벿��:nechild
		{
			Tree::setChildConfirm(it, '1', ne);
			ptr = (uchar*)(img.data + y1 * img.step);
			temp.setFirstHalf(ptr[(x1 + x2 + 1) / 2], ptr[x2]);
			ptr = (uchar*)(img.data + y2 * img.step);
			temp.setLastHalf(ptr[(x1 + x2 + 1) / 2], ptr[x2]);
			P.push_back(temp);
			tempc.setCoordinate((x1 + x2 + 1) / 2, y1, x2, y2);
			C.push_back(tempc);
		}
		else //�ݹ����
		{
			BuildTree(img, it.getNeChild(), P, C, num, epsilon, doubleCoordinate((x1 + x2 + 1) / 2, y1, x2, y2));
		}
	}
	return;
}

/** Make Imggest for STC algorithm
  * @author CuiYuxin
  * @param Mat imggest
  * @param vector<colorListStandard>& P
  * @param vector<doubleCoordinate>& C */
void Algo::MakeImggest(Mat imggest, vector<colorListStandard>& P, vector<doubleCoordinate> C)
{
	uchar g1 = 0, g2 = 0, g3 = 0, g4 = 0;
	for (unsigned int i = 0; i < P.size(); i++)
	{
		g1 = P[i].g1; g2 = P[i].g2;
		g3 = P[i].g3; g4 = P[i].g4;
		int x1 = C[i].dot1.first; 
		int y1 = C[i].dot1.second;
		int x2 = C[i].dot2.first;
		int y2 = C[i].dot2.second;
		if (x1 == x2 && y1 == y2)
		{
			uchar* ptr = (uchar*)(imggest.data + y1 * imggest.step);
			ptr[x1] = g1;
		}
		else if (x1 == x2)
		{
			for (int y = y1; y <= y2; y++)
			{
				double i1 = (double)(y - y1) / (double)(y2 - y1);
				(imggest.data + imggest.step * y)[x1] = (int)(g1 + (g2 - g1) * i1);
			}
		}
		else if (y1 == y2)
		{
			for (int x = x1; x <= x2; x++)
			{
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				(imggest.data + y1 * imggest.step)[x] = (int)(g1 + (g2 - g1) * i2);
			}
		}
		else
		{
			for (int y = y1; y <= y2; y++)
			{
				uchar* ptr = (uchar*)(imggest.data + y * imggest.step);
				for (int x = x1; x <= x2; x++)
				{
					double i1 = (double)(y - C[i].dot1.second) / (C[i].dot2.second - C[i].dot1.second);
					double i2 = (double)(x - C[i].dot1.first) / (C[i].dot2.first - C[i].dot1.first);
					double g5 = g1 + (g2 - g1) * i2;
					double g6 = g3 + (g4 - g3) * i2;
					ptr[x] = g5 + (g6 - g5) * i1;
				}
			}
		}
	}
}

/** Encode matrix for DP algorithm
  * @author CuiYuxin
  * @param Mat* R
  * @param Size s
  * @param vector<char>& Q */
void Algo::EnCode(Mat R,Size s, vector<char>& Q)
{
	int c = 0;
	int offsetValue = 0;
	int count = 0;
	int height = s.height;
	int width = s.width;
	for (int i = 0; i < height; i++)
	{
		c = 0;
		offsetValue = 0;
		count = 0;
		for (int j = 0; j < width; j++)
		{
			int value = R.at<uchar>(i, j);
			if (0 == value)
			{
				if (j == width - 1)
				{
					Q.push_back('0');
				}
			}
			else
			{
				if (1 == value)
				{
					Q.push_back('1');
					Q.push_back('1');
				}
				else if (2 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('1');
				}
				else if (3 == value)
				{
					Q.push_back('1');
					Q.push_back('0');
					Q.push_back('0');
				}
				//λ�ô�1��ʼ ���Ǵ�0��ʼ ���Զ��ȥ1
				int b = ceil(log((double)(width - c - count)) / log(2.0f));
				if (0 == count)
				{
					offsetValue = j;
				}
				else
				{
					offsetValue = j - c - 1;
				}
				b = (b == 0) ? 1 : b;
				count = 1;
				c = j;
				for (int v = b - 1; v >= 0; v--)
				{
					if ((offsetValue & (1 << v)) == 0)
					{
						Q.push_back('0');
					}
					else
					{
						Q.push_back('1');
					}
				}
			}
		}
	}
	
	
}

/** Judge if blocks are the same for DP algorithm
  * @author CuiYuxin
  * @param double epsilon
  * @param Mat img
  * @param doubleCoordinate dots
  * @return bool isSame */
bool Algo::IsSameBlock(const Mat img, doubleCoordinate dots, int margin)
{
	int x1 = dots.dot1.first;
	int y1 = dots.dot1.second;
	int x2 = dots.dot2.first;
	int y2 = dots.dot2.second;
	uchar* gy1 = (uchar*)img.data + y1 * img.step;
	uchar* g1 = gy1 + x1;
	uchar* g2 = gy1 + x2;
	uchar* gy2 = (uchar*)img.data + y2 * img.step;
	uchar* g3 = gy2 + x1;
	uchar* g4 = gy2 + x2;
	bool returnValue = true;

	if (x1 == x2 && y1 == y2)
	{
		returnValue = true;
	}
	else if (y1 == y2)
	{
		for (int x = x1 + 1; x < x2; x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			double g = *g1 + (*g4 - *g1) * i2;
			uchar* gValue = gy1 + x;
			if (abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}

		}
	}
	else if (x1 == x2)
	{
		for (int y = y1 + 1; y < y2; y++)
		{
			double i1 = (double)(y - y1) / (double)(y2 - y1);
			double g = *g1 + (*g4 - *g1) * i1;
			uchar* gy = (uchar*)img.data + y * img.step;
			uchar* gValue = gy + x1;
			if (abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}
		}
	}
	else
	{
		for (int x = x1; x <= x2; x++)
		{
			for (int y = y1; y <= y2; y++)
			{
				double i1 = (double)(y - y1) / (double)(y2 - y1);
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				double g5 = *g1 + (*g2 - *g1) * i2;
				double g6 = *g3 + (*g4 - *g3) * i2;
				double g = g5 + (g6 - g5) * i1;
				uchar* gy = (uchar*)img.data + y * img.step;
				uchar* gValue = gy + x;
				if (abs(*gValue - g) > margin)
				{
					returnValue = false;
					break;
				}
			}
		}
	}

	return returnValue;
}

/** Decode matrix for DP algorithm
  * @author CuiYuxin
  * @param Mat* R
  * @param Size s
  * @param const vector<char>& Q */
void Algo::Decode(Mat R, Size s, const vector<char>& Q)
{
	int n = 0;
	int count = 0;
	//�ϸ�����Ԫ�ص�λ��
	int c = 0;
	int row = 0;
	int num = 0;
	int height = s.height;
	int width = s.width;
	for (int pos = 0; pos < Q.size(); pos++)
	{
		if ('1' == Q[pos])
		{
			pos++;
			if ('1' == Q[pos])
			{
				n = 1;

			}
			else
			{
				pos++;
				if ('1' == Q[pos])
				{
					n = 2;
				}
				else
				{
					n = 3;
				}
			}
		}
		else
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
			continue;
		}
		int b = ceil(log((double)(width - c - count)) / log(2.0f));
		b = b == 0 ? 1 : b;
		count = 1;
		int value = 0;
		for (int i = b - 1; i >= 0; i--)
		{
			pos++;
			if ('1' == Q[pos])
			{
				value += 1 << i;
			}
		}
		if (num == 0)
		{
			c = c + value;
		}
		else
		{
			c = c + value + 1;
		}
		num++;
		R.at<uchar>(row, c) = n;
		if (c == (width - 1))
		{
			row++;
			count = 0;
			c = 0;
			num = 0;
		}
	}
}