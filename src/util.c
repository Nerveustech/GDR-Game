//Creato Da Michael
#include "util.h"


int lancio_d4(){
	int numero;
	int minore = 1;
	int maggiore = 4;
	
	numero = (rand() % ( maggiore - minore + 1)) + minore;
	return numero;
}

int lancio_d6(){
	int numero;
	int minore = 1;
	int maggiore = 6;

	numero = (rand() % ( maggiore - minore + 1)) + minore;
 	return numero;
}

int lancio_d8(){
	int numero;
	int minore = 1;
	int maggiore = 8;

	numero = (rand() % ( maggiore - minore + 1)) + minore;
	return numero;
}

int lancio_d20(){
	int numero;
	int minore = 1;
	int maggiore = 20;

	numero = (rand() % ( maggiore - minore + 1)) + minore;
	return numero;
}

int printf_spazio(int num){
	for(int spazio = 0; spazio < num; spazio++){
		printf("\n");
	}
}


void printf_centro(int spazio, int preset, char* buffer){
	if(preset == 0)
		printf("%*s\n", spazio / 2 + strlen(buffer) / 2, buffer);
	if(preset == 1)
		printf("%*s", spazio / 2 + strlen(buffer) / 2, buffer);
}

void printf_mostri(){
	printf_centro(128, 1, " N.  Nome Mostro             Livello  Vita   Armatura  Exp Drop  Punti Avventura\n");
	printf_centro(120, 1, "[1]  Iena                        1       5       11        10           1\n");
	printf_centro(120, 1, "[2]  Lupo                        1      11       13        50           1\n");
	printf_centro(120, 1, "[3]  Zombie                      2      22        8        50           2\n");
	printf_centro(120, 1, "[4]  Goblin                      2       7       15        50           2\n");
	printf_centro(120, 1, "[5]  Scheletro                   2      13       13        50           2\n");
	printf_centro(120, 1, "[6]  Banshee                     4      58       12       100          15\n");
	printf_centro(120, 1, "[7]  Fantasma                    4      45       11       100          15\n");
	printf_centro(120, 1, "[8]  Armatura Animata            4      33       18       200          20\n");
	printf_centro(120, 1, "[9]  Assassino                   5      28       17       150          25\n");	
	printf_centro(120, 1, "[10] Golem Di Pietra            10     178       17       900         100\n");
	printf_centro(120, 1, "[11] BeHolder Boss              13     189       18     10000         200\n");
	printf_centro(120, 1, "[12] Lich Boss                  21     135       17     33000         300\n");
	printf_centro(120, 1, "[13] Illithilich Boss           22     135       17     41000         300\n");
	printf_centro(120, 1, "[14] Drago Oro Boss             50     546       22     62000         500\n");
	printf_centro(120, 1, "[15] Alucard Boss               99    2048       20     99999         800\n");
	printf("\n");
	printf_centro(0, 1, "[0] Crea Avventura\n");
	printf_centro(0, 1, "[98] Crea Mostro\n");
	printf_centro(0, 1,"[99] Annulla\n");
	printf("\n");
}

void print_banner(){
	printf_centro(120, 0, "   ********     *******      *******      ********       **      ****     ****  ********");
	printf_centro(120, 0, "  **//////**   /**////**    /**////**    **//////**     ****    /**/**   **/** /**///// ");
	printf_centro(119, 0, " **      //    /**    /**   /**   /**   **      //     **//**   /**//** ** /** /**    ");
	printf_centro(120, 0, "/**            /**    /**   /*******   /**            **  //**  /** //***  /** /******* ");
	printf_centro(120, 0, "/**    *****   /**    /**   /**///**   /**    *****  ********** /**  //*   /** /**////  ");
	printf_centro(120, 0, "//**  ////** **/**    **  **/**  //**  //**  ////** /**//////** /**   /    /** /**      ");
	printf_centro(120, 0, " //******** /**/*******  /**/**   //**  //********  /**     /** /**        /** /********");
	printf_centro(120, 0, "  ////////  // ///////   // //     //    ////////   //      //  //         //  //////// ");
}

void printf_sconfitta(){
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣤⣤⣦⣦⣦⣦⣦⣦⣦⣦⣦⣦⣤⣄\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣮⣯⣯⣇⡯⠏⠋⠛⠋⠉⠉⠉⠉⠉⠉⠙⠛⠫⣇\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣮⣯⣪⠏⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣮:\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⢣⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣯⣇⡯:\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢫⣦⣤⣀⣀⢀⠀⠀⢀⢀⣀⣀⣠⣤⣤⣶⣦⣯⣯⢇⣇⡧⠛⠁\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠋⢯⣣⢇⢪⢎⢇⣇⣇⣇⣇⣇⣇⣇⡧⠏⠛⠉⠉\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣀⣀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣎⣣⠃⠈⠀⠀⠀⠈⢃⢠⣀⣀⣀⢀⣠.⣤⣤.\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣦⣮⣯⠏⠋⠉⠉⠉⠑⢂⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣇⢢⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⢉⣎⢪::\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣠⣦⣯⣣⠃⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢆⣣⠀⠀⠀⠀⠀⠀⠀⢠⣣⢇⠋⢀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢢⣧⣆⠊\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣄⣆⢎⢈⠋⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢂⣣⠀⠀⠀⠀⠀⠀⣇⢂⢎⣎⣦⣄⣋⢪⣆⠀⠀⠀⠀⠀⠀⣦⣆⢤⣎⣢⡆\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣠⣤⣤⣦⣦⣏⢋⠏⠃⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⢠⢂⢒⣦⣤⡀⠀⠀⢁⢊⠀⠀⠀⠀⠀⠀  ⠃⢫⢊⣃⠋⠋⠁⣄⣀⠀⢣⣯⣧⠫⢧⠇\n");
	printf("⠀⠀⠀⣢⣦⣦⣮⣇⣏⣏⣏⣯⣧⣇⠧⠯⠋⠋⠃⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣇⢪⣆⢤⣮⢀⡀⠀⢇⢪⠀⠀⠀⠀⠀⠀ ⠀⠀⠑⢋⢄⠀⣀⣪⢃⣣⠉⠓⠋\n");
	printf("⠀⠀⠀⠘⢞⣀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠣⣨⢇⣠⠀⢰⢃⢈⠀⠀⠀⠀⠀⠀    ⠀⠀⠀⠀⠀⠉⠉\n");
	printf("⠀⠀⠀⠀⠀⠈⠙⠃⢇⣧⣧⣯⣧⣧⣦⣄⠀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⣄⣮⢇⡮⠀⢀⣫⣇⠃\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⢀⣏⠀⢀⣤⣦⣯⣪⣣⠀⣠⣆⣇⢪⣆⢀⣠⣮⣎⢅⠂⢀⣤⣆⣎⢣⠋⠁\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢪⢣⢣⣦⣯⢣⠫⠃⢌⣎⣇⣇⣢⠮⣪⢪⢃⣇⢢⠋⠘⢧⣇⣆⠇⠃⠁\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠋⠉⠉⠀⠀⠀⠀⠈⠋⠃⠁⠀⠀⠀⠙⠁⠁\n");
}


void printf_banner_combat(){
	printf("				             ,▄▄▄▄▄▄▄▄,\n");
	printf("				         ▄███▀▀██▄▄█▀▀▀██▄,\n");
	printf("				       ▄████████████████▄▀██∞\n");
	printf("				      ██████████████████████\n");
	printf("				     ▐████████████████████████\n");
	printf("				     █████████████████████████▌\n");
	printf("				     ██████████████████████████W\n");
	printf("				      ▐██████████████▄,   `▀▀▀█▌\n");
	printf("				       ███████████████████▄▄▄, █\n");
	printf("				       ███████████████████████▌▐█\n");
	printf("				     ,█████████████████████████ ▀▀\n");
	printf("				   ,▄███████████ ██████████████▌\n");
	printf("				               ▀─ ▀█████████████\n");
	printf("				4██▄▄▄▄▄▄,,         ▀███████████▌            ,,▄▄▄▄▄▄██@\n");
	printf("				  ▀███████████▄▄,        ▀▀▀█████      ,▄▄████████████`\n");
	printf("				    ▀███████▀███████▄,         `▀ ,▄███████▀▀██████▀ \n");
	printf("				       ▀▀█████▄▄,▀▀█████▄▄    ,▄█████▀▀▀▄▄█████▀▀\n");
	printf("				           ▀▀██████▄▄,▀▀████████▀▀,▄▄██████▀▀ \n");
	printf("				            ,,  ▀▀█████████▀▀,▄▄██████▀▀` ,, \n");
	printf("				           ██▌▄███████▀▀▄▄▄█████▀▀███████▄███ \n");
	printf("				           ███▐██▀▀▄▄████▀▀  ▀▀████▄▄█▀██████  \n");
	printf("				       ▄▄██████▐█████▀▀          `▀████████████▄▄ \n");
	printf("				,▄▄▄██████████████▀                  ▀██████████████▄▄▄, \n");
	printf("				████████▀▀    ▀███                    ▀███    ▀▀▀███████ \n");
	printf("				▀███▀                                              └███▀ \n");
}


void printf_vittoria(){
	printf("					  ⌐╗╥,  ╓g╦@@@▒░░░░░░░░▒▒@@▓&▄▄╥  ,╓╗~  \n");
	printf("					╒░▓    ╙▒▒▒╢╢▒▒       ░░▒▒╢▓▓▓▓▒░╙   ╙░╕\n");
	printf("					╟╟░    ░║╢▒▒╢╣▒        ░▒▒╢▓▓▓▓▒░░   ░╢▓\n");
	printf("					 ░@      ╠▒░▒▒▒        ░▒▒╫▓▓▓▒      ]▒`\n");
	printf("					 ╙╜╗   ░░▒╢░▒▒▒░       ░▒▒▓▓▓▓▒░░░  ╓▒╝\n");
	printf("					   Ñ,     ▒▒░▒╢▒      ░░▒╫▓▓▓░    ,@▒`\n");
	printf("					    `╝N,   ▒▒▒╢▒▒░   ░░▒╢▓▓▓▒   ,mW \n");
	printf("					        ╣w  ╢▒▒╢▒░  ░░░▒╫▓▓▓  ╓D  \n");
	printf("					           0╖▒▒▒╢▒░ ░░▒╢▓▓▓╓ß  \n");
	printf("					             ╙▒▒╢▒▒ ░░╢▓▓▓╜ \n");
	printf("					                ║╢▒░░▒▓▓ \n");
	printf("					                ░╟╣▒▒╫▓░ \n");
	printf("					                 ╓╣╨╨▓W \n");
	printf("					                  ▓▒▒▓ \n");
	printf("					                 ╓▓  ▓▄  \n");
	printf("					                ╟▓▒  ▒▓▓ \n");
	printf("					              ,▓▓▒░  ░╢▓▓, \n");
	printf("					              ▓╣▒░  ┌▒╢▓▓▓[ \n");
	printf("					            ,▓╣▒▒   ░▒▒╫▓▓▓╗ \n");
	printf("					            ╫╣╣▒▒░░░░▒▒╫▓▓▓▓U\n");
}

