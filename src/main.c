//
//  main.c
//  Travel
//
//  Created by Anton Sipaylo on 4/5/19.
//  Copyright © 2019 Anton Sipaylo. All rights reserved.
//

#include "user.h"
#include "SQL_commands.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n\n");
    return 0;
}

int main(int argc, const char * argv[]) {
    user *client = ask_for_user_info();
    process_user_auth(DATA_BASE_NAME, &client);
    sqlite3 *db;
    int result = 0;
    result = sqlite3_open_v2(DATA_BASE_NAME, &db, SQLITE_OPEN_READWRITE, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Something went wrong, when opening/creating database!\n");
    }
    if (client->status == notRegistered) {
        printf("We're sorry, but you haven't registerd in our system yet\n");
        return 0;
    }
    if (client->status == admin) {
        printf("You are an administrator!\n");
    } else if (client->status == notAdmin) {
        printf("You aren't admin!\n");
    }
    while (true) {
        char *request = NULL;
        printf(INTERFACE_LIST);
        int command = 0;
        scanf(" %i", &command);
        if (command == 1) request = completed_tours();
        else if (command == 2) request = bus_info(client);
        else if (command == 3) request = crew_money_for_period(client);
        else if (command == 4) request = most_expensive_tour();
        else if (command == 5) request = max_mileage();
        else if (command == 6) request = crew_money_with_percentage_between_dates();
        else if (command == 7) request = crew_money_date(client);
        else if (command == 8) request = insert();
        else if (command == 9) request = delete_from_table();
        else if (command == 10) request = update();
        else {
            printf("Invalid command number!\n");
            continue;
        }
        if (request == NULL) {
            printf("Invalid request!\n");
            continue;
        }
        char *zErrMsg;
        result = sqlite3_exec(db, request, callback, NULL, &zErrMsg);
        if (result != SQLITE_OK) {
            printf("Execution failed! Error: %s\n", zErrMsg);
        } else {
            printf("Request was executed!\n");
        }
        char c;
        while (true) {
            printf("q - quit, c - continue: ");
            scanf(" %c", &c);
            if (c != 'q' && c != 'c') {
                printf("Invalid command! Try again: ");
                continue;
            } else {
                break;
            }
        }
        if (c == 'q') break;
        else if (c == 'c') continue;
    }
    sqlite3_close(db);
    return 0;
}
