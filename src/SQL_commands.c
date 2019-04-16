//
//  SQL_commands.c
//  Travel
//
//  Created by Anton Sipaylo on 4/13/19.
//  Copyright © 2019 Anton Sipaylo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "SQL_commands.h"

char* read_date()
{
    static char date[20];
    printf("Enter date YYYY-MM-DD: ");
    scanf("%s", date);
    return date;
}

int read_bus_number()
{
    int bus_number = 0;
    printf("Enter number of the bus: ");
    scanf("%d", &bus_number);
    return bus_number;
}

char* completed_tours ()
{
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    int bus_number = read_bus_number();
    char* date = read_date();
    sprintf(sql, "SELECT * FROM completed_tours ct WHERE ct.bus_number = %i and ct.finish_date < '%s'", bus_number, date);
    return sql;
}

char *form_additional_condition(user *client) {
    char *add_condition = (char*)calloc(MAX_CONDITIONS_LEN, sizeof(char));
    if (client->status == notAdmin) {
        sprintf(add_condition, " AND ct.bus_number='%i'", client->bus_number);
    } else {
        free(add_condition);
        add_condition = "";
    }
    return add_condition;
}

//
char *bus_info(user *client) {
    char *add_condition = form_additional_condition(client);
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    int bus_number = read_bus_number();
    sprintf(sql, "SELECT count(ct.bus_number) as amount_of_trips, sum(ct.passengers_amount) as passengers_amount, sum(ct.passengers_amount) * ct.cost as total_cost FROM completed_tours ct WHERE ct.bus_number = %i%s", bus_number, add_condition);
    free(add_condition);
    return sql;
}

char* bus_info_Andrew(user *client)
{
    char *add_condition = form_additional_condition(client);
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    int bus_number = read_bus_number();
    sprintf(sql, "SELECT ct.bus_number, COUNT(*) as amount_of_trips, SUM(ct.passengers_amount) as passengers_amount, SUM(cost*passengers_amount) as total_cost FROM completed_tours ct INNER JOIN buses b ON ct.bus_number = b.id WHERE bus_number = %d%s;", bus_number, add_condition);
     free(add_condition);
    return sql;
}
//

char* crew_money_for_period(user *client)
{
    char *add_condition = form_additional_condition(client);
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    char dateStart[20], dateFinish[20];
    printf("Enter start date YYYY-MM-DD: ");
    scanf("%s", dateStart);
    printf("Enter finish date YYYY-MM-DD: ");
    scanf("%s", dateFinish);
    sprintf(sql, "SELECT ct.bus_number as bus_number, SUM(ct.cost*ct.passengers_amount)*0.2 as money FROM completed_tours ct WHERE ct.finish_date > '%s' AND ct.finish_date < '%s'%s;", dateStart, dateFinish, add_condition);
    printf("\nsql = %s\n", sql);
    free(add_condition);
    return sql;
}


char* most_expensive_tour ()
{
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    sprintf(sql, "SELECT * FROM completed_tours ct INNER JOIN buses b ON ct.bus_number = b.id INNER JOIN crew c ON b.id = c.bus_number WHERE ct.cost = (select max(cost) from completed_tours);");
    return sql;
}

char* max_mileage ()
{
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    sprintf(sql, "SELECT ct.bus_number, b.name, b.mileage, sum(ct.passengers_amount) FROM completed_tours ct INNER JOIN buses b ON ct.bus_number = b.id WHERE b.mileage = (select MAX(mileage) from buses) GROUP BY ct.bus_number;");
    return sql;
}

char* crew_money_with_percentage_between_dates()
{
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    int percent = 20;
    printf("Enter percent of earnings: ");
    char dateStart[20], dateFinish[20];
    scanf("%d", &percent);
    printf("Enter start date YYYY-MM-DD: ");
    scanf("%s", dateStart);
    printf("Enter finish date YYYY-MM-DD: ");
    scanf("%s", dateFinish);
    sprintf(sql, "SELECT b.id, c.surname, SUM(ct.cost*ct.passengers_amount)*0.%d/3 FROM completed_tours ct INNER JOIN buses b ON ct.bus_number = b.id INNER JOIN crew c ON c.bus_number = b.id WHERE ct.finish_date > '%s' AND ct.finish_date < '%s';", percent, dateStart, dateFinish);
    return sql;
}
// Example: SELECT b.id, c.surname, SUM(ct.cost*ct.passengers_amount)*0.2/3 FROM completed_tours ct INNER JOIN buses b ON ct.bus_number = b.id INNER JOIN crew c ON c.bus_number = b.id WHERE ct.finish_date > '1999-10-10' AND ct.finish_date < '2020-10-10';

char* crew_money_date(user *client)
{
    char *add_condition = form_additional_condition(client);
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    sprintf(sql, "SELECT ct.bus_number, SUM(ct.cost*ct.passengers_amount) FROM completed_tours ct INNER JOIN buses b ON b.id = ct.bus_number WHERE ct.bus_number = %d AND ct.finish_date > '%s'%s;", read_bus_number(), read_date(), add_condition);
    free(add_condition);
    return sql;
}
// Example: SELECT ct.bus_number, SUM(ct.cost*ct.passengers_amount) FROM completed_tours ct INNER JOIN buses b ON b.id = ct.bus_number WHERE ct.bus_number = 1 AND ct.finish_date > 2020-10-10;

char *form_values_view() {
    char *values = (char*)calloc(MAX_TABLE_VALUES_LEN, sizeof(char));
    printf("values: ");
    scanf(" %[^\n]s", values); // read string with spaces
    char *new_values = (char*)calloc(MAX_TABLE_VALUES_LEN, sizeof(char));
    char *value = strtok(values, VALUES_DELIMITERS);
    sprintf(new_values, "'%s'", value);
    value = strtok(NULL, VALUES_DELIMITERS);
    while (value != NULL) {
        sprintf(new_values, "%s, '%s'", new_values, value);
        value = strtok(NULL, VALUES_DELIMITERS);
    }
    free(values);
    free(value);
    return new_values;
}

char* insert() {
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    char *table_name = (char*)calloc(MAX_TABLE_NAME_LEN, sizeof(char));
    printf("table name: ");
    scanf("%s", table_name);
    if (strcmp(table_name, "sightseeing_tours") == 0)
        return check_record();
    int i = 1;
    for (; i < TABLES_AMOUNT; i++)
        if (strcmp(table_name, tables[i]) == 0)
            break;
    if (i == TABLES_AMOUNT) {
        return NULL;
    }
    printf("columns: %s\n", tables_columns[i]);
    char *values = form_values_view();
    sprintf(sql, "INSERT INTO %s (%s) VALUES (%s);", table_name, tables_columns[i], values);
    free(table_name);
    free(values);
    return sql;
}

char* check_record()
{
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    char name[20], startPoint[20], finishPoint[20];
    double distance;
    printf("tour name: ");
    scanf("%s", name);
    printf("start point name: ");
    scanf("%s", startPoint);
    printf("finish point name: ");
    scanf("%s", finishPoint);
    printf("tour distance: ");
    scanf("%lf", &distance);
    sprintf(sql, "INSERT INTO sightseeing_tours (%s) SELECT * FROM (SELECT '%s', '%s', '%s', %lf) AS tmp WHERE NOT EXISTS (SELECT name FROM sightseeing_tours WHERE name = '%s') LIMIT 1;", tables_columns[0], name, startPoint, finishPoint, distance, name);
    return sql;
}
//Example: INSERT INTO sightseeing_tours (name, start_point, finish_point, distance) SELECT * FROM (SELECT 'Red Sea from Moscow', 'Moscow', 'Hurgada', 500) AS tmp WHERE NOT EXISTS (SELECT name FROM sightseeing_tours WHERE name = 'Red Sea from Moscow') LIMIT 1;

char *form_conditions(int i) {
    char *conditions = (char*)calloc(MAX_CONDITIONS_LEN, sizeof(char));
    int counter = 0;
    while (true) {
        counter++;
        if (counter > 1) {
            sprintf(conditions, "%s AND", conditions);
        }
        char *column_name = (char*)calloc(MAX_COLUMN_NAME_LEN, sizeof(char));
        printf("column name: ");
        scanf(" %s", column_name);
        char *column_value = (char*)calloc(MAX_COLUMN_VALUE_LEN, sizeof(char));
        printf("column value: ");
        scanf(" %s", column_value);
        sprintf(conditions, "%s %s='%s'", conditions, column_name, column_value);
        free(column_name);
        free(column_value);
        if (counter == tables_columns_amount[i])
            break;
        char c;
        printf("SETTING CONDITIONS TO DELETE: q - quit, c - continue: ");
        while (true) {
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
    return conditions;
}

int index_of_table(const char *table_name) {
    int i = 0;
    for (; i < TABLES_AMOUNT; i++) {
        if (strcmp(table_name, tables[i]) == 0) {
            break;
        }
    }
    return i;
}

char* delete_from_table() {
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    char *table_name = (char*)calloc(MAX_TABLE_NAME_LEN, sizeof(char));
    printf("table name: ");
    scanf("%s", table_name);
    int i = index_of_table(table_name);
    printf("Columns: %s\n", tables_columns[i]);
    char *conditions = form_conditions(i);
    sprintf(sql, "DELETE FROM %s WHERE %s;", table_name, conditions);
    free(table_name);
    free(conditions);
    return sql;
}

char* update() {
    printf("UPDATE chose request!\n");
    char *sql = (char*)calloc(MAX_REQUEST_LEN, sizeof(char));
    char *table_name = (char*)calloc(MAX_TABLE_NAME_LEN, sizeof(char));
    printf("table name: ");
    scanf("%s", table_name);
    int i = index_of_table(table_name);
    printf("Columns: %s\n", tables_columns[i]);
    printf("SET CONDITIONS:\n");
    char *set_conditions = form_conditions(i);
    printf("WHERE CONDITIONS:\n");
    char *where_conditions = form_conditions(i);
    sprintf(sql, "UPDATE %s SET %s WHERE %s;", table_name, set_conditions, where_conditions);
    free(table_name);
    free(set_conditions);
    free(where_conditions);
    return sql;
}
