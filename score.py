def points(l):
  if type(l)<>list or 6<>len(l):
    raise Exception("l not a list of correct length")
  l.sort()
  if l==range(1,7):return 1500
  m=[l.count(i) for i in range(1,7)]
  if 3==m.count(2):return 7500
  s=0
  if m[0]==1 or m[0]==2:s+=100*m[0]
  if m[4]==1 or m[4]==2:s+=50*m[4]
  if m[0]>2:s+=1000*(m[0]-2)
  for i in range(1,6):
    if m[i]>2:s+=(i+1)*100*(m[i]-2)
  return s
