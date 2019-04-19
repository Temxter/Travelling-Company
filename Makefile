#makefile for Travel program

EXE = build/program
OBJMAIN = bin/main.o
OBJUSER = bin/user.o
OBJSQL = bin/SQL_commands.o
MAIN = src/main.c
USER = src/user.c
SQL = src/SQL_commands.c
SQLITE3 = src/sqlite3.c
OBJSQLITE3 = bin/sqlite3.o

execute: $(EXE)
	open $(EXE)


$(EXE): $(OBJMAIN) $(OBJUSER) $(OBJSQL) $(OBJSQLITE3) 
	gcc -std=c99 -o $(EXE) $(OBJMAIN) $(OBJUSER) $(OBJSQL) $(OBJSQLITE3) -lsqlite3 -ldl -lpthread

Directories:
	mkdir -p bin build

$(OBJMAIN): $(MAIN)
	gcc -std=c99 -MD -o $(OBJMAIN) -c $(MAIN)

$(OBJUSER): $(USER)
	gcc -std=c99 -MD -o $(OBJUSER) -c $(USER)

$(OBJSQL): $(SQL)
	gcc -std=c99 -MD -o $(OBJSQL) -c $(SQL)

$(OBJSQLITE3): $(SQLITE3)
	gcc -std=c99 -MD -o $(OBJSQLITE3) -c $(SQLITE3)

clean:
	rm -rf /build/program bin/*.o