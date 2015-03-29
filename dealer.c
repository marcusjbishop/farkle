#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<sys/select.h>
#include<string.h>
#include"score.c"

int
main(void)
{
  int		  f        [2];
  int		  g        [2];
  int		  pid;
  fd_set	  wset  , rset;
  char		  s       [8];
  int		  dice     [6];
  int m[6];
  int		  n;
  struct timeval  t;
  long score;
  int nDice,newNdice;

  if ((pipe(f)) < 0)
    perror("pipe f failed\n");
  if ((pipe(g)) < 0)
    perror("pipe g failed\n");
  if ((pid = fork()) < 0) {
    perror("fork failed\n");
  } else if (pid ==0) { //Child
    close(f[1]);
    close(g[0]);
    dup2(f[0], 0);
    dup2(g[1], 1);
    close(f[0]);
    close(g[1]);
    setvbuf(stdout, NULL, _IOLBF, 6);
    /* fgets(s,7,stdin); s[0]=100; puts(s); */
    execve("/Users/marcus/farkle/player.py", NULL, NULL);
  } else { //Parent

    close(f[0]);
    close(g[1]);
    srand(time(NULL));
    t.tv_sec = 3;
    t.tv_usec = 0;
    score=0;
    nDice=6;

    while(1){
      FD_ZERO(&wset);
      FD_SET(f[1], &wset);
      roll(dice);
      frequencyVector(dice,m,nDice);
      printDice(dice, s, nDice);
      if(straight(m)){
        score+=1500;
        printf("Straight %s",s);
        continue;
      }
      if(threePair(m)){
        score+=750;
        printf("Three pair %s",s);
        continue;
      }

      n = select(f[1] + 1, NULL, &wset, NULL, &t);
      if(n==0){
        fprintf(stderr,"Timeout, player not ready for writing");
        break;
      } else if(n<0){
        perror("Write select failed\n");
        exit(1);
      }
      n = write(f[1], s, strlen(s));
      if(n!=strlen(s)){
        perror("Wrote wrong number of bytes\n");
        exit(1);
      }
      printf("parent wrote %d bytes of %s\n", n, s);

      FD_ZERO(&rset);
      FD_SET(g[0], &rset);
      n = select(g[0] + 1, &rset, NULL, NULL, &t);
      if(n==0){
        fprintf(stderr,"Timeout, player not ready for reading\n");
        break;
      } else if(n<0){
        perror("Read select failed\n");
        exit(1);
      }
      n = read(g[0], s, nDice+1);
      printf("parent read %d bytes of %s\n", n, s);
      newNdice=parseResponse(s,m);
      if(newNdice>=nDice){
        fprintf(stderr,"too many dice rolled\n");
        exit(1);
      }

    }
  }
}
