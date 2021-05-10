#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;
ifstream f("gram_reg.in");
string tranz[10000]; //retin tranzitiile pe parcurs
int n;
unordered_map<string, vector<string>> mp; //retin input-ul

int nrterm(int y) //functie care calculeaza numarul de terminale
{
    int nr=0;
    for (int i=0; i<=y; i++)
    {   if(tranz[i][0]!='N')
            if(tranz[i]!="#")
                nr++;
    }
    return nr;
}

void afisterm(int m) //functie care afiseaza terminalele
{   for (int i=0; i<=m; i++)
        if(tranz[i][0]!='N' && tranz[i][0]!='#')
            cout<<tranz[i][0]<<" ";
        cout<<"\n";
}

void bkt(int k) //functie backtracking pentru gasirea solutiilor
{
    if(tranz[k - 1][0]=='N' && nrterm(k-1)<= n) //cazul in care pe un nivel din tranz este un neterminal si nu am ajuns la nr de litere dorit
            for(int i=0; i<mp[tranz[k-1]].size(); i++)
            {
                tranz[k]=mp[tranz[k-1]][i];
                bkt(k+1);
            }
        if(tranz[k-1].length()>=2 && nrterm(k-1)<=n) //cazul in care pe un nivel din tranz este o litera + un neterminal si
                                                     //nu am ajuns la nr de litere dorit
            if(tranz[k-1][1]=='N')
            {
                for(int i=0; i<mp[tranz[k-1].substr(1,2)].size(); i++)
                {
                    tranz[k]=mp[tranz[k-1].substr(1,2)][i];
                    bkt(k+1);
                }
            }
    if (nrterm(k-1)==n && tranz[k-1].find('N')==std::string::npos) //cazul in care am ajuns la numarul de litere dorit si nu este un neterminal
            afisterm(k - 1); //afisam cuvantul
}

int main()
{
    string a, b;
    while (f>>a>>b) //citesc din fisier
        mp[a].push_back(b); //si completez map-ul
    cout<<"n= ";
    cin>>n;
    tranz[0]="NS"; //marchez in tranz punctul de plecare
    bkt(1); //apelez functia de backtracking
    return 0;
}

