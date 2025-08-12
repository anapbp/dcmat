dcmat: lexico.l bison.y *.c
	flex lexico.l
	bison -d bison.y
	gcc *.c -I. -lm -o dcmat -g -Og


clean:
	rm -f dcmat lex.yy.c bison.tab.c bison.tab.h
