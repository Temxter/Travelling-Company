#pragma once

#include "user.h"

#define MAX_REQUEST_LEN (300)
#define TABLES_AMOUNT (5)
#define MAX_TABLE_NAME_LEN (20)
#define MAX_COLUMN_NAME_LEN (20)
#define MAX_COLUMN_VALUE_LEN (30)
#define MAX_TABLE_VALUES_LEN (150)
#define VALUES_DELIMITERS (" ,")
#define MAX_CONDITIONS_LEN (200)
#define OPERATION_LEN (20)
#define DATA_BASE_NAME ("/Users/anton/University/ProgrammingTechnology/lab5/my-project-travel/Travel/database.db")
#define INTERFACE_LIST ("1 - info about completed races\n"\
"2 - info about amount of races\n"\
"3 - info about crew for period\n"\
"4 - info about the most expensive race"\
"5 - info about bus with max mileage"\
"6 - info about crew money between two dates\n"\
"7 - info about crew money specified by date\n"\
"8 - insert info into table\n"\
"9 - delete from table\n"\
"10 - update table: ")

static const char *tables[TABLES_AMOUNT] = {"sightseeing_tours", "buses", "crew", "completed_tours", "user_auth"};
static const int tables_columns_amount[TABLES_AMOUNT] = {4, 3, 6, 6, 3};
static const char *tables_columns[TABLES_AMOUNT] = {"name, start_point, finish_point, distance", "name, mileage, photo", "surname, experience_years, category, address, birth_year, bus_number", "start_date, finish_date, passengers_amount, cost, sightseeing_tour_id, bus_number", "login, password, isAdmin"};

char* read_date(void);
int read_bus_number(void);
char* completed_tours(void);
//another variant of next request
char* bus_info(user *client);
char* bus_info_Andrew(user *client);
//
char* crew_money_for_period(user *client);
char* most_expensive_tour(void);
char* max_mileage(void);
char* crew_money_with_percentage_between_dates(void);//5
char* crew_money_date (user *client);//6
char* insert(void);
char* delete_from_table(void);
char* update(void);
char* check_record(void);
