//=====[[ C Library ]]=====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//=====[[ Constant Variable ]]=====
#define USERNAME_SIZE 50

//=====[[ Structure ]]=====
typedef struct {
    char username[USERNAME_SIZE];
    int customer_handled;
    int bg_color;
    int text_color;
} UserProfile;

//=====[[ Procedure/Functions ]]=====
void apply_color(int bg_color, int text_color) {
    printf("\033[0m");
    printf("\033[4%dm", bg_color);
    printf("\033[3%dm", text_color);
}

int load_user_profile(const char *username, UserProfile *profile) {
    char path[128];
    sprintf(path, "database/profiles/user/%s.txt", username);

    FILE *fp = fopen(path, "r");
    if (!fp) return 0;

    char line[256];
    if (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        if (!token) { fclose(fp); return 0; }
        strcpy(profile->username, token);

        token = strtok(NULL, ",");
        profile->customer_handled = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        profile->bg_color = token ? atoi(token) : 0;

        token = strtok(NULL, ",");
        profile->text_color = token ? atoi(token) : 7;
    } else {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

void save_user_profile(const UserProfile *profile) {
    char path[128];
    sprintf(path, "database/profiles/user/%s.txt", profile->username);

    FILE *fp = fopen(path, "w");
    if (!fp) return;

    fprintf(fp, "%s,%d,%d,%d\n",
            profile->username,
            profile->customer_handled,
            profile->bg_color,
            profile->text_color);

    fclose(fp);
}

void set_background_color(UserProfile *profile) {
    int bg_color = profile->bg_color;
    while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("|                 Settings - Background Color    |\n");
        printf("+------------------------------------------------+\n");
        printf("  Background color codes:\n");
        printf("  0=Black   1=Red    2=Green   3=Yellow\n");
        printf("  4=Blue    5=Magenta 6=Cyan    7=White\n");
        printf("+------------------------------------------------+\n");
        printf("  Current background color code: %d\n", bg_color);
        printf("  Enter background color code (0-7) or -1 to back\n");
        printf(">> ");

        if (scanf("%d", &bg_color) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (bg_color == -1) {
            printf("\033[0m");
            break;
        }
        if (bg_color < 0 || bg_color > 7) {
            printf("Invalid color code.\n");
            system("pause");
            continue;
        }

        profile->bg_color = bg_color;
        apply_color(profile->bg_color, profile->text_color);
        printf("Background color changed!\n");
        
		system("pause");

        save_user_profile(profile);
    }
}

void set_text_color(UserProfile *profile) {
    int text_color = profile->text_color;
    while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("|                   Settings - Text Color         |\n");
        printf("+------------------------------------------------+\n");
        printf("  Text color codes:\n");
        printf("  0=Black   1=Red    2=Green   3=Yellow\n");
        printf("  4=Blue    5=Magenta 6=Cyan    7=White\n");
        printf("+------------------------------------------------+\n");
        printf("  Current text color code: %d\n", text_color);
        printf("  Enter text color code (0-7) or -1 to back\n");
        printf(">> ");

        if (scanf("%d", &text_color) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (text_color == -1) {
            printf("\033[0m");
            break;
        }
        if (text_color < 0 || text_color > 7) {
            printf("  >> Invalid color code.\n");
            system("pause");
            continue;
        }

        profile->text_color = text_color;
        apply_color(profile->bg_color, profile->text_color);
        printf("  >>Text color changed!\n");
        
		system("pause");

        save_user_profile(profile);
    }
}

void delete_account(const char *username) {
    FILE *file = fopen("database/authentication.bin", "rb");
    FILE *temp = fopen("database/auth_temp.bin", "wb");
    if (!file || !temp) {
        printf("Failed to open files.\n");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    struct User {
        char username[USERNAME_SIZE];
        char password[50];
    } user;

    int found = 0;
    while (fread(&user, sizeof(user), 1, file)) {
        if (strcmp(user.username, username) != 0) {
            fwrite(&user, sizeof(user), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("database/authentication.bin");
        rename("database/auth_temp.bin", "database/authentication.bin");

        char profile_path[128];
        sprintf(profile_path, "database/profiles/user/%s.txt", username);
        remove(profile_path);

        printf("Account '%s' deleted successfully.\n", username);
    } else {
        remove("database/auth_temp.bin");
        printf("Account not found.\n");
    }

	system("pause");
}

void settings_menu(const char *username) {
    int choice;
    UserProfile profile;

    if (!load_user_profile(username, &profile)) {

        strcpy(profile.username, username);
        profile.customer_handled = 0;
        profile.bg_color = 0;
        profile.text_color = 7;
    }
    
    apply_color(profile.bg_color, profile.text_color);

    while (1) {
        system("cls");
        apply_color(profile.bg_color, profile.text_color);
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                               |\n", profile.username);
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|        Inventory Management System (BST)       |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Set Background Color                       |\n");
        printf("| [2] Set Text Color                             |\n");
        printf("|                                                |\n");
        printf("| [3] Delete Account                             |\n");
        printf("|                                                |\n");
        printf("| [0] Back                                       |\n");
        printf("|                                                |\n");
        printf("+------------------------------------------------+\n");
        printf(">> ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 1) {
            set_background_color(&profile);
        } else if (choice == 2) {
            set_text_color(&profile);
        } else if (choice == 3) {
            printf("Are you sure you want to delete your account '%s'? (y/n): ", username);
            char confirm = getchar();
            while (getchar() != '\n');

            if (confirm == 'y' || confirm == 'Y') {
                delete_account(username);
                printf("  >> Account deleted. Exiting program.\n");
                exit(0);
            } else {
                printf("  >> Account deletion canceled.\n");
                system("pause");
            }
        } else if (choice == 0) {
            printf("\033[0m");
            break;
        } else {
            printf("  >> Invalid choice.\n");
            system("pause");
        }
    }
}

