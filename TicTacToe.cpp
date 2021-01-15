#include<bits/stdc++.h>

#define SUCCESSFUL 5000
#define FAILURE -5000
#define DRAW 0
#define BLANK '-'

using namespace std;
char COMP_MARKER,USER_MARKER;

//Return all possible moves
vector<int> AvailableBox(char board[9])
{
	vector<int> AvlBox;
	int i=0;
	while(i!=9)
	{
		if(board[i]==BLANK)
			AvlBox.push_back(i);
		i++;
	}
	return AvlBox;
}


// Required box to win
vector<vector<int>> DesireBox
{
	{ 0,1,2 },{ 3,4,5 },{ 6,7,8 },
	{ 0,3,6 },{ 1,4,7 },{ 2,5,8 },
	{ 0,4,8 },{ 6,4,2 }

};



// Return all the box no. that are occupied with the marker
vector<int> FilledBox(char board[9], char marker)
{
	vector<int> filled_box;
	int i=0;
	while(i!=9)
	{
			if(marker==board[i])
				filled_box.push_back(i);
			i++;
	}
	return filled_box;
}


// Check the box
bool isFilled(char board[9],int pos)
{

    if(board[pos]!=BLANK)
	    return true;
	else
	    return false;
}

//Return opponent marker
char GetOppMark(char marker)
{
	char OppMrk;
	if(marker==COMP_MARKER)
		OppMrk = USER_MARKER;
	else
		OppMrk = COMP_MARKER;
	return OppMrk;
}


// Game has won or not
bool IsWon(vector<int> occu)
{
    bool f=false;
    for(int i=0;i<DesireBox.size();i++)
    {
        for(int k=0;k<3;k++)
        {
            for(int j=0;j<occu.size();j++)
            {
                if(occu[j]==DesireBox[i][k])
                {
                    f=true;
                    if(k==2)
                        return true;
                    break;
                }
                else
                    f=false;
            }
            if(!f)
                break;
        }
        if(i==DesireBox.size()-1)
            return false;
    }

}

// Board is full or not
bool IsBoardFull(char board[9])
{
	vector<int> avl_box = AvailableBox(board);

	if(avl_box.size()!=0)
		return false;
	else
		return true;
}

// won or lost
int BoardState(char board[9], char marker)
{
	char OppoMrk = GetOppMark(marker);
	vector<int> occup_box = FilledBox(board, marker);

	bool is_won = IsWon(occup_box);
	if(is_won)
		return SUCCESSFUL;
	occup_box = FilledBox(board, OppoMrk);
	bool is_lost = IsWon(occup_box);

	if(is_lost)
		return FAILURE;
	bool is_full = IsBoardFull(board);
	if(is_full)
		return DRAW;
	return DRAW;
}
// game is finished or not
bool game_done(char board[9])
{
	if(IsBoardFull(board))
		return true;
	if(DRAW!=BoardState(board,USER_MARKER))
		return true;
	return false;
}
// MiniMax algo
pair<int,int> minimax(char board[9], char marker, int depth, int alpha, int beta)
{
	int best_move = -1;
	int best_score = (marker == COMP_MARKER) ? FAILURE : SUCCESSFUL;


	if(IsBoardFull(board) || DRAW != BoardState(board, COMP_MARKER))
	{
		best_score = BoardState(board, COMP_MARKER);
		return make_pair(best_score, best_move);
	}

	vector<int> leg_moves = AvailableBox(board);

	for(int i=0; i<leg_moves.size(); i++)
	{
		int current_move = leg_moves[i];
		board[current_move] = marker;


		if(marker==COMP_MARKER)
		{
			int score = minimax(board, USER_MARKER, depth + 1, alpha, beta).first;


			if(best_score<score)
			{
				best_score = score - depth * 10;
				best_move = current_move;

				alpha = max(alpha, best_score);
				board[current_move] = BLANK;
				if(beta<=alpha)
				{
					break;
				}
			}

		}
		else
		{
			int score = minimax(board, COMP_MARKER, depth + 1, alpha, beta).first;

			if(best_score>score)
			{
				best_score = score + depth * 10;
				best_move = current_move;

				beta = min(beta, best_score);
				board[current_move] = BLANK;
				if(beta<=alpha)
				{
					break;
				}
			}

		}

		board[current_move] = BLANK;

	}

	return make_pair(best_score, best_move);
}
void print(char board[9])
{

    cout<<"******************************\n";
	cout<<"          "<<board[0] <<"   " <<board[1] <<"   " <<board[2] <<"\n";
	cout<<"          "<<board[3] <<"   " <<board[4] <<"   " <<board[5] <<"\n";
	cout<<"          "<<board[6] <<"   " <<board[7] <<"   " <<board[8] <<"\n";
    cout<<"******************************\n\n";

}
int main()
{

	char want='y',f1='y';
    char input;

	while(want=='y' || want=='Y')
    {
        char board[9] = { '1','2','3','4','5','6','7','8','9' };

        	cout<<"\n\n             **HELLO USER!!!**\n***WELCOME TO OUR REAL-TIME TIC TAC TOE GAME***\n\n\n";
    while(f1=='y')
    {
        f1='n';
        cout<<"WHICH MARKER DO YOU WANT TO PREFER ? 'X' OR '0'? ";
        cin>>input;
        cout<<"\n";
        if(input=='X')
        {
            COMP_MARKER='0';
            USER_MARKER='X';
        }
        else if(input=='0')
        {
            COMP_MARKER='X';
            USER_MARKER='0';
        }
        else
        {
            cout<<"**PLEASE CHOOSE A CORRECT MARKER !!!**\n\n\n"  ;
            f1='y';
        }
    }

        	print(board);

        	for(int i=0; i<9; i++)
                board[i]='-';

        	while(!game_done(board))
        	{
        		int box;
        		cout<<"CHOOSE THE POSITION NUMBER OF THE 3X3 GRID : ";
        		cin>>box;
        		if( box>9 || box<1 )
                {
                    cout<<"\n**WRONG INPUT !!..PLEASE CHOOSE BETWEEN 1 TO 9(BOTH INCLUSIVE)**\n\n\n";
                    continue;
                }
        		box--;
        		cout<<"\n";

        		if(isFilled(board,box))
        		{
        			cout<<"**THE POSTION IS OCCUPIED. PLEASE TRY ANOTHER ONE..!!!**\n\n\n\n" ;
        			continue ;
        		}
        		else
        			board[box] = USER_MARKER;
        		pair<int,int> ai_move = minimax(board, COMP_MARKER, 0, FAILURE, SUCCESSFUL);

        		board[ai_move.second] = COMP_MARKER;
        		print(board);
    	    }

    	cout<<"\n\n********** GAME OVER **********\n\n" ;

    	int player_state = BoardState(board, USER_MARKER);

    	if(player_state==SUCCESSFUL)
    	    cout<<"**CONGRATULATIONS !! YOU WON THE GAME**";
    	else if(player_state==FAILURE)
    	    cout<<"**SORRY!! YOU LOST THE GAME**";
    	else if(player_state==DRAW)
    	    cout<<"**OOPS !! THE GAME IS DRAW**";
    	want='x';
    	while(!(want=='y' || want=='Y' || want=='n' || want=='N'))
        {

        	cout<<"\n\n\nDO YOU WANT TO RESTART THE GAME ?[y/n]: ";
        	cin>>want;
            if(!(want=='y' || want=='Y' || want=='n' || want=='N'))
                cout<<"\n**PLEASE ENTER THE CORRECT KEY!!!**";
        }
    }
	return 0;
}
