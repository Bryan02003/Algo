#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

void AdjList(int node, vector<list<int>> &adjList, vector<bool> &visited, vector<pair<int, int>> &treeEdge)
{
    visited[node] = true;

    for (int n : adjList[node]) // Parcours des sommets adjacents
    {
        if (!visited[n])
        {
            treeEdge.push_back({node + 1, n + 1});  // Ajout de l'arête à l'arbre couvrant
            AdjList(n, adjList, visited, treeEdge); // Appel récursif pour visiter le sommet adjacent
        }
    }
}

int main()
{
    ifstream infile("INPARBGRAPH.TXT");
    ofstream outfile("OUTARBGRAPH.TXT");

    int n, m;

    infile >> n >> m; // lecture du nombre de sommets et d'arêtes

    vector<list<int>> adjList(n); // Matrices d'adjacence initialisée à 0

    for (int i = 0; i < m; i++) // Lecture des arêtes du fichier
    {
        int u, v;
        infile >> u >> v;
        adjList[u - 1].push_back(v - 1);
        adjList[v - 1].push_back(u - 1); // Graphe non orienté
    }

    vector<bool> visited(n, false);
    vector<pair<int, int>> treeEdges; // arêtes de l'arbre couvrant

    AdjList(0, adjList, visited, treeEdges);

    for (auto edge : treeEdges)
    {
        outfile << edge.first << " " << edge.second << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}