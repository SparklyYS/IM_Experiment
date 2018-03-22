#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iostream>
#include "graph.h"

const string res_file = "res.txt";
const int MAXN = 11;
const int LIMIT = 10000;

vector<double> vec[MAXN];
void CalculateSum(Graph &g, int idx);

string attr_file;  // the attribute file contain nodes and edges
string graph_file; // the graph file contain the graph
int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] == string("-help") || argv[i] == string("-h") || argc == 1)
        {
            cout << "./main -attr *** -graph ***" << endl;
            exit(-1);
        }
        if (argv[i] == string("-attr"))
        {
            attr_file = argv[i + 1];
        }
        if (argv[i] == string("-graph"))
        {
            graph_file = argv[i + 1];
        }
    }
    Graph graph(attr_file);
    cout << "begin to read Graph..." << endl;
    graph.readGraph(graph_file);
    cout << "readGraph Over..." << endl;

    cout << "begin to init vec...." << endl;
    for (int i = 0; i < MAXN; i++)
    {
        for (int j = 0; j < graph.n; j++)
        {
            vec[i].push_back(0);
        }
    }
    cout << "init vec Over..." << endl;

    double start, finish;
    start = clock();
    for (int i = 0; i < graph.n; i++)
    {
        double probSum = 0;
        for (int j = 0; j < graph.gT[i].size(); j++)
        {
            probSum += graph.probT[i][j];
        }
        vec[0][i] = probSum;
    }

    for (int i = 1; i < MAXN - 1; i++)
    {
        CalculateSum(graph, i);
    }
    finish = clock();
    cout << "totoal time: " << (finish - start) / CLOCKS_PER_SEC << "s" << endl;

    for (int i = 0; i < graph.n; i++)
    {
        vec[MAXN - 1][i] = 0;
        for (int j = 0; j < MAXN - 1; j++)
        {
            vec[MAXN - 1][i] += vec[j][i];
        }
    }

    int snode; // sample node
    srand((unsigned int)time(NULL));
    for (int i = 0; i < LIMIT; i++)
    {
        while (true)
        {
            snode = rand() % (graph.n);
            if (vec[MAXN - 1][snode] != 0)
                break;
        }
        cout << snode << ": " << vec[MAXN - 1][snode] << " ";
        for (int j = 0; j < MAXN - 1; j++)
        {
            cout << vec[j][snode] / vec[MAXN - 1][snode] << " ";
        }
        cout << endl;
    }

    return 0;
}

void CalculateSum(Graph &g, int idx)
{
    for (int i = 0; i < g.n; i++)
    {
        double probSum = 0;
        for (int j = 0; j < g.gT[i].size(); j++)
        {
            int adj_vert = g.gT[i][j];
            probSum += (g.probT[i][j] * vec[idx - 1][adj_vert]);
        }
        vec[idx][i] = probSum;
    }
}