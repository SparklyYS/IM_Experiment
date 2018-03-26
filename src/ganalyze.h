#ifndef GANALYZE_H
#define GANALYZE_H

#include "head.h"

class Ganalyze
{
    vector< vector<double> > vec;

    // constructor
  public:
    Ganalyze() {}

    Ganalyze(Graph g)
    {
        for (int i = 0; i < MAXN; i++)
        {
            vec.push_back(vector<double>(g.n, 0));
        }
    }

  private:
    // 计算累积和
    inline void CalculateSum(Graph g, int idx)
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

    // function
  public:
    // 分析Graph中的传播概率随着跳数的变化
    void AnalyzeProb(Graph g)
    {
        double start, finish;
        start = clock();
        for (int i = 0; i < g.n; i++)
        {
            double probSum = 0;
            for (int j = 0; j < g.gT[i].size(); j++)
            {
                probSum += g.probT[i][j];
            }
            vec[0][i] = probSum;
        }

        for (int i = 1; i < MAXN - 1; i++)
        {
            CalculateSum(g, i);
        }
        finish = clock();
        cout << "totoal time: " << (finish - start) / CLOCKS_PER_SEC << "s" << endl;

        for (int i = 0; i < g.n; i++)
        {
            vec[MAXN - 1][i] = 0;
            for (int j = 0; j < MAXN - 1; j++)
            {
                vec[MAXN - 1][i] += vec[j][i];
            }
        }
    }

    // 采样 LIMIT 个结点输出 MAXN-1 跳的结果
    void SampleNode(Graph g)
    {
        int snode; // sample node
        srand((unsigned int)time(NULL));
        for (int i = 0; i < LIMIT; i++)
        {
            // 舍弃累积和为0的结点, 重新选择
            while (true)
            {
                snode = rand() % (g.n);
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
    }
};

#endif
