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

const int N = 100;
// const int NN;
int det;
int nsize;
// int count1 = 0;
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
    int D = 0; 
    if (n == 1)
	    return A[0][0];
    int temp[N][N]; 
    int sign = 1;  
    for (int f = 0; f < n; f++){
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);
        sign = -sign;
    }
    return D;
}
 
void adjoint(int A[N][N],int adj[N][N], int start, int end, int n)
{
    if (n == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[N][N];
    for (int i=start; i<end; i++){
        for (int j=0; j<n; j++){
            getCofactor(A, temp, i, j, n);
            sign = ((i+j)%2==0)? 1: -1;
            int deter = (determinant(temp, n-1));
            adj[i][j] = (sign)*(deter);
        }
    }
}

int main(int argc, char* argv[]){
	int rank, size;
	MPI_Init (&argc, &argv);      
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);        
	MPI_Comm_size (MPI_COMM_WORLD, &size);        
    int row_number_start = 0;
	int ADJ[N][N];
	for (int i = 0; i < N; ++i){
		for (int j = 0; j < N; ++j){
			ADJ[i][j] = 0;
		}
	}
    float INV[N][N]; 
	int A[N][N];
	if(rank==0){
		din(size_of_matrix);
		nsize = size_of_matrix;
		for(int i = 0; i < size_of_matrix; i++)
		{
			for (int j = 0; j < nsize; ++j)
			{
				cin>>A[i][j];
			}
		}
 		int stride = max(nsize/(size-1),1); 
		// cout << "det" << endl;
		det = determinant(A, nsize);
		// cout << det << endl;
	    if (det == 0){
	        cout << "Singular matrix, can't find its inverse";
	        return 0;
	    }
		int row_end;
 		int nlast = nsize;
	    for(int i = 1; i < size; i++){
	    	MPI_Send(&nsize,1,MPI_INT,i,0,MPI_COMM_WORLD);
	    	if(i!=size-1){
		 		MPI_Send(&row_number_start,1,MPI_INT,i,1,MPI_COMM_WORLD);
		 		row_end = row_number_start + stride; 
		 		MPI_Send(&row_end,1,MPI_INT,i,2,MPI_COMM_WORLD);
	    	}
	    	else{
		 		MPI_Send(&row_number_start,1,MPI_INT,i,1,MPI_COMM_WORLD);
		 		MPI_Send(&nlast,1,MPI_INT,i,2,MPI_COMM_WORLD);
	    	}
	    	for(int j = 0; j < nsize; j++){
		    	MPI_Send(&A[j],nsize,MPI_INT,i,3,MPI_COMM_WORLD);
		    	// cout<<"sent is: "<<A[j][0]<<"\n";
	    	}
	 		row_number_start += stride;
	    }
	    int flags;
	    int START=0,END=stride;
	    for (int i = 1; i < size; ++i)
	    {
	    	if(i==size-1){
	    		END = nsize;
	    	}
	    	for(int j = START; j<END; j++){
	    		// cout << "AT j: " << j << "0: start: "<< START << "end: "<< END<<"\n";
	    		MPI_Recv(&ADJ[j], nsize, MPI_FLOAT, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	    	}
	    	START = END;
	    	END = START + stride;
	    	/* code */
	    }
	    // trace(det);
	    // cout<<"Inverse of given matrix is: "<<"\n";
        cout<<setprecision(2);
		for (int i=0; i<nsize; i++){
	        for (int j=0; j<nsize; j++){
	            INV[i][j] = float(ADJ[j][i]/float(det));
	        	cout<<INV[i][j]<<" ";
	        }
	        cout<<"\n";
	    }
	}
	else{
		int Start;
		int End;
		// int nn = 4;
		int nsize;
		MPI_Comm_rank (MPI_COMM_WORLD, &rank);
		MPI_Recv(&nsize,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&Start,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&End,1,MPI_INT,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		// cout<<nsize<<"dsfadwf\n";
		for(int j = 0; j < nsize; j++){
	    	MPI_Recv(&A[j],nsize,MPI_INT,0,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	    	// cout<<"at rank: " << rank << "val: "<<A[j][0]<<"\n";
    	}
		// cout << "luls" << rank << " " << Start << " " << End << endl;
		adjoint(A, ADJ, Start, End, nsize);
		for(int i=Start;i<End;i++){
			MPI_Send(&ADJ[i], nsize, MPI_FLOAT, 0, i, MPI_COMM_WORLD);
		}
		// MPI_Send(&End,1,MPI_INT,0,3,MPI_COMM_WORLD);
	}
	MPI_Finalize();
	// for (int i=0; i<N; i++){
	//         for (int j=0; j<N; j++){
	//             INV[i][j] = ADJ[i][j]/float(det);
	//         	cout<<INV[i][j]<<" ";
	//         }
	//         cout<<"\n";
	//     }
	return 0;
}