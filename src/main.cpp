#include "head.h"
#include "graph.h"
#include "ganalyze.h"

const string res_file = "res.txt";


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
    cout << "begin to read Graph..." << endl;
    Graph graph(attr_file, graph_file);
    cout << "readGraph Over..." << endl;

    cout << "begin to init vec...." << endl;
    Ganalyze ganalyze(graph);
    cout << "init vec Over..." << endl;
    
    cout << "start analyzing..." << endl;
    ganalyze.AnalyzeProb(graph);
    cout << "end analyzing..." << endl;
    
    ganalyze.SampleNode(graph);

    return 0;
}

