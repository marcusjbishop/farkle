from decide import *
def player():
  score=0
  while True:
    w=raw_input()
    dice=[int(x) for x in w.split(',')]
    if l==[-1]:break
    d=decide(dice,score)
