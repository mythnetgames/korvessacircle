#include "account.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ACCOUNT_FILE "../lib/etc/accounts.dat"

static struct account **account_table = NULL;
static int num_accounts = 0;

struct account *find_account(const char *name) {
    for (int i = 0; i < num_accounts; ++i) {
        if (strcasecmp(account_table[i]->name, name) == 0)
            return account_table[i];
    }
    return NULL;
}

int check_account_password(struct account *acct, const char *password) {
    // TODO: Use proper password hashing
    return strcmp(acct->password, password) == 0;
}

struct account *create_account(const char *name, const char *password, const char *email) {
    struct account *acct = calloc(1, sizeof(struct account));
    strncpy(acct->name, name, MAX_ACCOUNT_NAME);
    strncpy(acct->password, password, MAX_ACCOUNT_PASS);
    strncpy(acct->email, email, MAX_ACCOUNT_EMAIL);
    acct->num_chars = 0;
    acct->ansi_enabled = 0;
    // Add to table
    account_table = realloc(account_table, sizeof(struct account*) * (num_accounts + 1));
    account_table[num_accounts++] = acct;
    return acct;
}

int save_account(struct account *acct) {
    // TODO: Implement persistent save (append or rewrite file)
    (void)acct;
    return 1;
}

int load_accounts() {
    // TODO: Implement loading all accounts from file
    return 1;
}

void free_account(struct account *acct) {
    if (!acct) return;
    for (int i = 0; i < acct->num_chars; ++i)
        free(acct->char_names[i]);
    free(acct);
}
