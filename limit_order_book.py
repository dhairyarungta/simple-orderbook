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

        self.parent = None 
        self.left_child = None
        self.right_child = None

        self.orders = OrderList(self)
        self.append(order)
    
    @property 
    def is_root(self):
        return isinstance(self.parent, LimitLevelTree)
    
    @property
    def volume(self):
        return self.price*self.size
    
    @property
    def balance_factor(self):
        #Return the balance value of this particualr node

        right_height = self.right_child.height if self.right_child else 0
        left_height = self.left_child.height if self.left_child else 0

        return right_height-left_height
    
    @property
    def grandpa(self):
        try:
            if self.parent:
                return self.parent.parent
            else :
                return None
        
        except AttributeError:
            return None
    
    @property
    def height (self):
        #Return the height of this node 
        left_height = self.left_child.height if self.left_child else 0
        right_height = self.right_child.height if self.right_child else 0
        if left_height>right_height:
            return left_height+1
        else :
            return right_height+1
        
    @property
    def min(self):
        #return smallest node under this node

        minimum = self
        while minimum.left_child:
            minimum = minimum.left_child
        return minimum
    

    def append (self, order)
        #Wrapper for append in OrderList
        return self.orders.append(order)
    
    def _replace_node_in_parent(self, new_value = None)
        
    def remove(self):
        #Delete this particular limit level
        

    def __len__(self):
        return len(self.orders)





class LimitLevelTree:
    #AVL BST Root Node
    __slots__ = ['right_child', 'is_root']
    
    def __init__(self):
        self.right_child = None
        self.is_root = True

    def insert(self,limit_level):
        current_node = self
        while True:
            if current_node.is_root or limit_level.price>current_node.price:
                if current_node.right_child is None :
                    current_node
            
            
        

class OrderList:
    #Doubly linked list, list class 

    __slots__ = ['head', 'tail', 'parent_limit', 'count']
    
    def __init__(self) -> None:
        self.head = None 
        self.tail = None
        self.count = 0
        self.parent_limit = parent_limit
    
    def __len__ (self):
        return self.count
    
    def append (self,order)
        #Append order to this list 
        if self.tail is None :
            order.root = self 
            self.tail = order
            self.head = order 
            self.count +=1

        else :
            self.tail.append(order)


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



            


