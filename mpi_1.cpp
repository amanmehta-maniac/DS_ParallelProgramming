#include <mpi.h>
#include <bits/stdc++.h>
#include <stdlib.h> 
using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector<long long>     VLL;
typedef vector< VI >    VVI;
typedef long long int   LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))


#define din(n) int n; scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define llin(n) long long n; scanf("%lld",&n)
#define llout(n) printf("%lld\n",n)
#define strin(s,l) char s[l]; scanf("%s",s)
#define strout(n) printf("%s\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;
 
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
 
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init (&argc, &argv);      /* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
	if(rank==0){
		din(N);
		int n = N;
		int * original = (int*) malloc(N*sizeof(int));
		// int * final = (int*) malloc(N*sizeof(int));
		for(int i = 0; i < n; i++){
			cin>>original[i];
		}
		int stride = max(1,N/(size-1));
		int start = 0;
		int end = stride  + start;
		int * sorted = (int*) malloc(N*sizeof(int));
		for(int i = 1; i < size; i++){
			if(start >= N){
				int gar1=-1;
				MPI_Send(&gar1,1,MPI_INT,i,i,MPI_COMM_WORLD);
			}
			else{
				if(i==size-1 || end>=N) {
					end = N;
				}
				int sz = end - start;
				MPI_Send(&sz,1,MPI_INT,i,i,MPI_COMM_WORLD);
				for(int j = start; j < end; j++){
					int temp = original[j];
					MPI_Send(&temp,1,MPI_INT,i,i,MPI_COMM_WORLD);
				}
			}
			start += stride;
			end = start + stride;
		}
		int it = 0;
		start = 0; end = stride;
		for(int i = 1; i < size; i++){
			if(start >= N){
				break;
			}
			if(i==size-1 || end>=N){
				end = N;
			}
			int sz = end - start;
			for(int j = 0; j < sz; j++){
				int temp;
				MPI_Recv(&temp, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sorted[it++] = temp;
				// cout<<"received: "<<temp<<" ";
			}
			start += stride;
			end = start + stride;
		}
		// cout<<"all subarrays sorted\n";
		mergeSort(sorted,0,N-1);
		for(int i = 0; i < N; i++){
			cout<<sorted[i]<<" ";
		}
		cout<<endl;
	}
	else{
		int sz;
		int myrank;
		MPI_Comm_rank (MPI_COMM_WORLD, &myrank);

		MPI_Recv(&sz, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		if(sz > 0){
			int sub[sz];
			for(int i = 0; i < sz; i++){
				int temp;
				MPI_Recv(&temp, 1, MPI_INT, 0, myrank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				sub[i] = temp;
			}
			// cout<<"size: "<<sz<<endl;
			// cout<<"sorting section\n";
			for(int i = 0; i < sz ; i++){
				// cout<<sub[i]<<" ";
			}
			// cout<<"after sorting \n";
			mergeSort(sub,0,sz-1);
			for (int i = 0; i < sz; ++i)
			{
				int temp = sub[i];
				MPI_Send(&temp,1,MPI_INT,0,0,MPI_COMM_WORLD);
				// cout<<sub[i]<<" ";
				/* code */
			}
			// cout<<endl;
		}
	}
	MPI_Finalize();
	return 0;
}