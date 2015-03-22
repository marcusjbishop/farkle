#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/select.h>
#include<string.h>
#include"score.c"

void
roll(int *dice)
{
  int		  i;
  for (i = 0; i < 6; i++)
    dice[i] = rand() % 6 + 1;
}

void
printDice(int *v, char *s, int n)
{
  int		  i;
  for (i = 0; i < n; i++)
    s[i] = v[i] + 48;
  s[n] = '\n';
}

int
main(void)
{
  int		  f        [2];
  int		  g        [2];
  int		  pid;
  fd_set	  wset  , rset;
  char		  s       [8];
  int		  dice     [6];
  int		  n;
  struct timeval  t;

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
    t.tv_sec = 2;
    t.tv_usec = 0;
    srand(time(NULL));
    roll(dice);
    printDice(dice, s, 6);
    printf("%s", s);
    n = select(f[1] + 1, NULL, &wset, NULL, &t);
    printf("parent write select returned %d\n", n);
    n = write(f[1], s, strlen(s));
    printf("parent wrote %d bytes of %s\n", n, s);

    FD_ZERO(&rset);
    FD_SET(g[0], &rset);
    n = select(g[0] + 1, &rset, NULL, NULL, &t);
    if (n < 0) {
      perror("Bad read pipe");
      exit(1);
    } else if (n == 0) {
      fprintf(stdout, "Failed to read");
      exit(1);
    }
    printf("parent read select returned %d\n", n);
    n = read(g[0], s, 12);
    printf("parent read %d bytes of %s\n", n, s);

  } else {
    //Child
      close(f[1]);
    close(g[0]);
    dup2(f[0], 0);
    dup2(g[1], 1);
    close(f[0]);
    close(g[1]);
    setvbuf(stdout, NULL, _IOLBF, 6);
    /* fgets(s,7,stdin); s[0]=100; puts(s); */

    execve("/Users/marcus/farkle/player.py", NULL, NULL);
  }
}
