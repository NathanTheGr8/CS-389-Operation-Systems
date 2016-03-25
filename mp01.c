#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h> 

//Global Varibles
int player_turn = 0;
int random_target_number = 0;
bool won = false;

typedef struct
{
       int passes_left;
       bool justPassed;
} Player;

Player p1;
Player p2;

//Methods from bottom
void player_number();
void set_random_player_turn();
void set_random_target_number();
bool player_takes_turn(Player* player);
void change_player_turn();
 
int main()
{
   set_random_player_turn();
   set_random_target_number();

   printf("%d\n",player_turn );
   printf("%d\n",random_target_number );

   while (!won){
      change_player_turn();
      printf("The Player Turn is :%d\n",player_turn);
      player_number();
      if (player_turn == 1){ //player 1's turn
         won = player_takes_turn(&p1);
      }
      else { //player 2's turn
         won = player_takes_turn(&p2);
      }
   }
   

}

void player_number(){
   bool flag = true;
   while (flag){
      printf("Enter Player Number\n");
      int input;
      scanf("%d", &input);

      if (input == player_turn){
         flag = false;
      }
      else {
         printf("You have to wait your turn\n");
      }
   }
   return;  
}

//sets a random starting player
void set_random_player_turn(){
   srand ( time(NULL) );
   player_turn = ( rand() % 2 ) + 1;
}


//Sets random target number that the players are trying to guess to a number between
// 1 and 1000
void set_random_target_number(){
   srand ( time(NULL) );
   random_target_number = ( rand() % 1000 ) + 1;
}

bool guess_number(){
   bool flag = false;

   printf("Enter Your Guess\n");
   int input;
   scanf("%d", &input);

   if(input < random_target_number){
      printf("%s\n", "Your guess is too low");
   }
   else if (input > random_target_number){
      printf("%s\n", "Your guess is too high");
   }
   else {
      printf("%s\n", "Your guess is correct!!");
      flag = true;
   }
   return flag;
}

bool player_takes_turn(Player* player){
   bool correct = false;
   //const char * yes = "y";

   printf("Will you pass this turn?(yes/no)\n");
   char pass_input[100];
   //fgets(pass_input);
   scanf("%s", pass_input);


   if(strcmp(pass_input, "yes") == 0){
      //if string check if player passed last turn and if they have passes left
      if(player->passes_left > 0 && player->justPassed == false){
         player->passes_left = player->passes_left - 1;
         printf("You have passed %d number of times, you have %d more times left\n", 3 - player->passes_left,player->passes_left);
      }
      player->passes_left = player->passes_left - 1;
      player->justPassed = true;
   }
   else
   {
      //if not pass then check number
      correct = guess_number();
      player->justPassed = false;
   }
   return correct;

}

void change_player_turn(){
   player_turn = player_turn +1;
   if (player_turn > 2){
      player_turn = 1;
   }
}
