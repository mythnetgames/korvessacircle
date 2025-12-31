#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "structs.h"

#define MAX_ACCOUNT_NAME 32
#define MAX_ACCOUNT_PASS 64
#define MAX_ACCOUNT_EMAIL 64
#define MAX_ACCOUNT_CHARS 10

struct account {
    char name[MAX_ACCOUNT_NAME+1];
    char password[MAX_ACCOUNT_PASS+1]; // Store as hash in production
    char email[MAX_ACCOUNT_EMAIL+1];
    int num_chars;
    char *char_names[MAX_ACCOUNT_CHARS]; // Character names owned by this account
    int ansi_enabled;
    // Add more fields as needed (discord, last login, etc)
};

struct account *find_account(const char *name);
int check_account_password(struct account *acct, const char *password);
struct account *create_account(const char *name, const char *password, const char *email);
int save_account(struct account *acct);
int load_accounts();
void free_account(struct account *acct);

#endif // ACCOUNT_H
