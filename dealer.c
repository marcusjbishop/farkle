#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/select.h>
#include<string.h>
#include"score.c"

int main(void) {
  int		  f        [2];
  int		  g        [2];
  int		  pid;
  fd_set	  wset  , rset;
  char		  s       [8];
  int		  dice     [6];
  int		  m        [6];
  int		  n;
  struct timeval  t;
  long		  score  , overallScore;
  int		  nDice   , newNdice;

  if ((pipe(f)) < 0)
    perror("pipe f failed\n");
  if ((pipe(g)) < 0)
    perror("pipe g failed\n");
  if ((pid = fork()) < 0) {
    perror("fork failed\n");
  } else if (pid == 0) { //Child
    close(f[1]);
    close(g[0]);
    dup2(f[0], 0);
    dup2(g[1], 1);
    close(f[0]);
    close(g[1]);
    setvbuf(stdout, NULL, _IOLBF, 6);
    execve("/Users/marcus/farkle/player.py", NULL, NULL);
  } else { //Parent

    close(f[0]);
    close(g[1]);
    srand(time(NULL));
    t.tv_sec = 3;
    t.tv_usec = 0;
    overallScore = 0;
    score = 0;
    nDice = 6;

    while (1) {
      roll(dice);
      printDice(dice, s, nDice);
      printf("Rolled %s", s);
      frequencyVector(dice, m, nDice);
      if (straight(m)) {
	overallScore += 1500;
	printf("Straight %s", s);
	printf("Score %ld\n__________\n", overallScore);
	score = 0;
	nDice = 6;
	continue;
      }
      if (threePair(m)) {
	overallScore += 750;
	printf("Three pair %s", s);
	printf("Score %ld\n__________\n", overallScore);
	score = 0;
	nDice = 6;
	continue;
      }
      if (0 == points(m)) {
	printf("Farkled %s", s);
	printf("Score %ld\n__________\n", overallScore);
	score = 0;
	nDice = 6;
	continue;
      }
      FD_ZERO(&wset);
      FD_SET(f[1], &wset);
      n = select(f[1] + 1, NULL, &wset, NULL, &t);
      if (n == 0) {
	fprintf(stderr, "Timeout, player not ready for writing");
	break;
      } else if (n < 0) {
	perror("Write select failed\n");
	exit(1);
      }
      n = write(f[1], s, nDice + 1);
      if (n != nDice + 1) {
	perror("Wrote wrong number of bytes\n");
	exit(1);
      }
      FD_ZERO(&rset);
      FD_SET(g[0], &rset);
      n = select(g[0] + 1, &rset, NULL, NULL, &t);
      if (n == 0) {
	fprintf(stderr, "Timeout, player not ready for reading\n");
	break;
      } else if (n < 0) {
	perror("Read select failed\n");
	exit(1);
      }
      n = read(g[0], s, nDice + 1);

      newNdice = parseResponse(s, m);
      if (newNdice >= nDice) {
	fprintf(stderr, "too many dice rerolled\n");
	exit(1);
      }
      if (0 == newNdice) {
	overallScore += points(m);
	printf("Score %ld\n__________\n", overallScore);
	score = 0;
	nDice = 6;
      } else {
	nDice = newNdice;
	score += points(m);
      }
    }
  }
}
