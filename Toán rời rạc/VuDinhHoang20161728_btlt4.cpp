#include<bits/stdc++.h>
using namespace std;
# define INF 0x3f3f3f3f
#define max 100
 
// xet cac dinh bat dau tu 0
//neu file test dinh bat dau tu 1 thi chi can tang V len 1 
//thuat toan se chay bt

typedef pair<int, int> iPair;	// iPair ==>  Integer Pair

struct State{
	int g;
	int b;
	State *p;
};

State *target;

int start_G,end_G;	//dinh bat dau va ket thuc cua co gai
int start_B,end_B;	//dinh bat dau va ket thuc cua chang trai
int r;				//khoang cach toi thieu giua 2 nguoi
int weight[100][100];

int V;    // No. of vertices 
int m;	//so cung cua do thi	
bool visited[100][100];
queue<State *> Q; 	
list< pair<int, int> > *adj;

void addEdge(int u, int v, int w);
int shortestPath(int s, int end);
void initVisited();
bool reachTarget(State *S);
void markVisit(State *S);
bool boyMoveOnly(State* S);
bool girlMoveOnly(State* S);
bool bothMove(State *S);
 

void initVisited(){
	for(int i = 1; i < V+1; i++)
		for(int j = 1; j < V+1; j++)
			visited[i][j] = false;	
} 

bool reachTarget(State *S){
	return S->g == end_G && S->b == end_B;
}

void markVisit(State *S){
	visited[S->g][S->b] == true;	
}

bool checkVisited(int u, int v){
	if(visited[u][v])
		return true;
	else
		return false;
}
bool girlMoveOnly(State *S){
	list< pair<int, int> >::iterator i;
	for(i = adj[S->g].begin(); i != adj[S->g].end(); i++){
		if(shortestPath(S->b,(*i).first) >= r && !checkVisited(S->b,(*i).first)){
			State *newS = new State;
			newS->b = S->b;
			newS->g = (*i).first;
			newS->p = S;
			Q.push(newS);
			markVisit(newS);
			if(reachTarget(newS)){
				target = newS;
				return true;
			}
		}
	}
}

bool boyMoveOnly(State  *S){
	list< pair<int, int> >::iterator i;
	for(i = adj[S->b].begin();i != adj[S->b].end();i++){
		if(shortestPath((*i).first,S->b) >= r && !checkVisited((*i).first,S->b)){
			State *newS = new State;
			newS->b = (*i).first;
			newS->g = S->g;
			newS->p = S;
			Q.push(newS);
			markVisit(newS);
			if(reachTarget(newS)){
				target = newS;
				return true;
			}
		}
	}
}

bool bothMove(State *S){
	list< pair<int, int> >::iterator i,j;
	for(i = adj[S->g].begin(); i != adj[S->g].end(); i++)
		for(j = adj[S->b].begin();j != adj[S->b].end();j++)
			if(shortestPath((*j).first,(*i).first) >= r && !checkVisited((*j).first,(*i).first)){
				State *newS = new State;
				newS->b = (*j).first;
				newS->g = (*i).first;
				newS->p = S;
				Q.push(newS);
				markVisit(newS);
				if(reachTarget(newS)){
					target = newS;
					return true;
				}
			}
}
void addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

int shortestPath(int src, int end)
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

void readFile(){
	int u, v, w;
	ifstream file("D:\\bt1.txt");
	if(file.is_open()){
		file>>V;
		file>>m;
		adj = new list<iPair> [V+1];
		
		while(!file.eof()){
			for(int i = 0; i < m; i++){
				file>>u;
				file>>v;
				file>>w;
				addEdge(u,v,w);
				weight[u][v] = weight[v][u] = w;
			}
			file>>start_G;
			file>>start_B;
			file>>end_G;
			file>>end_B;
			file>>r;
		}
	}
	
}

void printSolve(State *target){
	cout<<"----------------Result-----------------"<<endl;
	if(target == NULL)
		cout<<"Khong the";
	State *currentS = target;
	stack <State*> path;
	while(currentS != NULL){
		path.push(currentS);
		currentS = currentS->p;
	}
	while(path.size() > 0){
		currentS = path.top();
		path.pop();
		cout<<"("<<currentS->b<<" , "<<currentS->g<<" , distance = "<<shortestPath(currentS->b,currentS->g)<<")"<<endl;
	}
}

void solve(){
	initVisited();
	
 	State *S = new State;
 	S->b = start_B;	S->g = start_G; S->p = NULL;
 	markVisit(S);	Q.push(S);
 	while(!Q.empty()){
 		State *S = Q.front();	Q.pop();
 		if(boyMoveOnly(S)) break;
 		if(girlMoveOnly(S)) break;
 		if(bothMove(S)) break;
	 }
}
// Driver program to test methods of graph class
int main()
{
	readFile();
	cout<<shortestPath(1,4);
	if(shortestPath(start_G,start_B) < r){
		cout<<"Diem bat dau khong thoa man r!";
		return 0;
		
	}
    if(shortestPath(end_B, end_G) < r){
    	cout<<"--------------Result---------------"<<endl;
    	cout<<"Khong the.";
    	return 0;
	}
    target = NULL;

 	solve();
    printSolve(target);
    return 0;
}
