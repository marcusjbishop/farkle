from decide import *
def player():
  score=0
  while True:
    w=raw_input()
    dice=[int(x) for x in w.split(',')]
    if dice==[-1]:break
    d=decide(dice,score)
    score=d['score']
    print d['reroll']
    if []==d['reroll']:break
