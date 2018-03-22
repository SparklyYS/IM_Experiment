#include <ctime>
#include <cmath>
#include <vector>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include "sfmt/SFMT.h"

using namespace std;
double uniformRand();
double normalRand(double mean, double sigma);

const int maxn = 3200000;

vector<int> nodes[maxn];
int inDeg[maxn];

string infile;
int flag; // flag 0 1/d probability each| flag 1 random probability each | flag 2 normal random probability each

int main(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        if (argv[i] == string("-help") || argv[i] == string("-h") || argc == 1)
        {
            cout << "./format -dataset *** -flag ***" << endl;
            exit(-1);
        }
        if (argv[i] == string("-dataset"))
        {
            infile = argv[i + 1];
        }
        if (argv[i] == string("-flag"))
        {
            flag = atoi(argv[i + 1]);
        }
    }
    const string attrfile = "../attribute.txt";
    const string outfile = "../graph_file.inf";

    ifstream in(infile.c_str());
    int n, m; // n: number of nodes | m: number of edges
    int u, v;

    in >> n >> m;
    for (int i = 0; i < m; i++)
    {
        in >> u >> v;
        nodes[u].push_back(v);
        inDeg[v]++;
    }
    in.close();

    ofstream attrout(attrfile.c_str());
    ofstream out(outfile.c_str());

    sfmt_t sfmt;

    attrout << n << " " << m << endl;
    if (flag == 0)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < nodes[i].size(); j++)
            {
                int adj_vert = nodes[i][j];
                double prob = 1.0 / inDeg[adj_vert]; // generate the probability as 1/d
                out << i << " " << adj_vert << " " << prob << endl;
            }
        }
    }
    else if (flag == 1)
    {
        sfmt_init_gen_rand(&sfmt, 96532);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < nodes[i].size(); j++)
            {
                double prob = sfmt_genrand_real1(&sfmt); // generate the probability between [0, 1)
                out << i << " " << nodes[i][j] << " " << prob << endl;
            }
        }
    }
    else
    {
        double mean = 0.5, sigma = 0.2;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < nodes[i].size(); j++)
            {
                srand((unsigned int)time(NULL));
                double prob = normalRand(mean, sigma);
                out << i << " " << nodes[i][j] << " " << prob << endl;
            }
        }
    }
    attrout.close();
    out.close();

    return 0;
}

double uniformRand()
{
    return ((double)rand() + 1.) / ((double)(RAND_MAX) + 1.);
}

//return general normal distribution N~(mean, sigma*sigma)
double normalRand(double mean, double sigma)
{
    double u1 = uniformRand();
    double u2 = uniformRand();
    double X = cos(8 * atan(1.) * u2) * sqrt(-2 * log(u1));
    return sigma * X + mean;
}