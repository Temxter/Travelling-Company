//
//  SQL_create_commands.h
//  Travel
//
//  Created by Anton Sipaylo on 4/13/19.
//  Copyright © 2019 Anton Sipaylo. All rights reserved.
//

#ifndef SQL_create_commands_h
#define SQL_create_commands_h

const char *create_buses = "create table buses(id integer primary key autoincrement, name text not null, mileage double not null, photo blob not null);";
const char *create_sightseeing_tours = "create table sightseeing_tours(id integer primary key autoincrement, name text not null, start_point text not null, finish_point text not null, distance double not null);";
const char *create_completed_tours = "create table completed_tours(id integer primary key autoincrement, start_date date not null, finish_date date not null, passengers_amount int not null, cost double not null, sightseeing_tour_id int not null, bus_number int not null);";
const char *create_crew = "create table crew(id integer primary key autoincrement, surname text not null, experience_years int not null, category text not null, address text not null, birth_year int not null, bus_number int not null);";
//const char *create_user_auth = "create table user_auth(id integer primary key autoincrement, login varchar(20), password varchar(20), status int);"

#endif /* SQL_create_commands_h */
