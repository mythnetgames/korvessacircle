#include "account_menu.h"
#include "account.h"
#include "interpreter.h"
#include <string.h>
#include <stdlib.h>

// Add this to struct descriptor_data in structs.h:
// struct account *account;

static void prompt_for_account_password(struct descriptor_data *d);
static void prompt_for_account_email(struct descriptor_data *d);

void show_account_login_menu(struct descriptor_data *d) {
    write_to_output(d,
        "\r\nBy logging into our game you affirm you have reached the "
        "age of majority/consent in your jurisdiction or country.\r\n"
        "When in game refer to 'help information consent'\r\n"
        "------------------------------------------------------------\r\n"
        " C) Create a new game account. (NOTE: Not your character name)\r\n"
        " L) Login to an existing account\r\n"
        " G) Guest Gladiator\r\n"
        " N) Navehan Maze\r\n"
        " X) Disconnect from the server\r\n"
        "Your account name: ");
    d->account = NULL;
    d->account_menu_state = 0; // 0 = waiting for menu selection
}

void handle_account_login(struct descriptor_data *d, char *arg) {
    skip_spaces(&arg);
    if (d->account_menu_state == 0) {
        if (!*arg) {
            show_account_login_menu(d);
            return;
        }
        if (toupper(*arg) == 'C') {
            write_to_output(d, "\r\nEnter desired account name: ");
            d->account_menu_state = 1; // 1 = entering new account name
            return;
        } else if (toupper(*arg) == 'L') {
            write_to_output(d, "\r\nEnter your account name: ");
            d->account_menu_state = 2; // 2 = entering login account name
            return;
        } else if (toupper(*arg) == 'X') {
            STATE(d) = CON_CLOSE;
            return;
        } else {
            show_account_login_menu(d);
            return;
        }
    }
    // Account creation flow
    if (d->account_menu_state == 1) {
        // Creating new account, got name
        if (find_account(arg)) {
            write_to_output(d, "\r\nThat account name is already taken. Try another: ");
            return;
        }
        d->account = calloc(1, sizeof(struct account));
        strncpy(d->account->name, arg, MAX_ACCOUNT_NAME);
        write_to_output(d, "\r\nEnter a password for your new account: ");
        d->account_menu_state = 3; // 3 = entering new account password
        return;
    }
    if (d->account_menu_state == 3) {
        // Got password for new account
        strncpy(d->account->password, arg, MAX_ACCOUNT_PASS);
        write_to_output(d, "\r\nEnter your email address: ");
        d->account_menu_state = 4; // 4 = entering email
        return;
    }
    if (d->account_menu_state == 4) {
        // Got email, finish creation
        strncpy(d->account->email, arg, MAX_ACCOUNT_EMAIL);
        save_account(d->account);
        write_to_output(d, "\r\nAccount created!\r\n");
        show_account_main_menu(d);
        STATE(d) = CON_ACCOUNT_MENU;
        return;
    }
    // Account login flow
    if (d->account_menu_state == 2) {
        struct account *acct = find_account(arg);
        if (!acct) {
            write_to_output(d, "\r\nNo such account. Try again: ");
            return;
        }
        d->account = acct;
        write_to_output(d, "\r\nPassword: ");
        d->account_menu_state = 5; // 5 = entering password
        return;
    }
    if (d->account_menu_state == 5) {
        if (!d->account || !check_account_password(d->account, arg)) {
            write_to_output(d, "\r\nIncorrect password. Try again: ");
            return;
        }
        write_to_output(d, "\r\nLogin successful!\r\n");
        show_account_main_menu(d);
        STATE(d) = CON_ACCOUNT_MENU;
        return;
    }
    // Handle character selection after menu option 1
    if (d->account_menu_state == 10) {
        int idx = atoi(arg) - 1;
        if (idx < 0 || idx >= d->account->num_chars) {
            write_to_output(d, "\r\nInvalid selection.\r\n");
            show_account_main_menu(d);
            d->account_menu_state = 0;
            return;
        }
        char *char_name = d->account->char_names[idx];
        struct char_file_u tmp_store;
        int player_i = load_char(char_name, &tmp_store);
        if (player_i < 0) {
            write_to_output(d, "\r\nCharacter not found or could not be loaded.\r\n");
            show_account_main_menu(d);
            d->account_menu_state = 0;
            return;
        }
        if (d->character)
            free_char(d->character);
        CREATE(d->character, struct char_data, 1);
        clear_char(d->character);
        store_to_char(&tmp_store, d->character);
        GET_PFILEPOS(d->character) = player_i;
        d->character->desc = d;
        // TODO: Set up room, prompt, etc. as in legacy login
        write_to_output(d, "\r\nWelcome, %s!\r\n", char_name);
        STATE(d) = CON_PLAYING;
        d->account_menu_state = 0;
        return;
    }
}

void show_account_main_menu(struct descriptor_data *d) {
    write_to_output(d,
        "\r\n1. Login a character.\r\n"
        "2. Submit a character application.\r\n"
        "   (Approval required)\r\n"
        "10. Create randomly generated character.\r\n"
        "   (No approval required)\r\n"
        "3. Delete a pending application.\r\n"
        "4. Retire your current character.\r\n"
        "5. View your characters.\r\n"
        "6. Update your e-mail address.\r\n"
        "7. Change your account password.\r\n"
        "8. Toggle ANSI color setting.\r\n"
        "9. Harshmail.\r\n"
        "12. Link account to Discord account\r\n"
        "\r\n11. Log Out.\r\n"
        "\r\nYour Selection: ");
    d->account_menu_state = 0;
}

void handle_account_menu(struct descriptor_data *d, char *arg) {
    skip_spaces(&arg);
    if (!*arg) {
        show_account_main_menu(d);
        return;
    }
    int selection = atoi(arg);
    switch (selection) {
        case 1: // Login a character
            if (d->account->num_chars == 0) {
                write_to_output(d, "\r\nNo characters available. Submit an application or create a random character.\r\n");
                show_account_main_menu(d);
                return;
            }
            write_to_output(d, "\r\nWhich character would you like to log in?\r\n");
            for (int i = 0; i < d->account->num_chars; ++i)
                write_to_output(d, "%d. %s\r\n", i+1, d->account->char_names[i]);
            write_to_output(d, "Selection: ");
            d->account_menu_state = 10; // 10 = character selection
            return;
        case 2: // Submit a character application
            write_to_output(d, "\r\n[Application submission not yet implemented]\r\n");
            show_account_main_menu(d);
            return;
        case 10: // Create random character
            write_to_output(d, "\r\n[Random character creation not yet implemented]\r\n");
            show_account_main_menu(d);
            return;
        case 11: // Log Out
            d->account = NULL;
            d->account_menu_state = 0;
            STATE(d) = CON_ACCOUNT_LOGIN;
            show_account_login_menu(d);
            return;
        default:
            write_to_output(d, "\r\nOption not yet implemented or invalid.\r\n");
            show_account_main_menu(d);
            return;
    }
}
