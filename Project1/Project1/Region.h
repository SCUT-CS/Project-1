#pragma once
class Edge;
class Region
{
public:
	
private:
	double Mean;
	double Var;
	int Size; //�߳�
	Region* Father;
	int Count; //������������
	int SegmentCount; //number of edges shared by the waveform
	Edge* EdgeLink;
};

