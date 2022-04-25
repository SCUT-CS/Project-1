#pragma once
class Edge;
class Region
{
public:
	static Region* FindParent(Region* p);
	double Mean;
	double Var;
	int Size; //�߳�
	Region* Father;
	int Count; //������������
	int SegmentCount; //number of edges shared by the waveform
	Edge* EdgeLink;
};

