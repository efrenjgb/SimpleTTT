#include <stdio.h>
#include <string.h>

int analyze_board(char *node, int side)
{	
	if(node[0]==side&&node[1]==side&&node[2]==side||
		node[3]==side&&node[4]==side&&node[5]==side||
		node[6]==side&&node[7]==side&&node[8]==side)
		return 1;

	if(node[0]==side&&node[3]==side&&node[6]==side||
		node[1]==side&&node[4]==side&&node[7]==side||
		node[2]==side&&node[5]==side&&node[8]==side)
		return 1;

	if(node[0]==side&&node[4]==side&&node[8]==side||
		node[2]==side&&node[4]==side&&node[6]==side)
		return 1;

	if(node[0]==-side&&node[1]==-side&&node[2]==-side||
	node[3]==-side&&node[4]==-side&&node[5]==-side||
	node[6]==-side&&node[7]==-side&&node[8]==-side)
		return -1;

	if(node[0]==-side&&node[3]==-side&&node[6]==-side||
		node[1]==-side&&node[4]==-side&&node[7]==-side||
		node[2]==-side&&node[5]==-side&&node[8]==-side)
		return -1;

	if(node[0]==-side&&node[4]==-side&&node[8]==-side||
		node[2]==-side&&node[4]==-side&&node[6]==-side)
		return -1;

	for(int i=0;i<9;i++)
		if(node[i]==0)
			return -2;

	return 0;
}

int negamax(char *node, int depth, int side, int top)
{
	int cb = analyze_board(node, side);

	if(depth == 0 || cb != -2)
		return cb;

	int bestScore = -2;
	int bestMove = -2;
	int v;

	for(int i=0;i<9;i++)
	{
		if(node[i] != 0)
			continue;

		node[i] = side;
		v = -negamax(node, depth - 1, -side, 0);
		node[i] = 0;

		if(v >= bestScore)
		{
			bestScore = v;
			bestMove = i;
		}		
	}

	if(top)
		return bestMove;
	else
		return bestScore;
}

int get_move(char *node, int side)
{
	return negamax(node, 9, side, 1);
}

int game_over(char *board)
{
	if(analyze_board(board, 1)>-2)
		return 1;
	else
		return 0;
}

void print_board(char *board)
{
	printf("\n\n");
	int row = 0;
	for(int i=1;i<10;i++)
	{
		if(board[i-1]==1) printf(" x "); else if(board[i-1]==-1) printf(" o "); else printf("   "); 
		if(i%3==0&&i!=0&&i!=9) 
		{
			if(row==0) printf("\t 0 | 1 | 2");
			if(row==1) printf("\t 3 | 4 | 5");

			printf("\n-----------\t-----------\n");
			row++;
		}
		else if(i!=9)	printf("|");
	}
	if(row==2) printf("\t 6 | 7 | 8");
	printf("\n\n");
}

int main()
{
	char board[9];

	char win_msg[3][20] = {"Player O wins!\n\n", "Game is a draw!\n\n", "Player X wins!\n\n"};

	memset(board, 0, 9);

	int side=1, pos;

	while(!game_over(board))
	{
		print_board(board);
		printf("Enter move: ");
		scanf("%d", &pos);

		board[pos] = side;

		if(game_over(board))
			break;

		int move = get_move(board, -side);

		board[move] = -side;
	}

	print_board(board);

	int who = analyze_board(board, 1);

	printf("%s", win_msg[who+1]);

	return 0;
}