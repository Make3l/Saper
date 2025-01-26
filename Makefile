game: main.o logic.o output.o
	cc main.o logic.o output.o -o game.out

file_test: main.o test_logic.o
	cc main.o test_logic.o -o file_test.out

leaderboard_test: test_leaderboard.o output.c
	cc test_leaderboard.o output.c -o leaderboard_test

main.o: main.c
	cc -c main.c

logic.o: logic.c
	cc -c logic.c

test_logic.o: test_logic.c
	cc -c test_logic.c

test_leaderboard.o: test_leaderboard.c
	cc -c test_leaderboard.c
	
outpu.o: output.c
	cc -c output.c

clean:
	rm *.o