#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/main_menu.h"
#include "../library/authentication_menu.h"
#include "../library/cashier_menu.h"
#include "../library/leaderboard_menu.h"
#include "../library/settings_menu.h"


UserProfile profile;

void main_menu(const char *username){
    int choice;
    while (1) {
	    if (!load_user_profile(username, &profile)) {
		    strcpy(profile.username, username);
		    profile.customer_handled = 0;
		    profile.bg_color = 0;
		    profile.text_color = 7;
	    }
	    
		apply_color(profile.bg_color, profile.text_color);
		
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                               |\n", username); 
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|        Inventory Management System (BST)       |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Stock Management                           |\n");
        printf("| [2] View Stock                                 |\n");
        printf("|                                                |\n");
        printf("| [3] Cashier                                    |\n");
        printf("| [4] Leaderboard                                |\n");
        printf("|                                                |\n");
        printf("| [8] Settings                                   |\n");
        printf("| [9] Logout                                     |\n");
        printf("| [0] Exit                                       |\n");
    	printf("|                                                |\n");
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
            case 3:
            	printf("Loading cashier menu...\n\n");
            	system("pause");
            	cashier_menu(username);
            	break;
            case 8:
            	printf("Loading settings menu...\n\n");
            	system("pause");
            	settings_menu(username);
            	break;
            case 9:
            	printf("Logging out...\n\n");
            	system("pause");
            	authentication_menu();
            	break;
            case 0:
                printf("Data successfully stored. Exiting...\n\n");
                system("pause");
                printf("\033[0m");
                exit(0);
                break;
        }
    }
}
