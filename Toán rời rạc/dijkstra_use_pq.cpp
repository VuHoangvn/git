#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
#define max 100
 
typedef pair<int, int> iPair;	// iPair ==>  Integer Pair

struct State{
	int g;
	int b;
	char *msg;
	State *p;
};
 
class Graph
{
    int V;    // No. of vertices
 	bool visited[100][100];
 	queue<State *> Q;
 	State *target;

 	
    list< pair<int, int> > *adj;
    list<int> *ad;
    list<int> *pathB;
    list<int> *pathG;
 
	public:
    	Graph(int V);  // Constructor
    	void addEdge(int u, int v, int w);
    	int shortestPath(int s, int end);
    	void initVisited();
    	bool reachTarget(State *S,int end_G, int end_B);
		void markVisit(State *S);
		void findAllPath(int s, int d, int G);
		void findAllPathUtil(int u, int d, bool visited[], 
							 int path[], int path_index, int G);
							 
		
};
 
// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
    ad = new list<int>[V];
    pathB = new list<int>[V];
    pathG = new list<int>[V];
}

void Graph::initVisited(){
	for(int i = 0; i < V; i++)
		for(int j = 0; j < V; j++)
			visited[i][j] = false;	
} 

bool Graph::reachTarget(State *S, int end_G, int end_B){
	return S->g == end_G && S->b == end_B;
}

void Graph::markVisit(State *S){
	visited[S->g][S->b] == true;	
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
    ad[u].push_back(v);
    ad[v].push_back(u);
}
 
// Prints shortest paths from src to all other vertices
int Graph::shortestPath(int src, int end)
{   
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

    vector<int> dist(V, INF);
 
    pq.push(make_pair(0, src));
    dist[src] = 0;
 
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (dist[v] > dist[u] + weight)
            {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    
    return dist[end];
}


// Driver program to test methods of graph class
int main()
{
	ifstream file("D:\\text.txt");
	int V,u,v,w;
	
	if(file.is_open())
		file>>V;
	Graph g(V);
	
	if(file.is_open()){
		while(!file.eof()){
			file>>u;
			file>>v;
			file>>w;
			g.addEdge(u,v,w);
		}
	}else{
		cout<<"Error! Can't open the file.";
	}
    
    int start_G,end_G;	//dinh bat dau va ket thuc cua co gai
    int start_B,end_B;	//dinh bat dau va ket thuc cua chang trai
    int r;				//khoang cach toi thieu giua 2 nguoi
    
 
    cout<<"Nhap diem bat dau va ket thuc cua co gai: ";
    cin>>start_G; cin>>end_G;
    cout<<"Nhap diem bat dau va ket thuc cua chang trai: ";
    cin>>start_B; cin>>end_B;
    cout<<"Nhap khoang cach cho phep giua 2 nguoi: ";
    cin>>r;

 
    if(g.shortestPath(end_G, end_B) < r){
    	cout<<"Khong tim duoc duong di thoa man!!";
    	return 0;
	}
    
    return 0;
}
