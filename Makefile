game: main.o logic.o
	cc main.o logic.o -o game.out

file_test: main.o test_logic.o
	cc main.o test_logic.o -o file_test.out

main.o: main.c
	cc -c main.c

logic.o: logic.c
	cc -c logic.c

test_logic.o: test_logic.c
	cc -c test_logic.c

clean:
	rm *.o