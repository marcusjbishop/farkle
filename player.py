#!/usr/bin/python
import sys
from decide import *
def player():
  score=0
  while True:
    w=raw_input()
    dice=[int(x) for x in w]
    if dice=="-1":break
    d=decide(dice,score)
    score=d['score']
    s=''.join([str(x) for x in d['reroll']])
    if s=='':s='-1'
    print >>sys.stdout,s
    if []==d['reroll']:break

if __name__=='__main__':
  player()
