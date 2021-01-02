
# """
# This is HtmlParser's API interface.
# You should not implement it, or speculate about its implementation
# """
#class HtmlParser(object):
#    def getUrls(self, url):
#        """
#        :type url: str
#        :rtype List[str]
#        """


from threading import Thread
from threading import Lock
from threading import Condition
from queue import Queue


class HtmlParser(object):
    def __init__(self, urls, sub_urls):
        self.url_to_range = dict()
        self.urls = urls
        i = 0
        for x in urls:
            self.url_to_range[x] = sub_urls[i]
            i += 1

    def getUrls(self, url):
        """
        :type url: str
        :rtype List[str]
        """
        result = []
        idx,ignore = self.url_to_range[url]
        result.append(self.urls[idx])
        print(ignore,idx,result)
        return result

def get_host_name(givenUrl:str) -> str:
    parts = givenUrl.strip().split('/')
    hostIdx = 0
    token = parts[hostIdx]
    while True:
        if token == 'http:' or token == 'https:' or len(token) == 0:
            hostIdx += 1
            token = parts[hostIdx]
        else:
            break
    return token

class worker_loop:
    def __init__(self, idx, htmlParser, mediator):
        self.idx = idx
        self.parser = htmlParser
        self.mediator = mediator
        self.done = dict()
        self.q = Queue()

    def process(self):
        while True:
            topUrl = self.q.get()
            if topUrl == 'stop':
                break
            if topUrl not in self.done:
                target_host = get_host_name(topUrl)
                self.done[topUrl] = True
                for x in self.parser.getUrls(topUrl):
                    xhost = get_host_name(x)
                    if xhost == target_host:
                        self.mediator.dist(x)
                self.mediator.accum(self.idx, topUrl)
            self.mediator.add_pending(-1)

class main_loop:
    def __init__(self, N):
        self.N = N
        self.worker = []
        self.result = [[] for i in range(N)]
        self.pending_lock = Lock()
        self.pending_count = 0
        self.term_cond = Condition()

    def accum(self, src, x):
        self.result[src].append(x)          # no synchronization is needed here

    def dist(self, x):
        N = len(self.worker)
        self.add_pending(1)
        self.worker[hash(x)%N].q.put(x)     # thread synchronization happens in queue

    def add_pending(self, x):
        with self.pending_lock:
            self.pending_count += x
            if 0 == self.pending_count:
                with self.term_cond:
                    self.term_cond.notify()

    def run(self,startUrl: str, htmlParser: 'HtmlParser'):

        self.worker = [worker_loop(i, htmlParser,self) for i in range(self.N)]
        threads = [Thread(target=x.process) for x in self.worker]

        for x in threads:
            x.start()

        self.dist(startUrl)

        with self.term_cond:
            self.term_cond.wait(3)

        for w in self.worker:
            w.q.put('stop')

        for x in threads:
            x.join(2)


        explored = []
        for x in self.result:
            explored.extend(x)
        return explored


class Solution:

    def crawl(self, startUrl: str, htmlParser: 'HtmlParser'):
        m = main_loop(2)

        return m.run(startUrl, htmlParser)




if __name__ == "__main__":
    urls = ["http://news.yahoo.com","http://news.yahoo.com/news","http://news.yahoo.com/news/topics/","http://news.google.com","http://news.yahoo.com/us"]
    search_results = [[2,0],[2,1],[3,2],[3,1],[0,4]]
    start_url = "http://news.yahoo.com/news/topics/"

    parser = HtmlParser(urls, search_results)
    sln = Solution()
    print(sln.crawl(start_url, parser))

    

