from possible import *
pp=[possiblePoints(i) for i in range(1,7)]

def decide(dice,p): # p=points so far
  if type(dice)<>list or 6<len(l):
    raise Exception("dice not a list of proper length")
  if type(p)<>int or p<0:
    raise Exception("p not a natural number")
  m=[dice.count(i) for i in range(1,7)]
  score=points(m)
  keep=[x for x in dice if x==1 or x==5]
  reroll=[x for x in dice if x<>1 or x<>5]
  for x in subsets(reroll):
    s=sum(y['prob']*(y['score']+score) for y in pp[len(x)])
    print s
  
