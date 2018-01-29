#include <mpi.h>
#include <bits/stdc++.h>
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

const int N = 4;
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++){
        for (int col = 0; col < n; col++){
            if (row != p && col != q){
                temp[i][j++] = A[row][col];
                if (j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 
int determinant(int A[N][N], int n)
{
    int D = 0; // Initialize result
    if (n == 1)
        return A[0][0];
 
    int temp[N][N]; // To store cofactors
    int sign = 1;  // To store sign multiplier
    for (int f = 0; f < n; f++)
    {
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}
 
void adjoint(int A[N][N],int adj[N][N], int start, int end)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    int sign = 1, temp[N][N];
 
    for (int i=start; i<end; i++)
    {
        for (int j=0; j<N; j++)
        {
            getCofactor(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}
 
void display(int A[N][N])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
            cout << A[i][j] << " ";
        cout << endl;
    }
}


int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init (&argc, &argv);      /* starts MPI */
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        /* get current process id */
	MPI_Comm_size (MPI_COMM_WORLD, &size);        /* get number of processes */
	int A[N][N] = { {5, -2, 2, 7},
                    {1, 0, 0, 3},
                    {-3, 1, 5, 0},
                    {3, -1, -9, 4}};
 	int stride = max((N)/(size),1); 
 	cout<<stride<<"dsojgad\n";
	int ADJ[N][N];  // To store adjoint of A[][]
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			ADJ[i][j] = 0;
			/* code */
		}
		/* code */
	}
    float INV[N][N]; // To store inverse of A[][]
	int det = determinant(A, N);
	// cout<<count1<<" ";
	if(rank==0){
	    if (det == 0){
	        cout << "Singular matrix, can't find its inverse";
	        return 0;
	    }
		int row_end;
		cout<<"out of scandf\n";
 		int nlast = N;
    	int row_number_start = 0;
	    for(int i = 1; i < size; i++){
	    	if(i!=size-1){
		 		MPI_Send(&row_number_start,1,MPI_INT,i,1,MPI_COMM_WORLD);
		 		row_end = row_number_start + stride; 
		 		MPI_Send(&row_end,1,MPI_INT,i,2,MPI_COMM_WORLD);
	    	}
	    	else{
		 		MPI_Send(&row_number_start,1,MPI_INT,i,1,MPI_COMM_WORLD);
		 		MPI_Send(&nlast,1,MPI_INT,i,2,MPI_COMM_WORLD);
	    	}
	 		row_number_start += stride;
	    }
	    int flags;
		for (int i = 1; i < size; i++){
			MPI_Recv(&flags,1,MPI_INT,i,i,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			cout<<"confirmation received by: "<<i<<"\n";
 		} 		
		for (int i=0; i<N; i++){
	        for (int j=0; j<N; j++){
	            INV[i][j] = ADJ[i][j]/float(det);
	        	cout<<ADJ[i][j]<<" ";
	        }
	        cout<<"\n";
	    }
	}
	else{
		int Start,myrank;
		int End;
		MPI_Recv(&Start,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&End,1,MPI_INT,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		cout << "luls" << rank << " " << Start << " " << End << endl;
		adjoint(A, ADJ, Start, End);
		int done = 1;
		MPI_Comm_rank (MPI_COMM_WORLD, &myrank);
		MPI_Send(&done,1,MPI_INT,0,myrank,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	
	return 0;
}