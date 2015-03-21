#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/select.h>
#include"score.c"

void
roll(int *dice)
{
  int		  i;
  for (i = 0; i < 6; i++)
    dice[i] = rand() % 6 + 1;
}

void
printDice(int *v, char *s)
{
  sprintf(s, "%d,%d,%d,%d,%d,%d", v[0], v[1], v[2], v[3], v[4], v[5]);
}

int
main(void)
{
  int		  f        [2];
  int		  g        [2];
  int		  pid;
  fd_set	  wset  , rset;
  char		  s       [11];
  int		  dice     [6];

  if ((pipe(f)) < 0)
    perror("pipe failed");
  if ((pipe(g)) < 0)
    perror("pipe failed");
  if ((pid = fork()) < 0) {
    perror("fork failed");
  } else if (pid > 0) {
    //Parent

    close(f[0]);
    close(g[1]);

    FD_ZERO(&wset);
    FD_SET(f[1], &wset);
    srand(time(NULL));
    roll(dice);
    printDice(dice, s);
    select(f[1] + 1, NULL, &wset, NULL, NULL);
    if (11 != write(f[1], s, 11))
      perror("didn't write so well");
    printf("wrote %s\n", s);

    FD_ZERO(&rset);
    FD_SET(g[0], &rset);
    //select(NULL, g[0] + 1, &rset, NULL, NULL);
    printf("we're reading\n");
    //read(g[0], s, 11);
    printf("read %s\n", s);

  } else {
    //Child

    close(f[1]);
    close(g[0]);
    dup2(f[0], 0);
    dup2(g[1], 1);
    printf("child, we're grand\n");
    execve("/Users/marcus/farkle/player.py", NULL, NULL);
  }
}
