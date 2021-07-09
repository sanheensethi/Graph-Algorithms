#include <iostream>
#include <string>
#include<vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#define endl "\n"
using namespace std;

class Edge{
public:
	int source;
	int dest;
	int weight;
	Edge(int source,int dest,int weight){
		this->source = source;
		this->dest = dest;
		this->weight = weight;
	}
};

void printAdjacancy(vector<Edge*> v,int n){
	int** matrix = new int*[n];
	for(int i=0;i<n;i++){
		matrix[i] = new int[n];
		for(int j=0;j<n;j++) matrix[i][j] = 0;
	}
	for(int i=0;i<v.size();i++){
		matrix[v[i]->source][v[i]->dest] = v[i]->weight;
		matrix[v[i]->dest][v[i]->source] = v[i]->weight;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			std::cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}

int ** createAdjacancy(vector<Edge*> v,int n){
	int** matrix = new int*[n];
	for(int i=0;i<n;i++){
		matrix[i] = new int[n];
		for(int j=0;j<n;j++) matrix[i][j] = 0;
	}
	for(int i=0;i<v.size();i++){
		matrix[v[i]->source][v[i]->dest] = v[i]->weight;
		matrix[v[i]->dest][v[i]->source] = v[i]->weight;
	}
	return matrix;
}

void printList(vector<Edge*> v,vector<string> city){
	for(int i=0;i<v.size();i++){
		Edge *current = v[i];
		int src = current->source;
		int dest = current->dest;
		int wt = current->weight;
		if(src<dest){
			cout<<city[src]<<"->"<<city[dest]<<" "<<wt<<" KM"<<endl;
		}else{
			cout<<city[dest]<<"->"<<city[src]<<" "<<wt<<" KM"<<endl;
		}
	}
}

void printList(vector<Edge*> v){
	for(int i=0;i<v.size();i++){
		Edge *current = v[i];
		int src = current->source;
		int dest = current->dest;
		int wt = current->weight;
		if(src<dest){
			cout<<src<<" "<<dest<<" "<<wt<<endl;
		}else{
			cout<<dest<<" "<<src<<" "<<wt<<endl;
		}
	}
}

bool compare(Edge* e1,Edge* e2){
	return (e1->weight) < (e2->weight);
}

int findParent(int v,int *parent){
	if(parent[v] == v){
		return v;
	}
	return findParent(parent[v],parent);
}


void BFS(int **edges,int n,int source,int dest,vector<string> city){
	bool pathFound = false;
	unordered_map<int,int> parent;
	queue<int> q;
	q.push(source);
	parent[source] = -1;
	bool *visited = new bool[n];
	for(int i=0;i<n;i++) visited[i] = false;
	visited[source] = true;
	while(!q.empty()){
		int current = q.front();
		q.pop();
		for(int i=0;i<n;i++){
			if(i==source) continue;
			if(edges[current][i] > 0 && !visited[i]){
				q.push(i);
				visited[i] = true;
				parent[i] = current;
				if(i == dest){
					pathFound = true;
					break;
				}
			}
		}
	}
	cout<<endl;
	vector<int> path;
	if(pathFound){
		int currentVertex = dest;
		while(currentVertex!=-1){
			path.push_back(currentVertex);
			currentVertex = parent[currentVertex];
		}
		cout<<endl<<"Path To Follow : ";
		for(int i=path.size()-1;i>0;i--){
			cout<<path[i]<<"->";
		}
		cout<<path[0];
	}else{
		cout<<"No Path.";
	}
	cout<<endl<<endl;

	vector<int> pathS;
	if(pathFound){
		int currentVertex = dest;
		while(currentVertex!=-1){
			pathS.push_back(currentVertex);
			currentVertex = parent[currentVertex];
		}
		cout<<endl<<"Path To Follow : ";
		for(int i=pathS.size()-1;i>0;i--){
			cout<<city[pathS[i]]<<"->";
		}
		cout<<city[pathS[0]];
	}else{
		cout<<"No Path.";
	}
}

void shortestPath(vector<Edge*> v,int n,int from,int to,vector<string> city){
	int ** matrix = createAdjacancy(v,n);
	/*bool *visited = new bool[n];
	for(int i=0;i<n;i++) visited[i] = false;*/
	BFS(matrix,n,from,to,city); 
}

void kruskal(vector<Edge*> v,int n,vector<string> city){
	vector<Edge*> output;
	sort(v.begin(),v.end(),compare);
	int count = 0;
	int i = 0;
	int *parent = new int[n];
	for(int i=0;i<n;i++) parent[i] = i;
	while(count != n-1){
		Edge* currentEdge = v[i];
		int sourceParent = findParent(currentEdge->source,parent);
		int destParent = findParent(currentEdge->dest,parent);
		if(sourceParent != destParent){
			output.push_back(new Edge(currentEdge->source,currentEdge->dest,currentEdge->weight));
			count++;
			parent[sourceParent] = destParent;
		}
		i++;
	}
	cout<<endl;
	cout<<"MST Adjacancy Matrix : "<<endl;	
	printAdjacancy(output,n);
	cout<<endl;
	cout<<"MST List : "<<endl;
	printList(output);
	cout<<endl;
	printList(output,city);
	cout<<endl;
	cout<<"Enter Source : ";
	int src;cin>>src;
	cout<<endl;
	cout<<"Enter Destination : ";
	int des;cin>>des;
	cout<<endl;
	cout<<"Source : "<<city[src]<<" , "<<"Destination : "<<city[des]<<endl;

	shortestPath(output,n,src,des,city);
}

vector<string> cityCreate(){
	vector<string> city{"Mumbai","Delhi","Bangalore","Hyderabad","Chandigarh","Chennai","Kolkata","Surat","Pune","Jaipur","Lucknow","Kanpur","Nagpur","Inodre","Thane","Bhopal","Visakhapatnam","Patna","Agra","Ghaziabad","Agra","Faridabad","Meerut","RajKot","Varanasi","Amritsar","Srinagar","Dhanbad","Allahabad","Ranchi","JabalPur","Kota","Solapur","Gurgaon","Gorakhpur","Jamshedpur","Jalandhar","Noida","Shimla","Manali","Rohtang","Jammu","Gaya","Udaipur","Bikaner","Tiruchirappalli","Karnataka"};
	return city;
}

int main(){
	int n;cin>>n;
	vector<Edge*> input;
	int s,d,w;
	while(true){
		cin>>s>>d>>w;
		if(s == -1 || d == -1) break;
		input.push_back(new Edge(s,d,w));
	}
	cout<<endl;
	vector<string> city = cityCreate();
	printList(input,city);
	cout<<endl;
	cout<<"List : "<<endl;
	printList(input);
	cout<<endl;
	cout<<"Adjacancy Matrix : "<<endl;
	printAdjacancy(input,n);
	cout<<endl;
	kruskal(input,n,city);
}