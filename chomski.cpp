#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;
const int N=4;
int det;
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n){
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
int determinant(int A[N][N], int n){
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
void adjoint(int A[N][N], int adj[N][N], int start, int end, int row){
    if (N == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1, temp[N][N];
    for (int i=start; i<=end; i++){
        for (int j=0; j<row; j++){
            getCofactor(A, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            int xd = determinant(temp, N-1);
            adj[i][j] = (sign)*(xd);
        }
    }
}
void display(int A[N][N]){
	cout << "The Inverse is : \n";
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++)
            cout << (float)(A[j][i]/(det)) << " ";
        cout << endl;
    }
}
int main(int argc, char* argv[]){
    int rank, size,fl=0;
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
	int ADJ[N][N];
	int A[N][N] = { {5, -2, 2, 7},
                    {1, 0, 0, 3},
                    {-3, 1, 5, 0},
                    {3, -1, -9, 4}};

    det = determinant(A,N);
    int row=4;
    if(rank == 0){
    	if(det == 0) {cout << "Inverse does not exist\n";return 0;}
    	int flag, subDivide = max((row/size), 1);
    	int start = 0, end = start+subDivide;
    	for(int i=1;i<size;i++){
    		if(i == size - 1) end = row-1; 
    		MPI_Send(&start, 1, MPI_INT, i, 1e5, MPI_COMM_WORLD);
    		MPI_Send(&end, 1, MPI_INT, i, 2e5, MPI_COMM_WORLD);
    		start = end+1;
    		end = start + subDivide;
    	}
    	start=0,end=start+subDivide;
    	for(int i=1;i<size;i++){
    		if(i == size-1) end = row-1;
    		for(int j=start;j<=end;j++)
    			MPI_Recv(&ADJ[j], row, MPI_FLOAT, i, j, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    		start = end + 1;
    		end = start + subDivide;
    	}
	    display(ADJ);
   	}
	else {
		int rank, flag;
		int start, end;
	    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
		MPI_Recv(&start, 1, MPI_INT, 0, 1e5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(&end, 1, MPI_INT, 0, 2e5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		adjoint(A, ADJ, start, end,row);
		for(int i=start;i<=end;i++){
			MPI_Send(&ADJ[i], row, MPI_FLOAT, 0, i, MPI_COMM_WORLD);
		}
	}
    MPI_Finalize();
    return 0;
}