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

int parseResponse(char *s,int *m){
  int i=0;
  int newNdice=0;
  while(s[i]!='\n'){
    if(s[i]<49||s[i]>s[i]>54){
      fprintf(stderr,"Cant parse %s\n",s);
      exit(1);
    }
    m[i-49]--;
    newNdice++;
  }
  return newNdice;
}

void frequencyVector(int *dice,int *m,int n){
  int i,j;
  for(i=0;i<6;i++)
    m[i]=0;
  for (j = 0; j < 6; j++) {
    for (i = 0; i < n; i++) {
      if (dice[i] == j + 1)
	m[j]++;
    }
  }
}

int straight(int *m){
  int i,j;
  j = 0;
  for (i = 0; i < 6; i++)
    if (m[i] == 1)
      j++;
  if (j == 6)
    return 1;
  else
    return 0;
}

int threePair(int *m){
  int i,j;
  j = 0;
  for (i = 0; i < 6; i++)
    if (m[i] == 2)
      j++;
  if (j == 3)
    return 1;
  else
    return 0;
}

int
points(int *m){
  int		  i       ;
  int		  score = 0;

  /* Ones and fives worth 100 and 500 */
  if (m[0] == 1 || m[0] == 2)
    score += 100 * m[0];
  if (m[4] == 1 || m[4] == 2)
    score += 50 * m[0];

  /* Three-of-a-kind */
  if (m[0] > 2)
    score += 1000 * (m[0] - 2);
  for (i = 1; i < 6; i++)
    if (m[i] > 2)
      score += (i + 1) * 100 * (m[i] - 2);
  return score;
}
