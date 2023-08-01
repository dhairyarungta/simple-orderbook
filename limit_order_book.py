import logging
import time 
from itertools import islice


log = logging.getLogger(__name__)


class LimitOrderBook: 
    def __init__(self):
        self.bids = LimitLevelTree()
        self.asks = LimitLevelTree()
        self.best_bid = None
        self.best_ask = None 
        self._price_levels = {}
        self._orders = {}
    
    @property
    def top_level(self):
        #Returns the best available bid and ask
        return self.best_bid, self.best_ask
    
    def process(self, order)
        


class LimitLevel:
    #AVL BST Node
    __slots__ = ['price', 'size', 'parent','left_child','right_child',
                'head', 'tail', 'count', 'orders' ]
    
    def __init__(self, order) -> None:
        self.price = order.price
        self.size = order.size 





class LimitLevelTree:
    #AVL BST Root Node
    __slots__ = ['right_child', 'is_root']
    
    def __init__(self):
        self.right_child = None
        self.is_root = True

    def insert(self,limit_level)

class OrderList:
    #Doubly linked list, list class 

    __slots__ = ['head', 'tail', 'parent_limit', 'count']
    
    def __init__(self) -> None:
        self.head = None 
        self.tail = None
        self.count = 0
        self.parent_limit = parent_limit


class Order:
    #Order item node of the doubly linked list 
    __slots__ = ['uid', 'is_bid', 'size', 'price', 'timestamp', 'next_item',
                 'previous_item', 'root']
    
    def __init__(self, uid, is_bid, size, price, root = None,
                 timestamp = None, next_item = None, previous_item =None ) -> None:
        self.uid = uid
        self.is_bid = is_bid
        self.price = price 
        self.size = size 
        self.timestamp = timestamp if timestamp else time.time()
        
        self.next_item= next_item
        self.previous_item = previous_item
        self.root = root

    
    @property 
    def parent_limit(self):
        return self.root.parent_limit

    def append(self, order):
        #append the next order
        if self.next_item is None :
            self.next_item = order
            self.next_item.previous_item = self
            self.next_item.root = self.root

            self.root.count +=1
            self.root.tail = order
            self.parent_limit.size +=order.size
        else :
            self.next_item.append(order)

    def pop_from_list(self):
        #remove from doubly linked list 
        #return: order instance as tuple 
        if self.previous_item is None:
            #self item is head of list
            self.root.head = self.next_item
            if self.next_item:
                self.next_item.previous_item = None
        
        if self.next_item is None:
            #self item is tail of list
            self.root.tail = self.previous_item
            if self.previous_item: 
                self.previous_item.next_item = None
        
        #updating limit level and root attributes
        self.root.count-=1
        self.parent_limit.size-=self.size

        return self.__repr__()
    
    def __str__(self):
        return self.__repr__()
    
    def __repr__(self) -> str:
        return str((self.uid,self.is_bid, self.price, self.size, self.timestamp))



            


