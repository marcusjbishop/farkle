#!/usr/bin/python
import sys
from decide import *
def game():
  score=0
  turnOver=False
  while not turnOver:
    w=raw_input()
    dice=[int(x) for x in w]
    if 0==points(d2v(dice)):
      return 0
    d=decide(dice,score)
    score=d['score']
    s=''.join([str(x) for x in d['reroll']])
    s+='\n'
    print >>sys.stdout,s
    sys.stdout.flush()
    if []==d['reroll'] and not d['xTurn']:
      turnOver=True 
  return score

if __name__=='__main__':
  game()

#f=open('/tmp/log','w')
#    f.write("Read "+w+"\n")
#    f.write("want to reroll "+str(d['reroll'])+"\n")
#    f.write("wrote "+s)
#      f.write("__________\n")
