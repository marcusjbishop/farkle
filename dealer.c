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
    n = write(f[1], s, 11);
    printf("parent wrote %d bytes of %s\n", n, s);

    FD_ZERO(&rset);
    FD_SET(g[0], &rset);
    n = select(g[0] + 1, &rset, NULL, NULL, NULL);
    printf("parent read select returned %d\n", n);
    n = read(g[0], s, 12);
    printf("parent read %d bytes of %s\n", n, s);

  } else {
    //Child

      FD_ZERO(&rset);
    FD_SET(f[0], &rset);
    n = select(f[0] + 1, &rset, NULL, NULL, NULL);
    printf("child read select returned %d\n", n);
    n = read(f[0], s, 11);
    printf("child read %d bytes of %s\n", n, s);
    /*
     * FD_ZERO(&wset); FD_SET(g[1], &wset); n=select(g[1] + 1, NULL, &wset,
     * NULL, NULL); printf("child write select returned %d\n",n);
     */
    sprintf(s, "123456789te");
    n = write(g[1], s, 11);
    printf("child wrote %d bytes of %s\n", n, s);
    /*
     * close(f[1]); close(g[0]); dup2(f[0], STDIN_FILENO); dup2(g[1],
     * STDOUT_FILENO); close(f[0]); close(g[1]); gets(s); printf("%s\n",s);
     */



    //execve("/Users/marcus/farkle/player.py", NULL, NULL);
  }
}
