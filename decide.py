from p import pp
from score import points

def subsets(L):
  return [[L[j] for j in range(len(L)) if 1<<j&i]
    for i in range(0,1<<len(L))]

def uniq(l):
  u=[]
  for x in l:
    if not x in u:
      u.append(x)
  return u

def subtract(l,m):
  return [x-y for x,y in zip(l,m)]

def v2d(m):
  l=list()
  for i in range(6):
    l.extend([i+1]*m[i])
  return l

def d2v(l):
  return [l.count(i) for i in range(1,7)]

def decide(dice,previous):
  m=d2v(dice)
  canKeep=[m[0],0,0,0,m[4],0]
  for i in [1,2,3,5]:
    if m[i]>2:canKeep[i]=m[i]
  if 0==sum(canKeep):
    raise Exception("Farkle!")
  mustReroll=subtract(m,canKeep)
  choices=[]
  stay=points(m)+previous
  if stay>=300:
    choices.append(
      {'reroll':[],'exp':stay,'score':stay}) 
  for x in uniq(subsets(v2d(canKeep))):
    x.extend(v2d(mustReroll))
    if len(x)==len(dice):break
    reroll=d2v(x)
    keep=subtract(m,reroll)
    score=points(keep)
    exp=sum(x['prob']*(x['score']+score+previous)
      for x in pp[len(x)])
    choices.append(
      {'reroll':x,'exp':exp,'score':score+previous}) 
  mx=max(x['exp'] for x in choices)
  best=[x for x in choices if x['exp']==mx]
  return best[0]
  # If there are several, should we pick a different one?
  
