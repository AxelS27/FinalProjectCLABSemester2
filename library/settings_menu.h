#pragma once

typedef struct {
    char username[50];
    int customer_handled;
    int bg_color;
    int text_color;
} UserProfile;

int load_user_profile(const char *username, UserProfile *profile);
void apply_color();
void settings_menu(const char *username);

UserProfile *get_profile();

