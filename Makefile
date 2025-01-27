game: main.o logic.o output.o
	cc main.o logic.o output.o -o game.out

leaderboard_test: test_leaderboard.o output.c
	cc test_leaderboard.o output.c -o leaderboard_test.out

main.o: main.c
	cc -c main.c

logic.o: logic.c
	cc -c logic.c

test_leaderboard.o: test_leaderboard.c
	cc -c test_leaderboard.c
	
outpu.o: output.c
	cc -c output.c

clean:
	rm *.o