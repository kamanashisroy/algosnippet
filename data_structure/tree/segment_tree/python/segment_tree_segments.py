

class SegmentTreeNode:
    '''
    segment_tree_segments.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2024  Kamanashis Roy
    Algosnippet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Algosnippet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
    '''

    def __init__(self, pos, val, numLeaves):
        self.pos:int        = pos
        self.val = val
        self.isLeaf:bool    = False
        self.numLeaves:int  = numLeaves
        self.segments       = []
        self.beg            = self.pos
        self.end            = self.pos+1

        if 0 == self.pos:
            return # place-holder

        cur = self.pos
        while cur < numLeaves:
            cur <<= 1
        self.beg = cur
        cur = self.pos
        while cur < numLeaves:
            cur <<= 1
            cur += 1
        self.end = cur+1
    
    def __repr__(self):
        return 'pos={},({},{})'.format(self.pos, self.beg, self.end)
    
class SegmentTree:
    '''
    segment_tree_segments.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2024  Kamanashis Roy
    Algosnippet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    Algosnippet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with Algosnippet.  If not, see <https://www.gnu.org/licenses/>.
    '''
    def __init__(self, sz):
        x = 2
        while x < (sz+1):
            x <<= 1
        self.numLeaves = x
        # so there are self.numLeaves number of leaves
        # number of internal nodes == number of leaves
        # root = 1 , root.left = (1<<1) = 2, root.right = root.left+1 = 3
        # when numLeaves = 2, total nodes = 4
        total_nodes = self.numLeaves<<1
        self.items = [SegmentTreeNode(pos, None, self.numLeaves) for pos in range(total_nodes)]
    
    def split_at(self, idx:int) -> None:
        '''
        idx is 0 indexed.
        '''
        cur = self.numLeaves + idx
        while 0 != cur:
            for beg,end in self.process_deleted(cur, self.numLeaves+idx):
                yield (beg-self.numLeaves,end-self.numLeaves)
            assert(0 != cur)
            if 1 == cur:
                break
            cur >>= 1 # go to parent

    def push_segment(self, pos:int, beg:int, end:int) -> bool:
        if pos >= len(self.items):
            return False
        if self.items[pos] is None:
            self.items[pos] = SegmentTreeNode(pos,None, self.numLeaves)
        cur = self.items[pos]
        if beg < cur.beg or end > cur.end:
            return False
        if pos <= self.numLeaves:
            if not self.push_segment(pos<<1, beg, end):
                if not self.push_segment((pos<<1)+1, beg, end):
                    cur.segments.append((beg,end))
        else:
            cur.segments.append((beg,end))
        return True
 
    def __setitem__(self, begIdx:int,endIdx:int) -> bool:
        '''
        Insert a segment top-down
        '''
        return self.push_segment(1, begIdx+self.numLeaves, endIdx+self.numLeaves)

    def process_deleted(self, pos:int, deletedPos:int) -> None:
        cur = self.items[pos]
        target = 0
        for idx,(beg,end) in enumerate(cur.segments):
            if beg <= deletedPos and deletedPos < end:
                target = idx
                break
        else:
            return False
        
        beg,end = cur.segments[target]
        del cur.segments[target]
        yield (beg,end)

        if beg == deletedPos:
            yield (beg, beg+1)
            if end != (beg+1):
                yield (beg+1, end)
        else:
            if deletedPos == end:
                assert(deletedPos != end)
            yield (beg, deletedPos)
            if (deletedPos+1) != end:
                yield (deletedPos+1, end)
        return True


'''
Example,

stree = SegmentTree(N)
stree[beg] = end 	# insert interval (beg,end)
stree.split_at(pos) # split interval at pos

Used in this problem ,

https://leetcode.com/problems/maximum-segment-sum-after-removals/submissions/1198870783/
'''

