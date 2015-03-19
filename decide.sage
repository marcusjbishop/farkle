load('score.py')
load('p.py')
def v2d(m):
  l=list()
  for i in range(6):
    l.extend([i+1]*m[i])
  return l

def d2v(l):
  return vector([l.count(i) for i in range(1,7)])

def decide(dice,previous):
  m=d2v(dice)
  canKeep=vector([m[0],0,0,0,m[4],0])
  for i in [1,2,3,5]:
    if m[i]>2:canKeep[i]=m[i]
  mustReroll=m-canKeep
  choices=[]
  for x in subsets(v2d(canKeep)):
    x.extend(v2d(mustReroll))
    if len(x)==len(dice):break
    reroll=d2v(x)
    keep=m-reroll
    score=points(keep)
    exp=sum(x['prob']*(x['score']+score+previous)
      for x in pp[len(x)])
    choices.append(
      {'reroll':x,'exp':exp,'score':score+previous}) 
  mx=max(x['exp'] for x in choices)
  best=[x for x in choices if x['exp']==mx]
  return best[0]['reroll']
  
