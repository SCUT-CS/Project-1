#pragma once
class Corner_Vertex
{
public:
	int x;
	int y;
	Corner_Vertex* Next;
};

class Region;
class Edge
{
public:
	Edge* PreLink;
	Edge* SucLink;
	Region* Reg;
	Corner_Vertex* First;
	Corner_Vertex* Last;
};
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

