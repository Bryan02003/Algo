#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

//using namespace std;

std::vector<std::pair<int,int>> findLIS(const std::vector<int>& A)
{
    int n=A.size(); 
    std::vector<int> dp(n,1); //stocke la valeur de la sous séquence croissante la plus longue
    std::vector<int> prev(n,-1); //stocke l'indice de l'elt précédent de la sous séquence
    int max_len=1,max_idx=0; //max_len stocke la long de la ssc trouvée et max_idx stocke l'ind de la fin de la ss

    for(int i=1;i<n;i++)
    {
        for(int j=0;j<i;j++)
        {
            if(A[j]<A[i] && dp[i]<dp[j]+1)
            {
               dp[i]=dp[j]+1;
               prev[i]=j; 
            }
        }
        if(dp[i]>max_len)
        {
            max_len = dp[i];
            max_idx = i;
        }
    }

    std::vector<std::pair<int, int>> lis;
    int current_idx = max_idx;
    while (current_idx != -1)
    {
        lis.push_back({A[current_idx], current_idx + 1});
        current_idx=prev[current_idx];
    }

    reverse(lis.begin(), lis.end()); //reverse les élements de la liste
    return lis;

}

int main()
{
    std::ifstream infile("INPMONOSEQ.TXT"); //Ouvre le fichier d'entrée
    std::ofstream outfile("OUTMONOSEQ.TXT"); //Ouvre le fichier de sortie

    if(!infile.is_open() || !outfile.is_open())
    {
        std::cerr<<"Erreur d'ouverture des fichiers."<< std::endl;
        return 1;
    }

    int n;
    infile >> n;
    std::vector<int> A(n);

    for(int i=0;i<n;i++)
    {
        infile>>A[i];
    }

    std::vector<std::pair<int,int>> lis=findLIS(A);

    outfile << lis.size() << std::endl;

    // if(lis.empty())
    // {
    //     cerr << "Erreur : La sous-séquence est vide" << endl;
    //     return 1;
    // }

    for(const auto& elem : lis)
    {  
        outfile <<  "a[" << elem.second << "] = "<< elem.first << std::endl;
    }

    infile.close();
    outfile.close();

    return 0;
}

