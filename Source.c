/*Game Battle System Trial. Created by Sathya Jayakumar.
  This program would be implemented as several functions in a fully-fledged game.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

//Opponent's stats in demonstration
const int OPP_ATK = 5,
          OPP_DEF = 4,
	  OPP_MAGIC = 1,
	  OPP_SPD = 5,
          OPP_HP = 20;

//Function prototypes
int tryAgain();
int statBoost(int stat, int command);
int player(int command, int dmg, int stat);
int opponent(int def, int hp, char enemy[]);
int oppRestore(int hp, int remaining, char enemy[]);

int main(void) {
	//Time-based randomizer used in certain calculations
	time_t t;
	srand((unsigned)time(&t));
	
	//Different integer variables
	int hero, atk, def, mag, spd, hp, command, opphp, value, dmg = 0, index = 0, counter = 1, oppcounter = 1;

	//Opponent name in trial
	char enemy[] = "The Evil Overlord";

	//Program introduction
	printf("TURN-BASED GAME: Battle System Trial\nProgrammed by Sathya Jayakumar, UBC Engineering Student\n\n");
	system("PAUSE");

	//Selecting between 3 distinct types of heroes
	printf("\nSelect your hero class!\n\n	1. Knight\n	2. Mage\n	3. Thief\n\n");
	scanf("%d", &hero);

	//User prompted to enter valid integer if they entered an invalid one
	if (!(hero <= 3 && hero >= 1))
		hero = tryAgain();

	//Default HP (health point) total in trial
	hp = 20;

	//Different hero classes' statistic (stat) attributes
	if (hero == 1) {
		printf("\nYou are a knight!\n\n");
		atk = 7;
		def = 6;
		mag = 0;
		spd = 2;
	}
	else if (hero == 2) {
		printf("\nYou are a mage!\n\n");
		atk = 1;
		def = 3;
		mag = 7;
		spd = 4;
	}
	else if (hero == 3) {
		printf("\nYou are a thief!\n\n");
		atk = 4;
		def = 3;
		mag = 2;
		spd = 6;
	}

	system("PAUSE");

	//Challenge from opponent + HP in trial
	printf("\n%s challenges you!\n", enemy);
	opphp = OPP_HP;

	//Battle system loop
	while (opphp > 0 && hp > 0) {
		//Index counting # of turns
		index++;

		//Main menu; Indicates remaining HP and energy bars (to restore HP), as well as different commands possible
		printf("\nHP remaining: %d\nEnergy bars remaining: %d\nWhat will you do?\n\n	1. Attack\n	2. Magic\n	3. Flex\n	4. Focus\n	5. Defend\n	6. Energy bar\n	7. Run\n\n", hp, counter);
		scanf("%d", &command);

		//If no energy bars remain and its command is selected, loop will force user to select another command
		while (command == 6 && counter == 0) {
			printf("\nYou have no more energy bars! Do something else!: ");
			scanf("%d", &command);
		}

		//Damage calculator if physical attack command is selected
		if (command == 1) {
			dmg = (atk + rand() % 6) / OPP_DEF + 1;
			opphp -= dmg;
		}

		//Damage calculator if magic attack command is selected
		else if (command == 2) {
			dmg = (mag + rand() % 6) / OPP_DEF + 1;
			opphp -= dmg;
		}

		//Reducing energy bar counter by 1 if appropriate command is selected
		else if (command == 6)
			counter--;

		//If player's speed is greater than opponent's, the former will make their move first...
		if (spd >= OPP_SPD) {

			//Attack calculator if player chose to flex
			if (command == 3)
				atk = player(command, dmg, atk);

			//Magic calculator if player chose to focus
			else if (command == 4)
				mag = player(command, dmg, mag);

			//Defense calculator if player chose to defend
			else if (command == 5)
				def = player(command, dmg, def);

			//Calculator for other commands
			else hp = player(command, dmg, hp);

			/*If opponent's HP goes to or below 0 immediately after player's move, will break out of current "if" loop
			  and encompassing "while" loop, and the player wins*/
			if (opphp <= 0)
				break;

			//Randomizer to determine if opponent will restore HP or attack
			value = rand() % 10;

			//If randomizer returns certain value and energy bar counter is above 0, opponent can restore HP
			if (value > 7 && oppcounter != 0) {
				oppcounter--;
				opphp = oppRestore(opphp, oppcounter, enemy);
			}

			//Otherwise opponent will attack player
			else hp = opponent(def, hp, enemy);
		}

		//...otherwise the opponent will make their move first
		else {

			//Statements in loop the same as before, except opponent makes his move first...
			value = rand() % 10;

			if (value > 7 && oppcounter != 0) {
				oppcounter--;
				opphp = oppRestore(opphp, oppcounter, enemy);
			}

			else hp = opponent(def, hp, enemy);

			//...as such, will break out of loops if player's HP goes to or below 0, losing the game
			if (hp <= 0)
				break;

			if (command == 3)
				atk = player(command, dmg, atk);

			else if (command == 4)
				mag = player(command, dmg, mag);

			else if (command == 5)
				def = player(command, dmg, def);

			else hp = player(command, dmg, hp);
		}
	}

	//Win statement if player wins
	if (opphp <= 0)
		printf("\nYOU WIN!\nThe game was %d turns long.\n\n", index);

	//Lose statement if opponent wins
	else if (hp <= 0)
		printf("\nYou lost... :(\nThe game was %d turns long.\n\n", index);

	system("PAUSE");

	/*Thank you statement
	  NOTE: Depending on whether I have time or not, as I am taking summer courses, I may not create a full game
	  over said period*/
	printf("\n\n\nThank you for playing! See you in the final version!\n\n");

	//End game
	system("PAUSE");
	return 0;
}

//Function used if hero selected does not exist
int tryAgain() {
	int hero;

	printf("\nOption not given. Please try again: ");
	scanf("%d", &hero);

	return hero;
}

//HP restore and stat boost calculations and messages if player chooses appropriate command
int statBoost(int stat, int command) {

	if (command == 6) {
		stat += 10;
		printf("\nYou restored 10 HP!\n");
	}

	else {
		stat *= 2;

		if (command == 3)
			printf("\nYour attack increased!\n");
		else if (command == 4)
			printf("\nYour magic increased!\n");
		else if (command == 5)
			printf("\nYour defense increased!\n");
	}

	return stat;
}

/*Depending on selected command, prints damage dealt, calculates stat boost/restored HP,
  prints no escape message or turn wasted message*/
int player(int command, int dmg, int stat) {

	if (command == 1 || command == 2)
		printf("\nYou dealt %d damage!\n", dmg);

	else if (command == 3 || command == 4 || command == 5 || command == 6)
		stat = statBoost(stat, command);

	else if (command == 7)
		printf("\nYou can't escape!\n");

	else printf("\nYou wasted your turn! Don't do that again!\n");

	return stat;
}

//Opponent's damage calculator, printing damage dealt and returning player's remaining HP
int opponent(int def, int hp, char enemy[]) {
	//Another time-based randomizer, this time to calculate damage dealt by opponent each turn
	time_t t;
	srand((unsigned)time(&t));
	int oppdmg = (OPP_ATK + rand() % 6) / def + 1;

	hp -= oppdmg;

	printf("\n%s dealt %d damage!\n", enemy, oppdmg);

	return hp;
}

//Function restores 10 HP to opponent, printing approrpiate message and remaining energy bars
int oppRestore(int hp, int remaining, char enemy[]) {

	hp += 10;
	printf("\n%s ate an energy bar and restored 10 HP!\n%s has %d energy bars left!\n", enemy, enemy, remaining);

	return hp;
}
