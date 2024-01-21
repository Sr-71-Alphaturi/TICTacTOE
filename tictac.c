#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int p1=0;
static int p2=0;
char p11[15],p22[15];
char * c = "\
        88\n\
  ,d    \"\"              ,d                            ,d\n\
  88                    88                            88\n\
MM88MMM 88  ,adPPYba, MM88MMM ,adPPYYba,  ,adPPYba, MM88MMM ,adPPYba,  ,adPPYba, \n\
  88    88 a8\"     \"\"   88    \"\"     `Y8 a8\"     \"\"   88   a8\"    \"8a  a8P_____88 \n\
  88    88 8b           88    ,adPPPPP88 8b           88   8b       d8 8PP\"\"\"\"\"\"\"\n\
  88,   88 \"8a,   ,aa   88,   88,    ,88 \"8a,   ,aa   88,  \"8a,   ,a8\" \"8b,   ,aa\n\
  \"Y888 88  `\"Ybbd8\"'   \"Y888 `\"8bbdP\"Y8  `\"Ybbd8\"'   \"Y888  \"YbbdP\"'   `\"Ybbd8\"' \n";
char board[3][3];

void create_resetleaderboard()
{
    FILE* p= fopen("leaderboard.txt","w");
    fprintf(p,"%s %d\n","Player 1",0);
    fprintf(p,"%s %d\n","Player 2",0);
    fclose(p);
}
void update_leaderboard(int winner)
{
    FILE* p;
    if(winner==1)
        p1++;
    else
        p2++;
    p= fopen("leaderboard.txt","w");
    fprintf(p,"%s : %d\n",p11,p1);
    fprintf(p,"%s : %d\n",p22,p2);
    fclose(p);
}
void showleaderboard()
{
    FILE* p= fopen("leaderboard.txt","r"); 
    if(p==NULL)
        return;
    char x[10];
    while(fgets(x,10,p) != NULL)
        printf("%s",x);
    fclose(p);
}
void showboard()
{   printf("\n\n");
    for(int i=0; i<3;i++)
    {
        printf("  %c  |  %c  |  %c  \n",board[i][0],board[i][1],board[i][2]);
        if(i!=2)
            printf("-----------------\n");
    }
    printf("\n\n");
}
void makeboard()
{
    for(int i=0;i<3;i++){
        for(int j=0; j<3; j++){
            board[i][j] = ' ';
        }
    }
    showboard();
}
void intmakeboard()
{
    char x='1';
    for(int i=0;i<3;i++){
        for(int j=0; j<3; j++){
            board[i][j] = x++;
        }
    }
    showboard();
}
void update_board(int player){
    char x[10];
    if(player==1)
        strcpy(x,p11);
    else
        strcpy(x,p22);
    char sym[] = {' ','X','O'};
    int position,flag=1;
    do{  
    printf("Enter your choice %s : ",x);
    scanf("%d",&position);
    int row=(position-1)/3;
    int col = (position-1) %3;  
    if(board[row][col] == ' ')
    {
        board[row][col] = sym[player];
        flag=0;
    }
    else if(position>9 || position<1) {printf("Enter a valid position which is between 1 and 9.\n");}
    else
        printf("Invalid position as it is already filled.\n");
    }while(flag==1);
    showboard();
}
int chkwin(char psign)
{
    int winner=-1;
    if(psign=='X')
        winner=1;
    else if(psign=='O')
        winner=2;
    if(board[0][0] == psign && board[0][1] == psign && board[0][2] == psign ||
      board[1][0] == psign && board[1][1] == psign && board[1][2] == psign ||
      board[2][0] == psign && board[2][1] == psign && board[2][2] == psign)
      {
        return winner;
      }
    else if(board[0][0] == psign && board[1][0] == psign && board[2][0] == psign ||
      board[0][1] == psign && board[1][1] == psign && board[2][1] == psign ||
      board[0][2] == psign && board[1][2] == psign && board[2][2] == psign)
      {
        return winner;
      }
    else if(board[0][0] == psign && board[1][1] == psign && board[2][2] == psign ||
           board[0][2] == psign && board[1][1] == psign && board[2][0] == psign)
    {
        return winner;
    }
    return -1;
}
void playgame()
{
    int player_no,choice_end,winner;
    char psign;
    makeboard();
    for(int i=0;i<9;i++)
    {
        if(i%2==0)
            {player_no=1;psign='X';}
        else
            {player_no=2;psign='O';}
        update_board(player_no);
        winner = chkwin(psign);
        if(winner==1)
        {
            printf("The winner is %s.\n", p11);
            update_leaderboard(winner);
            break;
        }
        else if(winner==2)
        {
            printf("The winner is %s.\n", p22);
            update_leaderboard(winner);
            break;
        }   
    }
    if(winner==-1){
        printf("It's a draw!!!!");
    }   
    printf("Do You want to play again ? \n1. Yes\n2. No\nEnter your choice : ");
    scanf("%d",&choice_end);
    if(choice_end==2)
    {
        printf("The final score is \n\n");
        showleaderboard();
        exit(1);
    }
        
    else{
        playgame();
        system("clear");
    }      
}
void intropage()
{
    int ch;
    printf("%s",c);
    printf("________________________________________________________________________________\n");
    printf("________________________________________________________________________________\n\n");
    printf("\t\t\t\t\t\t\tCreated By - Soumya Jain\n\n");
    printf("________________________________________________________________________________\n");
    printf("________________________________________________________________________________\n\n");
    printf("Guide Lines : \nThe numbers 1-9 represent the board in the following way :\n ");
    intmakeboard();
    printf("Do you want to see the previous scoreboard ? \n1. Yes\n2. No\n");
    printf("Enter your choice : ");
    scanf("%d",&ch);
    if(ch==1){
        printf("\nPrevious scores were : \n");
        showleaderboard();
    }
    printf("To begin press 1, to exit press 0...");
    int cho;
    scanf("%d",&cho);
    if(cho==1){
    create_resetleaderboard();
    printf("Enter name of P1 : ");
    scanf("%s",p11);
    printf("Enter name of P2 : ");
    scanf("%s",p22);
    }
    else
        exit(1);
}
int main(){
    intropage();
    playgame();
    return 0;
}