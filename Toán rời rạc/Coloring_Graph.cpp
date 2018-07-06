#include<iostream>
#include<fstream>
#include<iomanip>
#define Max 50

using namespace std;

int a[Max][Max];
int verLevel[Max];
int vertex[Max];
int V,E;

// khai bao dang khuong mau cua ham hoan vi
template<class KDL>

void swap(int *a, int *b)
{
	int temp;
	temp = *a; 
	*a = *b; 
	*b = temp;
}

void readFile();
void arrVertex();
void vertexLevel();
void sortVertex();
int selectColor(int g[], int l);
int checkColor(int colored[], int numOfColor, int color);
void coloring();
void output();

int main()
{
	readFile();
	cout<<endl;
	output();
	vertexLevel();
	arrVertex();
	sortVertex();
	coloring();
	
	return 0;
}

void readFile()
{
	int q,p;
	ifstream file("D:\\dothi.txt");
	if(file.is_open())
	{
		file>>V;
		file>>E;
		for(int i = 0; i < V; i++)
			for(int j = 0; j < V; j++)
			{
				a[i][j] = 0;
			}
		while(!file.eof())
		{
			file>>p;
			file>>q;
			a[p][q] = 1;
			a[q][p] = 1;
		}
		file.close();
	}else
	{
		cout<<"Error! Can't open file.";
	}
	
}

void output()
{
	int i,j;
	for(i = 0; i < V; i++)
	{
		for(j = 0; j < V; j++)
		{
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

void arrVertex()
{
	int i;
	int count = 1;
	for(i = 0; i < V; i++)
	{
		vertex[i] = count++;
	}
}

void vertexLevel()
{
	int i, j;
	for(i = 0; i < V; i++)
	{
		verLevel[i] = 0;
		for(j = 0; j < V; j++)
			verLevel[i] = verLevel[i] + a[i][j];
	}
}

void sortVertex()
{
	int i, j;
	for(i = 0; i < V -1 ; i++)
		for(j = i+1; j < V; j++)
			if(verLevel[i] < verLevel[j])
			{
				swap(verLevel[i], verLevel[j]);
				swap(vertex[i], vertex[j]);
			}
}

int checkColor(int colored[], int numOfColor, int color)
{
	int i; 
	for(i = 0; i < numOfColor; i++)
		if(color == colored[i])
			return 1;
		return 0;
}

int selectColor(int g[], int l)
{
	int color = 1;
	
	do
	{
		if(checkColor(g, l, color) == 0)
		{
			return color;
			break;
		}
		else
			color++;
	}while(1);
}

void coloring()
{
	int i, j, t;
	int color = 1;
	int vertexColor[Max], extraColor[Max], preVertex[Max];
	int k, l;
	i = l = 1;
	t = 1; j = 2;
	vertexColor[vertex[i]] = color;			//to mau dinh thu nhat
	preVertex[l] = vertex[i];	//gan dinh thu nhat vao mang dinh truoc
	extraColor[0] = color;		//dua mau da to vao mang phu
	
	do
	{
		for(int kb = 0; kb < l; kb++)
			if(a[vertex[j]][preVertex[kb]] == 1)
				extraColor[t++] = vertexColor[preVertex[kb]];
	//dua dinh da to ma ke voi dinh dang xet vao mang phu
	vertexColor[vertex[j]] = selectColor(extraColor,t);
	l++;
	preVertex[l] = vertex[j];	//dua dinh dang xet vao mang truoc
	j++;	//chuyen sang xet dinh ke tiep den dinh cuoi cung
	t = 1;
	
	}while(j<=V);
	
	cout<<"dinh ---- mauto\n";
	for(i = 0; i < V; i++)
		cout<<setw(10)<<i<<vertexColor[i];
		
}
