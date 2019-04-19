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

#execute: $(EXE)
#	open $(EXE)


$(EXE): $(OBJMAIN) $(OBJUSER) $(OBJSQL) $(OBJSQLITE3) 
	gcc -o $(EXE) $(OBJMAIN) $(OBJUSER) $(OBJSQL) $(OBJSQLITE3) 

Directories:
	mkdir -p bin build

$(OBJMAIN): $(MAIN)
	gcc -o $(OBJMAIN) -c $(MAIN)

$(OBJUSER): $(USER)
	gcc -o $(OBJUSER) -c $(USER)

$(OBJSQL): $(SQL)
	gcc -o $(OBJSQL) -c $(SQL)

$(OBJSQLITE3): $(SQLITE3)
	gcc -o $(OBJSQLITE3) -c $(SQLITE3)

clean:
	rm -rf /build/program bin/*.o