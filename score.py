# calculate value of roll with frequency vector m
def points(m):
  #if type(m)<>list or 6<>len(m):
  #  raise Exception("m not a list of length six")
  m=list(m)
  if 6==m.count(1):return 1500
  if 3==m.count(2):return 7500
  s=0
  if m[0]==1 or m[0]==2:s+=100*m[0]
  if m[4]==1 or m[4]==2:s+=50*m[4]
  if m[0]>2:s+=1000*(m[0]-2)
  for i in range(1,6):
    if m[i]>2:s+=(i+1)*100*(m[i]-2)
  return s
