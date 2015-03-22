#!/usr/bin/python
import sys
from decide import *
def player():
  f=open('/tmp/log','w')
  f.write('invoked\n');
  score=0
  while True:
    f.write("waiting\n");
    w=raw_input()
    dice=[int(x) for x in w]
    f.write('read '+w+'\n')
    if dice=="-1":break
    d=decide(dice,score)
    score=d['score']
    s=''.join([str(x) for x in d['reroll']])
    if s=='':s='-1'
    print >>sys.stdout,s
    sys.stdout.flush()
    f.write('wrote '+s+'\n')
    if []==d['reroll']:break

if __name__=='__main__':
  player()
