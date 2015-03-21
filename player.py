#!/usr/bin/python
import sys
from decide import *
def player():
  f=open('/tmp/log','w')
  score=0
  while True:
    w=raw_input()
    dice=[int(x) for x in w.split(',')]
    f.write('read '+str(dice)+'\n')
    if dice==[-1]:break
    d=decide(dice,score)
    score=d['score']
    print >>sys.stdout,str(d['reroll'])+'\n'
    f.write('wrote'+str(d['reroll'])+'\n')
    if []==d['reroll']:break

if __name__=='__main__':
  player()
