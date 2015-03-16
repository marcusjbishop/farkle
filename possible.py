# calculate possible point scoring outcomes with n dice
n=3
P=[x for x in tuples(range(6),6) if sum(x)==n]
F=[x for x in P if x[0]==0 and x[4]==0 and
  x[1]<3 and x[2]<3 and x[3]<3 and x[5]<3]
D=[]
for x in P:
  if not x in F:
    D.append({'dice':x,'num':multinomial(x),'prob':multinomial(x)/6**n})
