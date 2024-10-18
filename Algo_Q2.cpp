#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Subsequence
{
    int length;
    int sum;
    vector<int> elements;
};

int main()
{
    ifstream infile("INPDIVSEQ.TXT");
    ofstream outfile("OUTDIVSEQ.TXT");

    int n,k;

    infile >> n >> k;
    vector<int> a(n);

    for(int i=0;i<n;i++)
    {
        infile >> a[i];
    }

    vector<Subsequence> dp(k, {0,0,{}}); //Stocke la sous-séquence la plus longue avec une somme ayant un reste r

    for(int i=0;i<n; i++)
    {
        vector<Subsequence> new_dp = dp; 

        for(int r=0;r<k;r++)
        {
            int new_r = (r+a[i])%k;

            if(dp[r].length+1 > new_dp[new_r].length)
            {
                new_dp[new_r].length=dp[r].length+1;
                new_dp[new_r].sum = dp[r].sum + a[i];
                new_dp[new_r].elements= dp[r].elements;
                new_dp[new_r].elements.push_back(a[i]);
            }
        }

        int new_r = a[i]%k;

        if(new_dp[new_r].length==0 || new_dp[new_r].length<1)
        {
            new_dp[new_r].length=1;
            new_dp[new_r].sum=a[i];
            new_dp[new_r].elements = {a[i]};    
        }

        dp =new_dp;
    }

        Subsequence result = dp[0];

        outfile << result.length << endl;

        for(int i=result.elements.size()-1;i>=0;i++)
        {
            outfile << "a[" <<find(a.begin(), a.end(), result.elements[i])-a.begin()+1 << "] = " << result.elements[i] << endl;
        }

        outfile <<"Sum = "<< result.sum << endl;

        infile.close();
        outfile.close();   


    return 0;
}