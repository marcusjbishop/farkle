#!/usr/bin/python
import sys
from decide import *
f=open('/tmp/log','w')
def player():
  score=0
  while True:
    w=raw_input()
    f.write("Read "+w+"\n")
    dice=[int(x) for x in w]
    if dice==[0]:
      f.write("Farkled\n__________\n")
      score=0
      continue
    d=decide(dice,score)
    f.write("want to reroll "+str(d['reroll'])+"\n")
    score=d['score']
    s=''.join([str(x) for x in d['reroll']])
    s+='\n'
    print >>sys.stdout,s
    sys.stdout.flush()
    f.write("wrote "+s)
    if []==d['reroll']:
      f.write("__________\n")
      score=0
      continue

if __name__=='__main__':
  player()
