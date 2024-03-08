
from bisect import insort
from bisect import bisect_left

class HashTableBase:
  def __init__(self, size = 10):
    self.length = size
    self.count = 0
  
  def load_factor(self):
    return self.count / self.length
  
  def _hash(self, string):
    return sum(map(ord, string)) # Bad hashing algorithm, but please don't change. Gives predictable collisions for testing
  
  def _index(self, value):
    return value % self.length

    
class ProbingHashTable(HashTableBase):
  def __init__(self, length = 10):
    HashTableBase.__init__(self,length)
    self.table = [None]*length
    self.maxdist = [0]*length

    
  def add(self, key, value):
    if 0 == self.length:
      self.rehash()
    else:
      fac = (self.count+1)/self.length
      if fac >= 0.75:
        self.rehash()

    return self.insert_helper(key, value)

    
  def insert_helper(self, key, val):
    idx = HashTableBase._hash(self, key)
    home = idx%len(self.table)
    for dist in range(len(self.table)):
        curr = (home+dist)%len(self.table)
        if self.table[curr] is not None:
          curkey,curdist,curval = self.table[curr]
          if curdist < dist:
            # robinhood
            self.table[curr] = (key,dist,val)
            self.maxdist[home] = max(self.maxdist[home],dist)
            return self.insert_helper(curkey, curval)
          continue
        self.table[curr] = (key,dist,val)
        self.maxdist[home] = max(self.maxdist[home],dist)
        self.count += 1
        return True
    return False # no space left
    
  def lookup(self, key):
    if not self.table:
      return None
    idx = HashTableBase._hash(self, key)
    home = idx%len(self.table)
    for dist in range(self.maxdist[home]+1):
      curr = (home+dist)%len(self.table)
      if self.table[curr] is not None:
        curkey,curdist,curval = self.table[curr]
        if curkey == key:
          return curval
    return None
  
  def delete(self, key):
    if not self.table:
      return None
    idx = HashTableBase._hash(self, key)
    home = idx%len(self.table)
    for dist in range(self.maxdist[home]+1):
      curr = (home+dist)%len(self.table)
      if self.table[curr] is not None:
        curkey,curdist,curval = self.table[curr]
        if curkey == key:
          self.table[curr] = None # empty slot
          self.count -= 1
          return True
    return False
  
  def rehash(self,suggested=4):
    # double in table
    target_size = max(suggested,len(self.table)<<1)
    oldtable = self.table
    self.count = 0
    self.table = [None]*target_size
    self.maxdist = [0]*target_size
    self.length = target_size

    for elem in oldtable:
      if elem is None:
        continue
      key,dist,val = elem
      # insert in bigtable
      self.insert_helper(key,val)


class ChainingHashTable(HashTableBase):
  def __init__(self, length = 10):
    HashTableBase.__init__(self,length)
    self.buckets = [[] for _ in range(length)]
  
  def add(self, key, value):
    if 0 == self.length:
      self.rehash()
    else:
      fac = (self.count+1)/self.length
      if fac >= 1.5:
        self.rehash()
    return self.insert_helper(key,value)
      
  def insert_helper(self, key, value):
    idx = HashTableBase._hash(self, key)
    bidx = idx%len(self.buckets)
    insort(self.buckets[bidx],(key,value))
    self.count+=1;
    return True
    
  def lookup(self, key):
    if not self.buckets:
      return None
    idx = HashTableBase._hash(self, key)
    bidx = idx%len(self.buckets)
    pos = bisect_left(self.buckets[bidx],(key,''))
    if pos >= len(self.buckets[bidx]):
      return None
    k,v = self.buckets[bidx][pos]
    if k == key:
      return v
    return None

  def delete(self, key):
    if not self.buckets:
      return False
    idx = HashTableBase._hash(self, key)
    bidx = idx%len(self.buckets)
    pos = bisect_left(self.buckets[bidx],(key,''))
    if pos >= len(self.buckets[bidx]):
      return False
    k,v = self.buckets[bidx][pos]
    if k == key:
      del self.buckets[bidx][pos]
      self.count-=1;
      return True
    return False
  
  def rehash(self,suggested = 4):
    target_size = max(suggested, len(self.buckets)<<1)
    oldbuckets = self.buckets
    self.buckets = [[] for _ in range(target_size)]
    self.length = target_size

    for b in oldbuckets:
      for k,v in b:
        self.insert_helper(k,v)

#tab = ProbingHashTable()
tab = ChainingHashTable()
for x in range(100):
  tab.add(str(x),str(x))

for x in range(100):
  assert(tab.lookup(str(x)) == str(x))

for x in range(100):
  assert(True == tab.delete(str(x)))

for x in range(100):
  assert(tab.lookup(str(x)) is None)
