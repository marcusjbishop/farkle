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
  char		  s       [12];
  int		  dice     [6];
  int		  n;

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
    n = select(f[1] + 1, NULL, &wset, NULL, NULL);
    printf("parent write select returned %d\n", n);
    n = write(f[1], s, sizeof(s));
    printf("parent wrote %d bytes of %s\n", n, s);

    FD_ZERO(&rset);
    FD_SET(g[0], &rset);
    n = select(g[0] + 1, &rset, NULL, NULL, NULL);
    printf("parent read select returned %d\n", n);
    //s[0]=0;
    n = read(g[0], s, 12);
    printf("parent read %d bytes of %s\n", n, s);

  } else {
    //Child
    close(f[1]);
    close(g[0]);
    dup2(f[0], STDIN_FILENO);
    dup2(g[1], STDOUT_FILENO);
    close(f[0]);
    close(g[1]);

    n=read(STDIN_FILENO,s,13);
    s[0]=100;
    write(STDOUT_FILENO,s,sizeof(s));

 //   execve("/Users/marcus/farkle/player.py", NULL, NULL);
  }
}
