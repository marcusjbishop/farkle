int
points(int *dice, int n)
{
  int		  m        [6] = {0, 0, 0, 0, 0, 0};
  int		  i       , j;
  int		  score = 0;
  for (j = 0; j < 6; j++) {
    for (i = 0; i < n; i++) {
      if (dice[i] == j + 1)
	m[j]++;
    }
  }
  j = 0;
  for (i = 0; i < 6; i++)
    if (m[i] == 1)
      j++;
  if (j == 6)
    return 1500;
  j = 0;
  for (i = 0; i < 6; i++)
    if (m[i] == 2)
      j++;
  if (j == 3)
    return 7500;
  if (m[0] == 1 || m[0] == 2)
    score += 100 * m[0];
  if (m[4] == 1 || m[4] == 2)
    score += 50 * m[0];
  if (m[0] > 2)
    score += 1000 * (m[0] - 2);
  for (i = 1; i < 6; i++)
    if (m[i] > 2)
      score += (i + 1) * 100 * (m[i] - 2);
  return score;
}
