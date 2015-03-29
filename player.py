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
    if dice=="-1":break
    d=decide(dice,score)
    f.write("want to reroll "+str(d['reroll'])+"\n")
    score=d['score']
    s=''.join([str(x) for x in d['reroll']])
    s+='\n'
    print >>sys.stdout,s
    if []==d['reroll']:
      f.write("__________\n")
      score=0
    f.write("wrote "+s+"\n")

if __name__=='__main__':
  player()
