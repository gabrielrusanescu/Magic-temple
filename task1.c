#include "utils.h"

int cuvintea(char *n)
{
    if(n[0]!='a')
        return -1;
    int v[4],i=0;
    while(i<4)
    {
        v[i]=n[i+1]-'0';
        i++;
    }
    int max1=maxi(v[0],v[1]),max2=maxi(v[2],v[3]);
    max1=maxi(max1,max2),i=0;
    while(i<4){
        if(v[i]==max1){
            return i+1;
        }
        i++;
    }
}

int cuvinteb(char *n)
{
    if(n[0]!='b')
        return -1;
    int k=0,x=0;
    for(int i=1; n[i]!='\0'; i++)
    {
        k=k*10+(n[i]-'0');
    }
    x=k%100;
    int pal=palindrom(k),pr=prim(x);
    if(pal && pr)
        return 3;
    else if(pal && !pr)
        return 1;
    else if(!pal && pr)
        return 2;
    else return 4;
}


int cuvintec(char *sir)
{
    if(sir[0]!='c')
        return -1;
    int n=sir[1]-'0',k=sir[2]-'0';
    int v[n],i=0,s=0,cnt=0,rest;
    for(int j=3; sir[j]!='\0'; j++,i++) v[i]=sir[j]-'0';
    i=0;
    while(cnt<k)
    {
        if(i>=n)
            i=i%n;
        s+=v[i];
        cnt++,i+=k;
    }
    rest=s%4;
    if(rest==0)
        return 3;
    else if(rest==1)
        return 2;
    else if(rest==2)
        return 1;
    else if(rest==3)
        return 4;
}

int main()
{
    int n,m;
    scanf("%d %d ",&n,&m);
    char coduri[10][10];
    int mat[10][10]={0},iactual=0,jactual=0,poz=1,nrlinii=0; mat[0][0]=1;
    char cod[100];
    fgets(cod,100,stdin);
    char *p=strtok(cod," ");
    while(p)
    {
        strcpy(coduri[nrlinii],p);
        int next;
        if(coduri[nrlinii][0]=='a')
            next=cuvintea(coduri[nrlinii]);
        else if(coduri[nrlinii][0]=='b')
            next=cuvinteb(coduri[nrlinii]);
        else if(coduri[nrlinii][0]=='c')
            next=cuvintec(coduri[nrlinii]);
        else continue;
        if(next==1) jactual++;
        else if(next==2) iactual--;
        else if(next==3) jactual--;
        else if(next==4) iactual++;
        nrlinii++,poz++,mat[iactual][jactual]=poz;
        p=strtok(NULL, " ");
    }

    for(int i=0; i<n; i++, printf("\n"))
        for(int j=0; j<m; j++)
            printf("%d ",mat[i][j]);
    return 0;
}
