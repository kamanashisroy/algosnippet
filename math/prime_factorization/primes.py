
def primes( biggest ):
    plist = []
    prime = [True]*(biggest+1)
    prime[0] = False
    prime[1] = False
    
    for i in range(2,biggest+1):
        if not prime[i]:
            continue
        plist.append(i)
        plen = len(plist)
        x = i+i
        while x <= biggest:
            prime[x] = False
            x += i
    print(plist)

primes(1000000)
