#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
ifstream f("input.in");

//mat=matricea arcelor
//nr_nod=numarul nodurilor
//nr_tranz=numarul tranziilor
//stare_in=starea initiala
//nf=numar stari finale
//stare_fin=vectorul starilor finale
//ni=numarul cuvintelor
//cuv=matricea cuvintelor

struct arc //structura pentru memorarea tranzitiilor
    {
        int n1,n2;
        char litera;
    }mat[100];

int nr_nod, nr_tranz,stare_in,nf,stare_fin[100],ni,stiva[100],vf,valid,varf;
char cuv[100][100];

void citire_fisier()//citeste automatul din fisier
{
    int i;
    f>>nr_nod>>nr_tranz;
    for(i=0; i<=nr_tranz-1; i++)
        f>>mat[i].n1>>mat[i].n2>>mat[i].litera;
    f>>stare_in;
    f>>nf;
    for(i=0; i<=nf-1; i++)
        f>>stare_fin[i];
    f>>ni;
    for(i=0; i<=ni-1; i++)
        f>>cuv[i];
}

int cauta(int nod, int v[], int l) //functia cauta un element intr-un vector de intregi de lungime l
{
    for(int i=0;i<l;i++)
        if(nod==v[i])
            return 1;
    return 0;
}

void afn(int stare,char cuv[])
{
//daca cuvantul nu mai are litere si starea se gaseste printre cele finale, atunci cuvantul e acceptat
    if(strlen(cuv)==0 && cauta(stare,stare_fin,nf)==1)
        {
            valid=1;
            stiva[vf]=stare;
            vf++;
            varf=vf;
        }
    else
//daca cuvantul mai are litere, verific unde pot pleca din starea curenta cu prima litera din cuvant si apelez recursiv functia afn
    if(strlen(cuv)>0 && valid==0)
 {
            int ok=0;
            for(int k=0;k<nr_tranz;k++)
            {
                if(mat[k].litera==cuv[0] && mat[k].n1==stare)
                {
                    ok=1;
                    stiva[vf]=stare;
                    vf++;
                    int x=vf;
                    afn(mat[k].n2,cuv+1);
                    vf=x-1;
                }

            }
            if(ok==0)
                    vf--;
}
}
int main()
{
   citire_fisier();//citeste automatul
   for(int i=0; i<=ni-1; i++) //pentru fiecare cuvant, cuvantul curent=cuv[i]
    {
        valid=0;
        for(int j=0;j<nr_tranz;j++)
        {
            vf=0;
            if(mat[j].n1==stare_in && mat[j].litera==cuv[i][0]) //verifica unde poate sa plece din starea initiala cu prima litera din cuvant
            {
                stiva[vf]=stare_in;
                vf++;
                afn(mat[j].n2,cuv[i]+1); //pt fiecare nod gasit apeleaza functia afn(nod bun, cuvantul fara prima litera)
            }
        }

        if(valid==1)
            {
            cout<<"DA"<<endl;
            cout<<"Traseu: ";
            for(int x=0;x<varf;x++)
                cout<<stiva[x]<<" ";
            cout<<endl;
            }
        else
            cout<<"NU"<<endl;
        if(strlen(cuv[i])==0 && cauta(stare_in,stare_fin,nf)==1)
        {
            valid=1;
            cout<<"DA Traseu: "<<stare_in<<" ";
        }
    }
    return 0;
}

