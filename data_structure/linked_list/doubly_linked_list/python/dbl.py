#!python

from typing import TypeVar, Generic
#from __future__ import annotations


DBLXT = TypeVar('DBLXT')
class DBL(Generic[DBLXT]):
    __slots__ = ['x','fr','to']
    def __init__(self,x:DBLXT,fr:'DBL[DBLXT]' = None,to:'DBL[DBLXT]' = None):
        self.x:DBLXT = x
        self.to = to
        self.fr = fr

    def appendafter(self,y:DBLXT) -> None:
        to = self.to
        self.to = DBL(y, self, self.to)
        if to is not None:
            to.fr = self.to

    def appendright(self,y:DBLXT) -> 'DBL[DBLXT]':
        assert(self.to is None)
        self.to = DBL(y,self)
        return self.to

    def extendafter(self, other:List[DBLXT]) -> None:
        for x in other:
            self.appendafter(x)

    def join(self,y:'DBL[DBLXT]') -> None:
        if y:
            self.to = y
            y.fr = self
        else:
            self.to = None

    def drop(self) -> None:
        if self.to:
            self.to.fr = self.fr
        if self.fr:
            self.fr.to = self.to
 
    def __iter__(self) -> None:
        head = self
        while head:
            yield head.x
            head = head.to

    def linkeditems(self, skip_head:bool = True) -> None:
        head = self
        if head and skip_head:
            head = head.to
        while head:
            yield head,head.x
            head = head.to

 
