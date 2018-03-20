#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class Graph
{
  public: 
    int n, m; 
    vector< vector<int> > gT;
    vector< vector<double> > probT;

  public:
    Graph() {}

    Graph(string attr)
    {
        readNM(attr);
        for (int i = 0; i < n; i++)
        {
            gT.push_back(vector<int>());
            probT.push_back(vector<double>());
        }
    }

    void readNM(string attr)
    {
        ifstream in(attr.c_str());
        in >> n >> m;
        cout << "n = " << n << endl;
        cout << "m = " << m << endl;

        in.close();
    }

    void add_edge(int u, int v, double p)
    {
        gT[u].push_back(v);
        probT[u].push_back(p);
    }

    void readGraph(string graph_file)
    {
        ifstream in(graph_file.c_str());

        int u, v;
        double p;
        for (int i = 0; i < m; i++)
        {
            in >> u >> v >> p;
            add_edge(u, v, p);
        }
        in.close();
    }
};
#endif