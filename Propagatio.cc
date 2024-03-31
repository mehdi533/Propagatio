#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <unistd.h>
#include <fstream>
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::stable_sort

using namespace std;

const string P1("P1 missing or incorrect");
const string WRONG_NB_COL_LGN("Nb columns and/or nb lines incorrect");
const string MATRIX_SQUARE("Matrix is not square");
const string IRREGULAR_CONTENT
("Matrix description with incorrect content");
const string DISCONNECTED_GRAPH
("Matrix corresponds to a disconnected graph");

// ---------------------------------------------------------------------

void initialize(vector<vector<bool> > &matAdj);
void errors_or_no(string Name, int unsigned rows, int unsigned columns);
// ---------------------------------------------------------------------
bool check_connexe(vector<vector<bool> > &matrix);
void set_visited(vector<vector<bool> > &matAdj, int node,
vector<bool> &visited);
// ---------------------------------------------------------------------
void change_degree(vector<vector<bool> > &matAdj, unsigned node,
vector<unsigned> &degree, unsigned track);
void count_propagation_node(vector<vector<bool> > &matAdj,
unsigned node, vector<int unsigned> &propagation, double &average,
bool &check);
long print_degree_nodes(const vector<unsigned> &degree, bool &check);
// ---------------------------------------------------------------------
int count_propagation_graph(vector<vector<bool> > &matAdj);
// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
	vector<vector<bool> > matAdj;
	initialize(matAdj);

	if(!check_connexe(matAdj)){
        cout << DISCONNECTED_GRAPH << endl;
        exit(0);
    }
    count_propagation_graph(matAdj);
	return 0;
}

// ---------------------------------------------------------------------

void initialize(vector<vector<bool> > &matAdj){
	string Name;
	int unsigned rows, columns;
	cin >> Name >> rows >> columns;
	///CHECK IF NO P1 ERROR OR SIZE EROOR
	errors_or_no(Name, rows, columns);
	if(rows == 1){
		cout << setprecision(6); // 6 chiffres à droite de la virgule
		cout << fixed;
		double trivial = 0.;
		cout << 0 << endl;
		cout << trivial << endl;
		exit(0);
	}
	///ENTER VALUES
	for(unsigned i = 0; i < rows; i++){
		vector<bool> lines;
        int unsigned input;
        for(unsigned j = 0; j < rows; j++){
            cin >> input;
            if(input != 1 and input != 0){
				cout << IRREGULAR_CONTENT << endl;
				exit(0);
			}
            lines.push_back(input);
        }
        matAdj.push_back(lines);
    }
    ///CHECK IF SYMETRIC
    for(unsigned i = 0; i < columns ; i++){
       if(matAdj[i][i] != 0){
           matAdj[i][i]=0;
       }
       for(unsigned j = 0 ; j < rows; j++){
           if(matAdj[i][j] != matAdj[j][i]){
               if(matAdj[i][j]){
                    matAdj[j][i]=1;
				} else {
                    matAdj[i][j]=1;
				}
           }
       }
   }

}

void errors_or_no(string Name, int unsigned rows, int unsigned columns){
	if(Name != "P1"){
		cout << P1 << endl;
		exit(0);
	}
	if(rows < 1 or columns < 1){
		cout << WRONG_NB_COL_LGN << endl;
		exit(0);
	}
	if(rows != columns){
		cout << MATRIX_SQUARE << endl;
		exit(0);
	}
}

// ---------------------------------------------------------------------

bool check_connexe(vector<vector<bool> > &matAdj){
    vector<bool> visited(matAdj.size());
    bool is_connexe = true;
    set_visited(matAdj, 0, visited);

    for(unsigned i=0; i < visited.size(); i++){
        is_connexe = is_connexe and visited[i];
    }
    return is_connexe;
}
void set_visited(vector<vector<bool> > &matAdj, int node,
vector<bool> &visited){
	visited[node] = true;
		for(unsigned int i=0 ; i < matAdj.size() ; i++){
			if(matAdj[node][i] and !visited[i]){
				set_visited(matAdj, i, visited);
			}
		}
}

// ---------------------------------------------------------------------

int count_propagation_graph(vector<vector<bool> > &matAdj) {
    double average = 0.;
    unsigned n = matAdj.size();
    vector<int unsigned> propagation;
    cout << setprecision(6); // 6 chiffres à droite de la virgule
    cout << fixed;
    bool check (true);

    for(unsigned i=0; i<n; i++) {
        //~ cout << "count_propagation_graph: " << i << endl;
        count_propagation_node(matAdj, i, propagation, average, check);
    }
    //~ cout << "-------------------" << endl;
	cout <<  (average / (n*n-n)) << endl;
    return 0;
}
void count_propagation_node(vector<vector<bool> > &matAdj,
unsigned node, vector<int unsigned> &propagation, double &average, bool &check) {
    unsigned n = matAdj.size();
    vector<unsigned> degree(n);
    vector<bool> visited(n);
	cout << setprecision(6); // 6 chiffres à droite de la virgule
    cout << fixed;
    change_degree(matAdj, node, degree, 1);
    long total = print_degree_nodes(degree, check);
	average += total;
}
void change_degree(vector<vector<bool> > &matAdj, unsigned node,
vector<unsigned> &degree, unsigned track){
    degree[node] = track;

    for(unsigned i=0; i < matAdj.size(); i++){
        // change if not visited or new degree is less
        bool change =  (degree[i] == 0 or degree[i] > track+1);
        // only connected nodes are considered
        if(i!=node && matAdj[node][i] && change) {
            change_degree(matAdj, i, degree, track+1);
        }
    }
}
long print_degree_nodes(const vector<unsigned> &degree, bool &check) {
	vector<string> degree_nodes(degree.size());
	long total = 0.;
	vector<bool> visited(degree.size());
	
	for(unsigned i(0); i<degree.size(); i++) {
		unsigned int value = degree[i] - 1;
		total += value;
		
		if(check){	
			if(!visited[value]){
				degree_nodes[value] += to_string(i);
				visited[value]=true;
			} 
			else{
				degree_nodes[value] += " " + to_string(i);
			}
		}
	}

	for(string level: degree_nodes) {
		if(level.empty()){
			break;
		}
		cout << level << endl;
	}
	check = false;
	return total;
	}




