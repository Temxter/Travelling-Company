//
//  user.c
//  Travel
//
//  Created by Anton Sipaylo on 4/5/19.
//  Copyright © 2019 Anton Sipaylo. All rights reserved.
//

#include "user.h"

void print_info_about_user(user *client) {
    printf("login = %s, password = %s\n", client->login, client->password);
}

void process_user_auth(const char* data_base_name, user **client) {
    sqlite3 *db;
    int result = 0;
    result = sqlite3_open_v2(data_base_name, &db, SQLITE_OPEN_READWRITE, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Something went wrong, when opening/creating database!\n");
        (*client)->status = notRegistered;
        return;
    }
    const char* sql = form_request_to_user_auth_table(*client);
    sqlite3_stmt *selectstm;
    result = sqlite3_prepare_v2(db, sql, -1, &selectstm, NULL);
    if (result == SQLITE_OK && sqlite3_step(selectstm) == SQLITE_ROW) {
        bool isAdmin = sqlite3_column_int(selectstm, STATUS_COLUMN_INDEX);
        (*client)->status = isAdmin ? admin : notAdmin;
        (*client)->bus_number = sqlite3_column_int(selectstm, BUS_NUMBER_COLUMN_INDEX);
    } else {
        printf("User wasn't found!\n");
        (*client)->status = notRegistered;
    }
    sqlite3_finalize(selectstm);
    sqlite3_close(db);
}

char *form_request_to_user_auth_table(user *client) {
    char* sql = (char*)calloc(SQL_MAX_LEN, sizeof(char));
    sprintf(sql, "select * from %s where login='%s' and password='%s'", USER_AUTH_TABLE, client->login, client->password);
    return sql;
}

user *ask_for_user_info() {
    user *client = (user*)malloc(sizeof(user));
    client->login = (char*)calloc(MAX_NAME_LEN, sizeof(char));
    printf("login: ");
    scanf("%s", client->login);
    client->password = (char*)calloc(MAX_PASSWORD_LEN, sizeof(char));
    printf("password: ");
    scanf("%s", client->password);
    return client;
}


