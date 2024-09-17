
PRKM = 31
PRKD = 1000000007

class rkHash:
    '''
    rk.py file is part of Algosnippet.
    Algosnippet is a collection of practice data-structures and algorithms
    Copyright (C) 2021  Kamanashis Roy
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

    def __init__(self, sz=0):
        self.h = 0
        self.q = deque()
        self.shift = 1
        self.sz = sz
        for _ in range(sz):
            self.shift *= PRKM
            self.shift %= PRKD

    def push(self, x):
        self.pop()
        self.h += (x+1)
        self.h %= PRKD
        self.q.append(x+1)

    def pop(self):
        self.h *= PRKM
        if self.sz == 0:
            return
        if len(self.q) >= self.sz:
            y = self.q.popleft()
            self.h = self.h - (y*self.shift)

