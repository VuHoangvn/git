#include<iostream>
#include<fstream>
#define max 50

using namespace std;

string mau[] = {"blue","green","yellow","orange","pink","gray"
				"red","black","brown","violet","purple"};

int a[max][max], b[max][max];
int V, E;
int vLevel[max], vertex[max], color[max];
int arr[max],count = 0;

void readFile();
void output();
void verLevel();
void swap(int *a, int *b);
void sortVer();
int selectColor(int g[], int l);
int checkColor(int colored[], int numOfColor, int color);
void coloring();

int main()
{
	readFile();
	output();
	verLevel();
	sortVer();
	coloring();
	
	return 0;
}

void readFile()
{
	int p, q;
	ifstream file ("D:\\dothi.txt");
	if(file.is_open())
	{
		file>>V;
		file>>E;
		while(!file.eof())
		{
			file>>p;arr[count] = p;count++;
			file>>q;arr[count] = q;count++;
			a[p][q] = 1;
			a[q][p] = 1;
		}
		file.close();
	}
	else
		cout<<"Error! Can't open file";
	
	for(p = 0; p < V; p++)
		for(q = 0; q < V; q++)
		{
			b[p+1][q+1] = a[p][q];
		}
	for(int i = 1; i <= V; i++)
	{
		vertex[i] = i;
	}
}

void output()
{
	int i,j;
	for(i = 1; i <= V; i++)
	{
		for(j = 1; j <= V; j++)
		{
			cout<<b[i][j]<<" ";
		}
		cout<<endl;
	}
}

void verLevel()
{
	for(int i = 1; i <= V; i++)
	{
		vLevel[i] = 0;
		for(int j = 1; j <= V; j++)
		{
			vLevel[i] = vLevel[i] + b[i][j];
		}
	}
}

void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sortVer()
{
	for(int i = 1; i <= V; i++)
		for(int j = i + 1; j <= V; j++)
		{
			if(vLevel[j] > vLevel[i])
			{
				swap(vLevel[i], vLevel[j]);
				swap(vertex[i], vertex[j]);
			}
		}
	
}

//kiem tra mau trung
int checkColor(int colored[], int numOfColor, int color)
{
	int i; 
	for(i = 1; i <= numOfColor; i++)
		if(color == colored[i])
			return 1;
		return 0;
}

int selectColor(int g[], int l)
{
	int color = 1;
	do{
		if(checkColor(g, l, color) == 0)
		{
			return color;
			break;
		}
		else
		color++;
	}while(1);
}

//to mau cac dinh cua do thi
void coloring()
{
	int i, j, t;
	int color = 1;
	int colorVertex[max], extraColor[max], preVertex[max];
	int k,l;
	i = l = 1;
	t = 1;
	j = 2;
	colorVertex[vertex[i]] = color; // to mau dinh thu nhat
	preVertex[l] = vertex[i]; // gan dinh thu nhat vao mang dinh truoc
	extraColor[0] = color; // dua mau da to vao mang phu
	
	do{
		for(int kb = 1; kb <= l; kb++)
			if(b[vertex[j]][preVertex[kb]] == 1)
				extraColor[t++] = colorVertex[preVertex[kb]];
		// dua mau dinh da to ma ke voi dinh dang xet vao mang phu
		colorVertex[vertex[j]] = selectColor(extraColor,t);
		
		l++;
		preVertex[l] = vertex[j];	// dua dinh da xet vao mang dinh truoc
		j++;	//chuyen sang dinh ke tiep den khi dinh cuoi cung duoc xet
		t = 1;
	}while(j <= V);
	
	cout<<"dinh-----mau to\n";
	for(i = 1; i <= V; i++)
		cout<<i-1<<"\t"<<colorVertex[i]<<endl;
		
	//ghi ra file
	ofstream file ("dothimau.txt");
	file<<"Graph dothi"<<endl;
	file<<"{"<<endl;
	for(i = 1; i <= V; i++)
	{
		file<<"\t"<<i-1<<" [fillcolor = "<<mau[colorVertex[i] -1]<<", style = filled];"<<endl;
	}
	
	for(i = 0; i < 2*E; i+=2)
	{
		file<<"\t"<<arr[i]<<"--"<<arr[i+1]<<";"<<endl;
	}
	file<<"}";
}
