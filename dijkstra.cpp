#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <climits>
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

vector<string> cityCreate(){
	vector<string> city{"Mumbai","Delhi","Bangalore","Hyderabad","Chandigarh","Chennai","Kolkata","Surat","Pune","Jaipur","Lucknow","Kanpur","Nagpur","Inodre","Thane","Bhopal","Visakhapatnam","Patna","Agra","Ghaziabad","Agra","Faridabad","Meerut","RajKot","Varanasi","Amritsar","Srinagar","Dhanbad","Allahabad","Ranchi","JabalPur","Kota","Solapur","Gurgaon","Gorakhpur","Jamshedpur","Jalandhar","Noida","Shimla","Manali","Rohtang","Jammu","Gaya","Udaipur","Bikaner","Tiruchirappalli","Karnataka"};
	return city;
}

int findMinVertex(int *distance,bool *visited,int n){
	int minVertex = -1;
	for(int i=0;i<n;i++){
		if(!visited[i] && (minVertex == -1 || distance[i] < distance[minVertex])){
			minVertex = i;
		}
	}
	return minVertex;
}

void shortestPath(int *parent,int src,int dest){
	vector<int> path;
	int fsrc = src;
	int fdest = dest;
	while(src != dest){
		path.push_back(parent[dest]);
		dest = parent[dest];
	}
	int i;
	cout<<"Path to Follow : ";
	for(i=path.size()-1;i>0;i--){
		cout<<path[i]<<"->";
	}
	cout<<path[i]<<"->"<<fdest;
	cout<<endl;
	std::vector<string> city = cityCreate();
	cout<<"From : "<<city[fsrc];
	cout<<"To : "<<city[fdest];
	cout<<endl;
	cout<<"Path To Follow : ";
	for(i=path.size()-1;i>0;i--){
		cout<<city[path[i]]<<"->";
	}
	cout<<city[path[i]]<<"->"<<city[fdest];
}

void dijkstra(vector<Edge *> v,int n,int src){
	int **edges = createAdjacancy(v,n);
	int *parent = new int[n];
	int *distance = new int[n];
	bool *visited = new bool[n];

	for(int i=0;i<n;i++){
		parent[i] = i;
		distance[i] = INT_MAX;
		visited[i] = false;
	}
	distance[src] = 0;
	for(int i=0;i<n-1;i++){
		int minVertex = findMinVertex(distance,visited,n);
		visited[minVertex] = true;
		for(int j=0;j<n;j++){
			if(edges[minVertex][j] > 0 && !visited[j]){
				int dist = distance[minVertex] + edges[minVertex][j];
				if(dist < distance[j]){
					distance[j] = dist;
					parent[j] = minVertex;
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<i<<"->"<<distance[i]<<endl;
	}
	cout<<std::endl;
	for(int i=0;i<n;i++){
		cout<<"src = "<<parent[i]<<" dest = "<<i<<endl;
	}

	int source = 0;
	int dest = 1;
	shortestPath(parent,src,dest);
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
	cout<<endl;
	for(int i=0;i<n;i++){
		cout<<city[i]<<endl;
	}
	cout<<endl;
	int source = 0;
	dijkstra(input,n,source);
	return 0;
}