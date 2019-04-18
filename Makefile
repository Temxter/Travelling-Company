#makefile for Travel program

EXE = build/program
OBJMAIN = bin/main.o
OBJUSER = bin/user.o
OBJSQL = bin/sql_commands.o
MAIN = src/main.c
USER = src/user.c
SQL = src/sql_commands.c

execute: $(EXE)
	open $(EXE)


$(EXE): $(OBJMAIN) $(OBJUSER) $(OBJSQL)
	gcc -std=c99 $(OBJMAIN) $(OBJUSER) $(OBJSQL) bin/sqlite3.o -o $(EXE) -lsqlite3

Directories:
	mkdir -p bin build

$(OBJMAIN): $(MAIN)
	gcc -c -o $(OBJMAIN) $(MAIN)

$(OBJUSER): $(USER)
	gcc -c -o $(OBJUSER) $(USER)

$(OBJSQL): $(SQL)
	gcc -c -o $(OBJSQL) $(SQL)

bin/sqlite3.o: src/sqlite3.c
	gcc -std=c99 -c -MD src/sqlite3.c -o bin/sqlite3.o

clean:
	rm -rf /build/program bin/*.o