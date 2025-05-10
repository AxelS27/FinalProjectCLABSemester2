#include <stdio.h>
#include <stdlib.h>

#include "../library/main_menu.h"

void main_menu(){
	int choice;
    
    while (1) {
    	system("clear");
		printf("+------------------------------------------------+\n");
	    printf("|                 STOCK UP CAFFEE                |\n");
	    printf("|        Inventory Management System (BST)       |\n");
	    printf("|------------------------------------------------|\n");
	    printf("| [1] Stock Management                           |\n");
	    printf("| [2] Report and analize                         |\n");
	    printf("|                                                |\n");
		printf("| [3] Cashier                                    |\n");
		printf("| [4] Leaderboard                                |\n");
		printf("| [5] Settings                                   |\n");
		printf("|                                                |\n");
		printf("| [9] Logout                                     |\n");
		printf("| [0] Exit                                       |\n");
	    printf("+------------------------------------------------+\n");
        printf(">> ");
        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
        }
        
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 0:
                printf("Data successfully stored. Exiting...\n\n");
                system("pause");
                exit(0);
                break;
        }
    }

}
