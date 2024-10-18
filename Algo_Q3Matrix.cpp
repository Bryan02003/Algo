#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void AdjMatrix(int node, vector<vector<int>>& adjMatrix,vector<bool>& visited, vector<pair<int, int>>& treeEdge, int n)
{
    visited[node] = true;

    for(int i =0;i<n;i++) // Parcours des sommets adjacents
    {
        if(adjMatrix[node][i] && !visited[i])
        {
            treeEdge.push_back({node + 1, i+1}); // Ajout de l'arête à l'arbre couvrant
            AdjMatrix(i, adjMatrix, visited, treeEdge,n); // Appel récursif pour visiter le sommet adjacent
        }
    }
}

int main()
{
    ifstream infile("INPARBGRAPH.TXT");
    ofstream outfile("OUTARBGRAPH.TXT");

    int n,m;

    infile >> n >> m; // lecture du nombre de sommets et d'arêtes

    vector<vector<int>> adjMatrix(n, vector<int>(n,0)); // Matrices d'adjacence initialisée à 0

    for(int i=0;i<m;i++) // Lecture des arêtes du fichier
    {
        int u, v;
        infile >> u >> v;
        adjMatrix[u-1][v-1] = 1;
        adjMatrix[v-1][u-1]=1; // Graphe non orienté
    }

    vector<bool> visited(n, false);
    vector<pair<int, int>> treeEdges;

    AdjMatrix(0, adjMatrix,visited,treeEdges, n);

    for(auto edge:treeEdges)
    {
        outfile << edge.first << " " <<edge.second << endl;
    }


    infile.close();
    outfile.close();

    return 0;
}