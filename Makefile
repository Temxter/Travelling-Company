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
	gcc $(OBJMAIN) $(OBJUSER) $(OBJSQL) -o $(EXE)

$(OBJMAIN): $(MAIN)
	gcc -c -o $(OBJMAIN) $(MAIN)

$(OBJUSER): $(USER)
	gcc -c -o $(OBJUSER) $(USER)

$(OBJSQL): $(SQL)
	gcc -c -o $(OBJSQL) $(SQL)

removeBin:
	rm -f *.o

removeBuild:
	rm -f /build/program