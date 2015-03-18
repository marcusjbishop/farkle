# calculate possible point-scoring outcomes with n dice
from score import points 
def possibleOutcomes(n):
  if type(n)<>int or n<0:
    raise Exception("n not a natural number")
  if n==0:
    return [{'dice':[],'num':0,'prob':1,'score':0}]
  P=[x for x in tuples(range(6),6) if sum(x)==n]
  F=[x for x in P if x[0]==0 and x[4]==0 and
    x[1]<3 and x[2]<3 and x[3]<3 and x[5]<3]
  D=[]
  for x in P:
    if not x in F:
      m=multinomial(x)
      p=points(x)
      D.append({'dice':x,'num':m,'prob':m/6**n,'score':p})
  return D
