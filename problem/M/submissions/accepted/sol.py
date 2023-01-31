def gen(k):
    siz = len(k)
    ans = []
    num = ['0','1','2','3','4','5','6','7','8','9']
    for i in range(1,10):
        temp = num[i]+ k[1:]
        if(k!=temp):
            ans.append(temp)
    for i in range(1,siz):
        for j in num:
            temp = k[:i]+j+k[i+1:]
            if(k!=temp):
                ans.append(temp)
    return ans
def is_valid(now):
    prime = [2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]
    used = [0]*101
    siz  = len(prime)
    ans = []
    temp = int(now)
    i = 0
    while(i<siz):
        if (temp%prime[i])==0:
            temp //= prime[i] 
            used[prime[i]]+=1
        else:
            i+=1
    fac = 1
    if temp ==1:
        for i in used:
           fac *= (i+1) 
        return (now,str(fac))
    return (-1,-1)
def good(k,k_):
    if(len(k)!=len(k_)):
        return False
    wrong =0
    for i in range(len(k)):
        if(k[i]!=k_[i]):
            wrong +=1
    if wrong ==1:
        return True
    return False

def __solve():
    now = input()
    n_,k_ = now.split(" ")
    n = gen(n_)#n list;
    temp= []
    for nn in n:
        posi = is_valid(nn)
        if(posi != (-1,-1)):
            temp.append(posi)
    temp.sort()
    for posi in temp:
        #print(posi)
        if(good(k_,posi[1])):
            print(posi[0]+" "+posi[1])
            return
if __name__ =="__main__":
    _ = input()
    _ = int(_)
    for p in range(0,_):    
        __solve()
