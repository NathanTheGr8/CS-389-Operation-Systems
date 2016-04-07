#include <stdio.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <assert.h>

//Nathan Davis
//nhdavis2

//Global Varibles
int player_turn = 0;
int random_target_number = 0;
bool won = false;

//This is my structure for each player
struct Player
{
       int passes_left;
       bool justPassed;
};


//The constructor for Player. Takes no args and sets to default values
struct Player *Player_create()
{
    struct Player *who = malloc(sizeof(struct Player));
    assert(who != NULL);

    who->passes_left = 3;
    who->justPassed = false;

    return who;
}

//To free up memory after completion
void Player_destroy(struct Player *who)
{
    assert(who != NULL);

    free(who);
}

//Promps the user for their player number to determine if its their turn
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


//This method prompts the current player to enter their guess and prompts them if it
// is too high, low, or correct
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


//Prompts the user if they would like to pass. If they can pass their turn us over
//If they can't they are told why and then directed to guess a number
//If they do not pass they are prompted to guess a number
//returns if their guess was correct
bool player_takes_turn(struct Player* player){
   bool correct = false;
   //const char * yes = "y";

   printf("Will you pass this turn?(yes/no)\n");
   char pass_input[100];
   //fgets(pass_input);
   scanf("%s", pass_input);


   if(strcmp(pass_input, "yes") == 0){
      //if string check if player passed last turn and if they have passes left
      if(player->passes_left > 0 && player->justPassed == false){
         player->passes_left -= 1;
         player->justPassed = true;
         printf("You have passed %d number of times, you have %d more times left\n", 3 - player->passes_left,player->passes_left);
      }
      else{
         if (player->passes_left <= 0) {
            printf("You can't pass because you have %d passes left\n",player->passes_left);
         }
         else {
            printf("You can't pass because you passed last turn\n");
         }

         correct = guess_number();
         player->justPassed = false;
      }
      
   }
   else
   {
      //if not pass then check number
      correct = guess_number();
      player->justPassed = false;
   }
   return correct;

}

//changes turn to the next player
void change_player_turn(){
   player_turn = player_turn +1;
   if (player_turn > 2){
      player_turn = 1;
   }
}


int main()
{
   struct Player *p1 = Player_create();
   struct Player *p2 = Player_create();

   set_random_player_turn();
   set_random_target_number();


   //printf("For debug purposes the target number is :%d\n",random_target_number );

   while (!won){
      change_player_turn();
      printf("Its Player %d's Turn\n",player_turn);
      player_number();
      if (player_turn == 1){ //player 1's turn
         won = player_takes_turn(p1);
      }
      else { //player 2's turn
         won = player_takes_turn(p2);
      }
   }
   
   //free up memory
   Player_destroy(p1);
   Player_destroy(p2);

   return 0;
}
