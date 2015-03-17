from score import *
def decide(l,p): # l=list dice, p=points so far
  if type(p)<>int or p<0:
    raise Exception("p not a natural number")
  s=points(l)
  m=[]
  while 1 in l:
    l.remove(1)
    l.append(1)
  while 5 in l:
    l.remove(5)
    l.append(5)
