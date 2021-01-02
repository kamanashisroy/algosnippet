
The idea is to distribute the nodes into different threads or processes.

```python
class worker_loop:
    def __init__(self, idx, htmlParser, mediator):
        self.idx = idx
        self.parser = htmlParser
        self.mediator = mediator
        self.done = dict()
        self.q = Queue()                                # Message queue

    def process(self):
        while True:
            topUrl = self.q.get()
            if topUrl == 'stop':                        # Terminate worker
                break
            if topUrl not in self.done:
                target_host = get_host_name(topUrl)
                self.done[topUrl] = True
                for x in self.parser.getUrls(topUrl):
                    xhost = get_host_name(x)
                    if xhost == target_host:
                        self.mediator.dist(x)           # distribute subtask
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
                    self.term_cond.notify()     # notify main thread when no more pending tasks

    def run(self,startUrl: str, htmlParser: 'HtmlParser'):

        self.worker = [worker_loop(i, htmlParser,self) for i in range(self.N)]
        threads = [Thread(target=x.process) for x in self.worker]

        for x in threads:
            x.start()

        self.dist(startUrl)

        with self.term_cond:
            self.term_cond.wait(3)

        for w in self.worker:           # send stop to all workers
            w.q.put('stop')

        for x in threads:               # wait for all workers to end
            x.join(2)


        explored = []
        for x in self.result:
            explored.extend(x)
        return explored


```


Links
=======

- [Web crawler](https://leetcode.com/problems/web-crawler-multithreaded/)
