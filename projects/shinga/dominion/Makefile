CFLAGS = -Wall -fpic -coverage -lm

default: dominion.o

myassert.o: myassert.h myassert.c
	gcc -c myassert.c -g $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o myassert.o interface.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o myassert.o interface.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o myassert.o interface.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o myassert.o interface.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o myassert.o interface.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o myassert.o interface.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o myassert.o interface.o
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o myassert.o interface.o
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o myassert.o interface.o
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o myassert.o interface.o $(CFLAGS)

randomtestresults.out: randomtestcard1 randomtestcard2 randomtestadventurer
	./randomtestcard1 > randomtestresults.out
	gcov -b dominion.o >> unittestresults.out
	./randomtestcard2 > randomtestresults.out
	gcov -b dominion.o >> unittestresults.out
	./randomtestadventurer > randomtestresults.out
	gcov -b dominion.o >> unittestresults.out


testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 dominion.o
	./unittest1 > unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out
	./cardtest2 >> unittestresults.out
	gcov -b dominion.o >> unittestresults.out





player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o randomtestcard1 randomtestcard2 randomtestadventurer randomtestresults.out unittestresults.out unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.exe *.gcov *.gcda *.gcno *.so
