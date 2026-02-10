#include "utils.h"

int main()
{
    int d;
    char metoda[15],sir[30],decriptat[30];
    scanf("%d %s",&d,metoda);
    if(d!=2)
        return -1;
    if(strcmp(metoda,"caesar")==0)
    {
        int cheie;
        scanf("%d %s",&cheie,sir);
        int i;
        for(i=0; sir[i]!='\0'; i++)
        {
            if(sir[i]>='a' && sir[i]<='z') decriptat[i]=((sir[i]-'a'-(cheie%26)+26)%26)+'a';
            else if(sir[i]>='A' && sir[i]<='Z') decriptat[i]=((sir[i]-'A'-(cheie%26)+26)%26)+'A';
            else if(sir[i]>='0' && sir[i]<='9') decriptat[i]=((sir[i]-'0'-(cheie%10)+10)%10)+'0';
            else decriptat[i]=sir[i];
        }
        decriptat[i]='\0';
        printf("%s",decriptat);
    }
    else if(strcmp(metoda,"vigenere")==0)
    {
        char cheie[300];
        scanf("%s %s",cheie,sir);
        int len1=strlen(cheie),len2=strlen(sir);
        int dif=len2-len1,multiplicator=len2/len1 + 1;
        if(dif>0)
        {
            int i=0;
            char aux[30];
            strcpy(aux,cheie);
            while(i<multiplicator)
            {
                strcat(cheie,aux);
                i++;
            }
        }
        int i;
        for(i=0; sir[i]!='\0' ; i++)
        {
            int k=cheie[i]-'A';
            if(sir[i]>='a' && sir[i]<='z') decriptat[i]=((sir[i]-'a'-k+26)%26)+'a';
            else if(sir[i]>='A' && sir[i]<='Z') decriptat[i]=((sir[i]-'A'-k+26)%26)+'A';
            else if(sir[i]>='0' && sir[i]<='9') decriptat[i]=((sir[i]-'0'-(k%10)+10)%10)+'0';
            else decriptat[i]=sir[i];
        }
        decriptat[i]='\0';
        printf("%s",decriptat);
    }
    else if(strcmp(metoda, "addition")==0)
    {
        int cheie,nr1=0,nr2=0;
        char numar1[20], numar2[20],numar1dec[20],numar2dec[20];
        scanf("%d %s %s",&cheie,numar1,numar2);
        for(int i=0; numar1[i]!='\0';i++) numar1dec[i]=((numar1[i]-'0'-(cheie%10)+10)%10)+'0';
        for(int i=0; numar2[i]!='\0';i++) numar2dec[i]=((numar2[i]-'0'-(cheie%10)+10)%10)+'0';
        numar1dec[strlen(numar1)]='\0',numar2dec[strlen(numar2)]='\0';
        for(int i=0; numar1[i]!='\0';i++) nr1=nr1*10+(numar1dec[i]-'0');
        for(int i=0; numar2[i]!='\0';i++) nr2=nr2*10+(numar2dec[i]-'0');
        printf("%d",nr1+nr2);
    }
    return 0;
}
