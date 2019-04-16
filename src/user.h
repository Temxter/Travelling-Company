//
//  user.h
//  Travel
//
//  Created by Anton Sipaylo on 4/5/19.
//  Copyright © 2019 Anton Sipaylo. All rights reserved.
//

#ifndef user_h
#define user_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>

#define SQL_MAX_LEN (100)
#define USER_AUTH_TABLE ("user_auth")
#define STATUS_COLUMN_INDEX (3)
#define BUS_NUMBER_COLUMN_INDEX (4)
#define MAX_NAME_LEN (20)
#define MAX_PASSWORD_LEN (20)

enum _user_status {admin = 0, notAdmin = 1, notRegistered = 2};

typedef enum _user_status user_status;

struct _user {
    char *login;
    char* password;
    user_status status;
    int bus_number;
};

typedef struct _user user;

void print_info_about_user(user *client);

void process_user_auth(const char* dataBaseName, user **client);

char *form_request_to_user_auth_table(user *client);

user *ask_for_user_info(void);
#endif /* user_h */
