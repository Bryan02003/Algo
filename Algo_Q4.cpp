#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void AdjMatrix(int node, vector<vector<int>>&adjMatrix,vector<bool>& visited, vector<int>& component, int n)
{
    visited[node] = true;
    component.push_back(node + 1); // Ajout de l'arête à l'arbre couvrant

    for(int i =0;i<n;i++) // Parcours des sommets adjacents
    {
        if(adjMatrix[node][i] && !visited[i])
        {
            AdjMatrix(i, adjMatrix, visited, component,n); // Appel récursif pour visiter le sommet adjacent
        }
    }
}

int main()
{
    ifstream infile("INPCONGRAPH.TXT");
    ofstream outfile("OUTCONGRAPH.TXT");

    int n,m;

    infile >> n >> m; // lecture du nombre de sommets et d'arêtes

    vector<vector<int>> adjMatrix(n, vector<int>(n,0)); // Matrices d'adjacence initialisée à 0

    for(int i=0;i<m;i++) // Lecture des arêtes du fichier
    {
        int u, v;
        infile >> u >> v;
        adjMatrix[u-1][v-1]=1;
        adjMatrix[v-1][u-1]=1; // Graphe non orienté
    }

    vector<bool> visited(n, false);
    vector<vector<int>> components; //Utile pour stocker toutes less composantes connexes

    for(int i=0;i<n;i++)
    {
        if(!visited[i])
        {
            vector<int> component; //Stockage de la composante courante
            AdjMatrix(i,adjMatrix,visited,component,n);
            components.push_back(component); //Ajout de la composante dans la liste des composantes
        }
    }

    outfile << components.size() << endl; // Affichagde du nombre de composantes connexes

    for(int i=0;i<components.size();i++) //Ecriture des composantes connexes
    {
        outfile << "composante connexe " << i+1 << endl;
        for(int j : components[i])
        {
            outfile << j << " ";
        }
        outfile << endl;
    }


    infile.close();
    outfile.close();

    return 0;
}