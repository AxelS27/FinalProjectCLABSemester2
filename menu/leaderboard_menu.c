//=====[[ C Library ]]=====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//=====[[ Custom Library ]]=====
#include "../library/leaderboard_menu.h"

//=====[[ Structure ]]=====
typedef struct {
    char username[50];
    int customer_handled;
} LeaderboardEntry;

//=====[[ Procedure/Function ]]=====
int load_profile_customer_handled(const char *filepath, LeaderboardEntry *entry) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) return 0;

    char line[256];
    if (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        if (!token) { fclose(fp); return 0; }
        strncpy(entry->username, token, sizeof(entry->username) - 1);
        entry->username[sizeof(entry->username) - 1] = '\0';

        token = strtok(NULL, ",");
        entry->customer_handled = token ? atoi(token) : 0;
    } else {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}

void sort_leaderboard(LeaderboardEntry *entries, int count, int descending) {
    for (int i = 1; i < count; i++) {
        LeaderboardEntry key = entries[i];
        int j = i - 1;
        if (descending) {
            while (j >= 0 && entries[j].customer_handled < key.customer_handled) {
                entries[j + 1] = entries[j];
                j--;
            }
        } else {
            while (j >= 0 && entries[j].customer_handled > key.customer_handled) {
                entries[j + 1] = entries[j];
                j--;
            }
        }
        entries[j + 1] = key;
    }
}

void leaderboard_menu(const char *username) {
    LeaderboardEntry entries[100];
    int count = 0;

    DIR *dir = opendir("database/profiles/user");
    if (!dir) {
        printf("-> Failed to open database/profiles/user.\n");
        system("pause");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[256];
            snprintf(path, sizeof(path), "database/profiles/user/%s", entry->d_name);
            FILE *fp = fopen(path, "r");
            if (fp) {
                fclose(fp);
                if (load_profile_customer_handled(path, &entries[count])) {
                    count++;
                    if (count >= 100) break;
                }
            }
        }
    }
    closedir(dir);

    int sort_desc = 1;

    while (1) {
        sort_leaderboard(entries, count, sort_desc);
        system("clear");

        printf("+---------------------------------------+\n");
        printf("| User: %-10s                      |\n", username);
        printf("|             LEADERBOARD               |\n");
        printf("+---------------------------------------+\n");
        printf("| Rank | Username       | Customers     |\n");
        printf("+---------------------------------------+\n");
        for (int i = 0; i < count; i++) {
            printf("| %-4d | %-13s | %-13d  |\n", i + 1, entries[i].username, entries[i].customer_handled);
        }
        printf("+---------------------------------------+\n");
		
		printf("\n+=======================================+");
        printf("\nSettings:\n\n");
        printf("[1] Sorting Ascending\n");
        printf("[2] Sorting Descending\n\n");
        printf("[0] Back\n");
        printf("+=======================================+\n");
        printf(">> ");

        int choice;
        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
        }

        if (choice == 1) {
            sort_desc = 0;
        } else if (choice == 2) {
            sort_desc = 1;
        } else if (choice == 0) {
            break;
        }
    }
}

