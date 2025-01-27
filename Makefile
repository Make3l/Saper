game: main.o logic.o output.o
	cc main.o logic.o output.o -o game.out

leaderboard_test: test_leaderboard.o output.c
	cc test_leaderboard.o output.c -o leaderboard_test.out

function_test: test_function.o logic.o
	cc test_function.o logic.o -o function_test.out

main.o: main.c
	cc -c main.c

logic.o: logic.c
	cc -c logic.c

test_leaderboard.o: test_leaderboard.c
	cc -c test_leaderboard.c
	
outpu.o: output.c
	cc -c output.c

test_function.o: test_function.c
	cc -c test_function.c

clean:
	rm *.o