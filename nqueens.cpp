#include <bits/stdc++.h>
using namespace std;
#define MAXN 30

//N, board, queens's positions
int N, board[MAXN][MAXN];
int pi[MAXN], pj[MAXN];

//adjacent cells
int di[8] = { 0, -1, -1, -1,  0,  1, 1, 1};
int dj[8] = { 1,  1,  0, -1, -1, -1, 0, 1};

//check if a position is valid to place a queen
bool validPos(int i, int j) {
	if (i < 0 || j < 0 || i >= N || j >= N) return false;
	return board[i][j] == 0;
}

//cost is the number of pairs that collide
int computeCost() {
	int ans = 0;
	
	//iterate over all queens
	for(int q1=1; q1<=N; q1++) {
		for(int q2=1; q2<q1; q2++) {
			//same row
			if (pi[q1] == pi[q2]) ans++;
			
			//same column
			if (pj[q1] == pj[q2]) ans++;

			//same 45 diagonal
			if (pi[q1]-pj[q1] == pi[q2]-pj[q2]) ans++;
			
			//same -45 diagonal
			if (pi[q1]+pj[q1] == pi[q2]+pj[q2]) ans++;
		}
	}
	return ans;
}

//print the board
void printboard() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%c", board[i][j] != 0 ? 'Q' : '.');
		}
		printf("\n");
	}
}

bool nqueens(int _N, bool prt) {
	N = _N;
	//clear board
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			board[i][j] = 0;
		}
	}
	
	//place n queens at random locations
	for(int q=1; q<=N; q++) {
		int i, j;
		
		//try a position until a valid one is found
		do {
			i = rand()%N;
			j = rand()%N;
		} while(!validPos(i, j));
		
		//place queen
		board[i][j] = q;
		pi[q] = i;
		pj[q] = j;
	}
	
	//optimal adjacent states
	vector<int> mq, mdi, mdj;
	
	//iterate until a minimum state is reached
	while(true) {
		
		//print current state
		if (prt) {
			printf("Current state, cost = %d:\n", computeCost());
			printboard();
		}
		
		//compute cost of all posible adjacent states, get minimum
		int minc = N*N;
		mq.clear();
		mdi.clear();
		mdj.clear();
		
		//try all queens q
		for(int q=1; q<=N; q++) {
			int i, j;
			
			//at queen q, try all possible adjacent cells
			for(int k=0; k<8; k++) {
				for(int m=1; m<8; m++) {
					if (!validPos(pi[q]+m*di[k], pj[q]+m*dj[k])) continue;
					
					//swicth queen place, compute cost and switch back
					pi[q] += m*di[k];
					pj[q] += m*dj[k];
					int ncost = computeCost();
					pi[q] -= m*di[k];
					pj[q] -= m*dj[k];
					
					//if a better cost is found, reset adjacent states
					if (ncost < minc) {
						mq.clear();
						mdi.clear();
						mdj.clear();
						minc = ncost;
					}
					
					//add adjacent state
					if (ncost == minc) {
						mq.push_back(q);
						mdi.push_back(m*di[k]);
						mdj.push_back(m*dj[k]);
					}
				}
			}
		}
		
		//if a move is not optimal, break
		if (minc >= computeCost()) break;
		
		//print optimal move
		int nxt = rand()%mq.size();
		int oq = mq[nxt];
		int odi = mdi[nxt];
		int odj = mdj[nxt];
		if (prt) {
			printf("move queen at (%d,%d) to (%d,%d)\n\n", pi[oq]+1, pj[oq]+1, pi[oq]+odi+1, pj[oq]+odj+1);
		}
		
		//move state
		swap(board[pi[oq]][pj[oq]], board[pi[oq]+odi][pj[oq]+odj]);
		pi[oq] += odi;
		pj[oq] += odj;
		
		//if optimal state found, break
		if (minc == 0) break;
	}
		
	//print final state
	if (prt) {
		printf("Final state, cost = %d:\n", computeCost());
		printboard();
	}
	
	//return wether or not an optimal position was reached
	return computeCost() == 0;
}

int main() {
	
	//random seed based on system time
	srand(time(NULL));
	
	//test cases
	int sz[5] = {8, 10, 15, 20, 25};
	for(int i=0; i<5; i++) {
		
		//measure start time
		clock_t dt = clock();
		
		//try until success
		while(!nqueens(sz[i], false));
		
		//measure end time
		dt = clock() - dt;
		
		//print result
		printf("Solution found, N = %d, time = %.6f s:\n", sz[i], dt * 1.0 / CLOCKS_PER_SEC);
		printboard();
	}
	return 0;
}