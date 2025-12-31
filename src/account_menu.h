#ifndef ACCOUNT_MENU_H
#define ACCOUNT_MENU_H

void show_account_login_menu(struct descriptor_data *d);
void show_account_main_menu(struct descriptor_data *d);
void handle_account_login(struct descriptor_data *d, char *arg);
void handle_account_menu(struct descriptor_data *d, char *arg);

#endif // ACCOUNT_MENU_H
