#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>


void deleteBoard(int** board, const int& N) {
	for (int i = 0; i < N; i++)
		delete[] board[i];
	delete[] board;
}

void PrintBoard(int** board, const int &N, const int &M) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}

int CountPossibleMoves(int** board, const int& N, const int& M) {
	int sum = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (board[i][j] == 0) sum++;
		}
	}
	return sum;
}

void GenerateAllPositions(int** board, const int& N, const int& M, const int &activePlayer) {
	printf("%d", CountPossibleMoves(board, N, M));
	printf("\n");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (board[i][j] == 0) {
				board[i][j] = activePlayer;
				PrintBoard(board, N, M);
				board[i][j] = 0;
			}
		}
	}
}

bool CheckForWinning(int** board, const int& N, const int& M, const int& K, int activePlayer) {

	//check rows
	int sum = 1;

	for (int i = 0; i < N; ++i) {
		sum = 1;
		for (int j = 0; j < M - 1; ++j) {
			if (board[i][j] == board[i][j+1] && board[i][j] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}

	//check columns
	for (int i = 0; i < M; ++i) {
		sum = 1;
		for (int j = 0; j < N - 1; ++j) {
			if (board[j][i] == board[j+1][i] && board[j][i] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}

	//check diagonal
	for (int start = 0; start < M-1; start++) {
		sum = 1;
		for (int i = 0, j = start; i < N - 1 && j < M - 1; i++, j++) {
			if (board[i][j] == board[i + 1][j + 1] && board[i][j] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}
	
	for (int start = 0; start < M - 1; start++) {
		sum = 1;
		for (int i = start, j = 0; i < N - 1 && j < M - 1; i++, j++) {
			if (board[i][j] == board[i + 1][j + 1] && board[i][j] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}
	
	for (int start = M - 1; start > 0; start--) {
		sum = 1;
		for (int i = 0, j = start; i < N - 1 && j > 0; i++, j--) {
			if (board[i][j] == board[i + 1][j - 1] && board[i][j] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}
	
	for (int start = N - 1; start > 0; start--) {
		sum = 1;
		for (int i = start, j = M - 1; i < N - 1 && j > 0; i++, j--) {
			if (board[i][j] == board[i + 1][j - 1] && board[i][j] == activePlayer) sum++;
			else sum = 1;
			if (sum == K) return true;
		}
	}
	
	return false;
}

int WhoWon(int** board, const int& N, const int& M, const int& K) {
	/*
	-1 - gra w toku
	0 - remis
	1 - 1 wygral
	2 - 2 wygral
	*/
	if (CheckForWinning(board, N, M, K, 1)) return 1;
	if (CheckForWinning(board, N, M, K, 2)) return 2;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (board[i][j] == 0) return -1;
		}
	}
	return 0;
}

int getSecondPlayer(const int &activePlayer) {
	if (activePlayer == 1) return 2;
	else return 1;
}

int max(const int& x, const int& y) {
	if (x > y) return x;
	else return y;
}

int min(const int& x, const int& y) {
	if (x < y) return x;
	else return y;
}

int minimax(int** board, int depth, bool isMax, const int& N, const int& M, const int& K, const int& activePlayer)
{		
	int score = WhoWon(board, N, M, K);

	if (score == 0)
		return 0;
	if (score == activePlayer)
		return 1;
	if (score == getSecondPlayer(activePlayer))
		return -1;

	if (isMax)
	{
		int best = -1000;
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				if (board[i][j] == 0)
				{
					board[i][j] = activePlayer;					
					best = max(best,minimax(board, depth + 1, !isMax,N,M,K,activePlayer));					
					board[i][j] = 0;
				}
			}
		}
		return best;
	}	
	else
	{
		int best = 1000;
		
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{				
				if (board[i][j] == 0)
				{					
					board[i][j] = getSecondPlayer(activePlayer);
					best = min(best, minimax(board, depth + 1, !isMax,N,M,K,activePlayer));					
					board[i][j] = 0;
				}
			}
		}
		return best;
	}
}

bool CheckAllForWinning(int** board, const int& N, const int& M, const int& K, const int& activePlayer) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			if (board[i][j] == 0) {
				board[i][j] = activePlayer;
				if (CheckForWinning(board, N, M, K, activePlayer)) {
					printf("1\n");
					PrintBoard(board, N, M);
					return true;
				}
				else {
					board[i][j] = 0;
				}				
			}
		}
	}
	return false;
}

int main() {
	int N, M, K;
	char command[50] ;
	while (true) {
		scanf("%s", &command);
		if (feof(stdin) != 0)
		{
			break;
		}
		if (!strcmp(command,"GEN_ALL_POS_MOV")) {
			int activePlayer;
			scanf("%i %i %i %i", &N, &M, &K, &activePlayer);			
			int** board = new int* [N];
			for (int i = 0; i < N; ++i)
				board[i] = new int[M];
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					scanf("%i", &board[i][j]);
				}
			}
			int secondPlayer;
			if (activePlayer == 1) secondPlayer = 2;
			else secondPlayer = 1;
			if (CheckForWinning(board,N,M,K,activePlayer) || CheckForWinning(board,N,M,K,secondPlayer)) {
				printf("0\n");
				deleteBoard(board, N);
			}
			else {
				GenerateAllPositions(board, N, M, activePlayer);
				deleteBoard(board, N);
			}
		}
		if (!strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
			int activePlayer;
			scanf_s("%i %i %i %i", &N, &M, &K, &activePlayer);
			int** board = new int* [N];
			for (int i = 0; i < N; ++i)
				board[i] = new int[M];
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					scanf("%d", &board[i][j]);
				}
			}
			int secondPlayer;
			if (activePlayer == 1) secondPlayer = 2;
			else secondPlayer = 1;
			if (CheckForWinning(board, N, M, K, activePlayer) || CheckForWinning(board, N, M, K, secondPlayer)) {
				printf("0\n");
				deleteBoard(board, N);
			}
			else {
				if (!CheckAllForWinning(board, N, M, K, activePlayer)) {
					GenerateAllPositions(board, N, M, activePlayer);
					deleteBoard(board, N);
				}				
			}
		}
		if (!strcmp(command, "SOLVE_GAME_STATE")) {
			int activePlayer;
			scanf_s("%i %i %i %i", &N, &M, &K, &activePlayer);
			int** board = new int* [N];
			for (int i = 0; i < N; ++i)
				board[i] = new int[M];
			for (int i = 0; i < N; ++i) {
				for (int j = 0; j < M; ++j) {
					scanf("%d", &board[i][j]);
				}
			}
			int result = minimax(board, 0, true, N, M, K, activePlayer);
			if (result == 0) printf("BOTH_PLAYERS_TIE\n");
			else if ((result == 1 && activePlayer == 1) || (result == -1 && activePlayer == 2)) printf("FIRST_PLAYER_WINS\n");
			else printf("SECOND_PLAYER_WINS\n");
			deleteBoard(board, N);
		}
	}
	return 0;
}