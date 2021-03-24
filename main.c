#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

void reorganiza(int vetor[],int copia[],int n)
{
    for(int i=0;i<n;i++)
    {
        copia[i]=vetor[i];
    }
}

void print(float Tempo[])
{
    printf("\n\n");
    printf("\n\tTempo Selection Sort: %.1f Ms",Tempo[0]);
    printf("\n\tTempo Insertion Sort: %.1f Ms",Tempo[1]);
    printf("\n\tTempo Merge Sort: %.1f Ms",Tempo[2]);
    printf("\n\tTempo Quick Sort: %.1f Ms",Tempo[3]);
    printf("\n\tTempo Heap Sort: %.1f Ms\n\n",Tempo[4]);
    system("pause");


    // 0 SelectionSort
    // 1 InsertionSort
    // 2 MergeSort
    // 3 QuickSort
    // 4 HeapSort
}

void validacao(int vetor[], int n, int escolha)
{
    int flag=0;
    int i;
    for(i=0;i<n;i++)
    {
        if(i==0)
        {
            if(vetor[i]>vetor[i+1])
            {
                flag=1;
                break;
            }
        }
        else if(i==n-1)
        {
            if(vetor[i]<vetor[i-1])
            {
                flag=1;
                break;
            }
        }
        else
        {
            if(vetor[i-1]>vetor[i] || vetor[i]>vetor[i+1])
            {
                flag=1;
                break;
            }
        }
    }

    if(flag==0)
    {
        switch(escolha)
        {
            case(0):
                printf("\n\tSelection Sort Valido");
                break;
            case(1):
                printf("\n\tInsertion Sort Valido");
                break;
            case(2):
                printf("\n\tMerge Sort Valido");
                break;
            case(3):
                printf("\n\tQuick Sort Valido");
                break;
            case(4):
                printf("\n\tHeap Sort Valido");
                break;
        }
    }
    else
    {
        switch(escolha)
        {
            case(0):
                printf("\n\tSelection Sort Invalido");
                break;
            case(1):
                printf("\n\tInsertion Sort Invalido");
                break;
            case(2):
                printf("\n\tMerge Sort Invalido");
                break;
            case(3):
                printf("\n\tQuick Sort Invalido");
                break;
            case(4):
                printf("\n\tHeap Sort Invalido");
                break;
        }
    }
}



float SelectionSort(int vetor[], int n)
{
    clock_t tinicio,tfinal;
    float tdec;
    tinicio=clock();
    int menor,aux=0;
    for(int i=0;i<n;i++)
    {
        menor=i;
        for(int j=i+1;j<n;j++)
        {
            if(vetor[j]<vetor[menor])
                menor=j;
        }
        aux=vetor[i];
        vetor[i]=vetor[menor];
        vetor[menor]=aux;
    }
    tfinal=clock();
    tdec=(float)((tfinal-tinicio)/(CLOCKS_PER_SEC/1000));
    return tdec;
}

float InsertionSort(int vetor[], int n)
{
    clock_t tinicio,tfinal;
    float tdec;
    tinicio=clock();
    int aux=0;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j>0;j--)
        {
            if(vetor[j]<vetor[j-1])
            {
                aux=vetor[j];
                vetor[j]=vetor[j-1];
                vetor[j-1]=aux;
            }
            else
                break;
        }

    }
    tfinal=clock();
    tdec=(float)((tfinal-tinicio)/(CLOCKS_PER_SEC/1000));
    return tdec;
}

void Merge(int vetor[],int aux[], int lo, int hi, int mid)
{
    for(int i=lo;i<=hi;i++)
    {
        aux[i]=vetor[i];
    }
    int j=lo,k=mid+1;
    for(int i=lo;i<=hi;i++)
    {
        if(j>mid)
            vetor[i]=aux[k++];
        else if(k>hi)
            vetor[i]=aux[j++];
        else if(aux[k]<aux[j])
            vetor[i]=aux[k++];
        else
            vetor[i]=aux[j++];
    }
}

void MSort(int vetor[],int aux[], int lo, int hi)
{
    int mid;
    if(hi<=lo)
        return;
    mid=lo+((hi-lo)/2);
    MSort(vetor,aux,lo,mid);
    MSort(vetor,aux,mid+1,hi);
    Merge(vetor,aux,lo,hi,mid);
}


float MergeSort(int vetor[],int n)
{
    clock_t tinicio,tfinal;
    float tdec;
    tinicio=clock();

    int *aux;
    aux =(int *)malloc(n* sizeof(int));
    MSort(vetor,aux,0,n-1);

    tfinal=clock();
    tdec=(float)((tfinal-tinicio)/(CLOCKS_PER_SEC/1000));
    return tdec;
}

void swap(int vet[], int pos1, int pos2)
{
    int aux;
    aux=vet[pos1];
    vet[pos1]=vet[pos2];
    vet[pos2]=aux;
}

void shuffle(int vetor[],int n)
{
    int random;
    for(int i=0;i<n;i++)
    {
        random=rand() % n;
        swap(vetor,i,random);
    }
}

int QuickSortP(int vetor[], int lo, int hi)
{
	int i, j;
	i = lo;
	j = hi+1;

    while(true)
    {
        while(vetor[++i]<vetor[lo])
        {
            if(i==hi)
                break;
        }
        while(vetor[lo]<vetor[--j])
        {
            if(j==lo)
                break;
        }
        if(i>=j)
            break;
        swap(vetor,i,j);
    }
    swap(vetor,lo,j);
    return j;
}

void SortQ(int vetor[], int lo, int hi)
{
	int j;
	if (hi <= lo)
		return;
	j = QuickSortP(vetor, lo, hi);
	SortQ(vetor, lo, j-1);
	SortQ(vetor,j+1,hi);
}

float QuickSort(int vetor[], int n)
{
    clock_t tinicio,tfinal;
    float tdec;
    tinicio=clock();

    shuffle(vetor,n);
    SortQ(vetor,0,n-1);

    tfinal=clock();
    tdec=(float)((tfinal-tinicio)/(CLOCKS_PER_SEC/1000));
    return tdec;
}

void sink(int vetor[], int n, int i)
{
    int pai=i, filho_e=2*i+1, filho_d=2*i+2;
    if (filho_e<n && vetor[filho_e]>vetor[pai])
        pai=filho_e;

    if (filho_d<n && vetor[filho_d]>vetor[pai])
        pai=filho_d;

    if (pai!= i)
    {
        swap(vetor,i,pai);
        sink(vetor,n,pai);
    }
  }

float HeapSort(int vetor[], int n)
{
    clock_t tinicio,tfinal;
    float tdec;
    tinicio=clock();

    for (int i= n/2-1; i>=0; i--)
        sink(vetor,n,i);

    for (int i=n-1; i>=0; i--)
    {
        swap(vetor,0,i);
        sink(vetor, i, 0);
    }

    tfinal=clock();
    tdec=(float)((tfinal-tinicio)/(CLOCKS_PER_SEC/1000));
    return tdec;

}


int main()
{
    int n;
    int *vetor,*aux;
    float tdec[5];

    do{
        system("cls");
        printf("\n\tQuantos valores deseja inserir no vetor?\n\t[1]-10\n\t[2]-100\n\t[3]-1000\n\t[4]-10000\n\t[5]-100000\n\t[6]-1000000\n\t[7]-Sair\n\t--:");
        scanf(" %d",&n);
    }while(n<1 || n>7);
    if(n==7)
    {
        return 0;
    }
    else
        n=round(pow(10,n));

    vetor =(int *)malloc(n* sizeof(int));
    aux =(int *)malloc(n* sizeof(int));

    int i=0;
    for(i=0;i<n;i++)
    {
        vetor[i]=rand()%100;
        aux[i]=vetor[i];
    }

    // 0 SelectionSort
    // 1 InsertionSort
    // 2 MergeSort
    // 3 QuickSort
    // 4 HeapSort

    tdec[0]=SelectionSort(aux,n);
    validacao(aux,n,0);

    reorganiza(vetor,aux,n);
    tdec[1]=InsertionSort(aux,n);
    validacao(aux,n,1);

    reorganiza(vetor,aux,n);
    tdec[2]=MergeSort(aux,n);
    validacao(aux,n,2);

    reorganiza(vetor,aux,n);
    tdec[3]=QuickSort(aux,n);
    validacao(aux,n,3);

    reorganiza(vetor,aux,n);
    tdec[4]=HeapSort(aux,n);
    validacao(aux,n,4);


    print(tdec);


    main();
}
