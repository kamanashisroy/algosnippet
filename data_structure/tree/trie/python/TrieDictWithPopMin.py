#GLOBAL_TRIE_ID = [0]
class Trie:
    def __init__(self, val=None,parent=None):
        self.val = val
        self.children = [None]*26
        #self.trid = GLOBAL_TRIE_ID[0]
        #GLOBAL_TRIE_ID[0] += 1
        self.explored = False
        #self.popped = False
        self.parent = parent
        self.item = None

    def extend(self, givenS):
        cur = self
        for x in givenS:
            if cur.children[x] is None:
                cur.children[x] = Trie(x,cur)
            cur = cur.children[x]
        if cur.explored: # already explored
            return cur,False
        cur.explored = True
        return cur,True

    def popleft(self):
        cur = self
        output = []

        while not cur.explored:
            for i in range(26):
                if cur.children[i] is not None:
                    cur = cur.children[i]
                    output.append(cur.val)
                    break
            else:
                break
        if not cur.explored:
            return None

        cur.explored = False
        while not cur.explored and cur.parent is not None:
            for i in range(26):
                if cur.children[i] is not None:
                    break
            else:
                if cur.parent is not None:
                    par = cur.parent
                    par.children[cur.val] = None # unplug subtree
                    cur = par
                    continue
            break
        return bytearray(output)

    def __contains__(self, givenS):
        cur = self

        for x in givenS:
            if cur.children[x] is None:
                return False
            cur = cur.children[x]
        return cur.explored

    def __getitem__(self, givenS):
        cur = self

        for x in givenS:
            if cur.children[x] is None:
                return None
            cur = cur.children[x]
        if cur.explored:
            return cur.item
        return None

    def __setitem__(self, givenS, itemVal):
        cur,_ = self.extend(givenS)        
        cur.item = itemVal

    def add(self, givenS):
        self.__setitem__(givenS,1)
 
