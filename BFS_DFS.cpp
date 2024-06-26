# include <iostream>
# include <stack>
# include <queue>
using namespace std;

class node{
	int id;
	int wt;
	node* next;

public:
	node(){
		id = 0;
		wt = 0;
		next = NULL;
	}

	node(int id, int wt){
		this->id = id;
		this->wt = wt;
		next = NULL;
	}

	friend class Graph;
};

class Graph{
	int v, e;			// No. of vertices and Edges
	node** adjList;		// Adjacency List to store node-edges
	string* cityNames;	// Map ID to name of city

public:
	Graph(){
		v = e = 0;
		adjList = NULL;
		cityNames = NULL;
	}

	Graph(int v, int e){
		this->v = v;
		this->e = e;
		adjList = new node*[v];
		for (int i=0; i<v; ++i){
			adjList[i] = NULL;
		}
		cityNames = new string[v];
	}

	void setData(int v, int e){
		this->v = v;
		this->e = e;
		adjList = new node*[v];
		for (int i=0; i<v; ++i){
			adjList[i] = NULL;
		}
		cityNames = new string[v];
	}

	void accept_nodes();
	void insert_edge(int srcID, int destID, string srcCity, string destCity, int wt);
	void display();

	int indegree(int id);
	int outdegree(int id);
	bool isConnected();

	void DFS(int currID);
	void DFS_iterative(int currID);
	void BFS(int currID);
};

// driver code ------------

int main(){
	Graph g;
	int choice = -1;
	int temp = 0;

	cout << "# Flight Paths using Graph\n";
	while(choice){
		cout << "\n---------- MENU ----------\n"
			 << "1. Create graph\n"
			 << "2. Accept nodes (flight paths)\n"
			 << "3. Display graph (flight paths)\n"
			 << "4. Check In-degree\n"
			 << "5. Check Out-degree\n"
			 << "6. Check if graph is connected\n"
			 << "7. Depth First Search (DFS)\n"
			 << "8. Breadth First Search (BFS)\n"
			 << "0. Exit"
			 << "\n--------------------------" << endl;
		cout << "Enter choice = ";
		cin >> choice;

		switch(choice){
		case 1: // Create graph
		{
			int v=0, e=0;
			cout << "Enter no. of Vertices = ";
			cin >> v;
			cout << "Enter no. of edges = ";
			cin >> e;
			g.setData(v, e);
			break;
		}

		case 2: // Accept nodes (flight paths)
		{
			g.accept_nodes();
			break;
		}

		case 3: // Display graph (flight paths)
		{
			g.display();
			break;
		}

		case 4: // Check In-degree
		{
			cout << "Enter vertex ID to find in-degree = ";
			cin >> temp;
			cout << "In-degree of " << temp << " = " << g.indegree(temp);
			break;
		}

		case 5: // Check Out-degree
		{
			cout << "Enter vertex ID to find out-degree = ";
			cin >> temp;
			cout << "Out-degree of " << temp << " = " << g.outdegree(temp);
			break;
		}

		case 6: // Check if graph is connected
		{
			string status = (g.isConnected()) ? ("graph is connected") : ("graph is disconnected");
			cout << status << endl;
			break;
		}

		case 7: // Depth First Search (DFS)
		{
			temp = 0;
			cout << "Enter node id to start DFS from = ";
			cin >> temp;
			cout << "Nodes visited by DFS = ";
			g.DFS_iterative(temp);
			break;
		}

		case 8: // Breadth First Search (BFS)
		{
			temp = 0;
			cout << "Enter node id to start BFS from = ";
			cin >> temp;
			cout << "Nodes visited by BFS = ";
			g.BFS(temp);
			break;
		}

		case 0: // Exit
		{
			cout << "Thank you :)" << endl;
			break;
		}

		default : // forced exit
		{
			cout << "# Forced exit due to error" << endl;
			exit(0);
		}
		}
	}
	return 0;
}

// DEFINITIONS -------------------------------------------------------------------

void Graph::accept_nodes() {
	cout << "Enter " << e << " edges:\n" << endl;
	int srcID, destID, wt;
	string srcCity, destCity;
	for (int i=0; i<e; ++i){
		cout << "\nsource ID = ";
		cin >> srcID;
		cout << "source City Name = ";
		cin >> srcCity;
		cout << "destination ID = ";
		cin >> destID;
		cout << "destination City Name = ";
		cin >> destCity;
		cout << "edge weight (Time of Flight in Hrs) = ";
		cin >> wt;

		insert_edge(srcID, destID, srcCity, destCity, wt);
		cout << "Edge " << srcCity << "->" << destCity << " inserted." << endl;
	}
}

void Graph::insert_edge(int srcID, int destID, string srcCity, string destCity, int wt) {
	cityNames[srcID] = srcCity;
	cityNames[destID] = destCity;

	node* n = new node(destID, wt);

	// empty list
	if(adjList[srcID] == NULL){
		adjList[srcID] = n;
		return;
	}

	// non-empty list
	node* temp = adjList[srcID];
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = n;
	return;
}

void Graph::display() {
	cout << "Adjacency List of Graph:" << endl;
	for (int i=0; i<v; ++i){
		node* temp = this->adjList[i];
		cout << "(" << i << "-" << cityNames[i] << ")" << "->\t";
		while (temp != NULL){
			cout << "|" << temp->id << ":" << cityNames[temp->id] << ":" << temp->wt << "| ";
			temp = temp->next;
		}
		cout << endl;
	}
}

int Graph::indegree(int keyID) {
	int indegree = 0;
	node* temp;
	for (int i=0; i<v; ++i){
		temp = adjList[i];
		while (temp != NULL){
			if (temp->id == keyID){
				++indegree;
			}
			temp = temp->next;
		}
	}
	return indegree;
}

int Graph::outdegree(int id) {
	node* temp = adjList[id];
	int outdegree = 0;
	while(temp != NULL){
		++outdegree;
		temp = temp->next;
	}
	return outdegree;
}

bool Graph::isConnected() {
	int* indegree = new int[v];
	int* outdegree = new int[v];

	for (int i=0; i<v; ++i){
		indegree[i] = this->indegree(i);
		outdegree[i] = this->outdegree(i);
	}

	for (int i=0; i<v; ++i){
		if (indegree[i] == 0 && outdegree[i] == 0){
			return false;
		}
	}
	return true;
}

void Graph::DFS_iterative(int currID){
    // Create a stack for DFS
	stack<int> st;
	bool* visited_nodes = new bool[v];

    // Push the current source node and mark it as visited
	st.push(currID);
	visited_nodes[currID] = true;

	while (!st.empty()){
		// Pop a vertex from stack and print it
		currID = st.top();
		st.pop();
		cout << cityNames[currID] << " ";

		// check adjacency list of current node
		node *temp = adjList[currID];
		while(temp != NULL){
			if (!visited_nodes[temp->id]){
				visited_nodes[temp->id] = true;
				st.push(temp->id);
			}
			temp = temp->next;
		}
	}
}

void Graph::BFS(int currID) {
    // Create a queue for BFS
	queue<int> q;
	bool* visited_nodes = new bool[v];

    // Push the current source node and mark it as visited
	q.push(currID);
	visited_nodes[currID] = true;

	while (!q.empty()){
		// Pop a vertex from queue and print it
		currID = q.front();
		q.pop();
		cout << cityNames[currID] << " ";

		node *temp = adjList[currID];
		while(temp != NULL){
			if (!visited_nodes[temp->id]){
				visited_nodes[temp->id] = true;
				q.push(temp->id);
			}
			temp = temp->next;
		}
	}
}
