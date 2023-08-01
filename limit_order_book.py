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
    
    def process(self, order):
        #process the order
        if order.size ==0:
            self.remove(order)
    
    def update(self, order):

    def remove(self, order):
    
    def add(self, order):

    def levels(self, depth = None):
        


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
    

    def append (self, order):
        #Wrapper for append in OrderList
        return self.orders.append(order)
    
    def _replace_node_in_parent(self, new_value = None):
        
        if not self.is_root:
            if self==self.parent.left_child:
                self.parent.left_child = new_value
            else :
                self.parent.right_child= new_value

        if new_value:
            new_value.parent = self.parent
        
    def remove(self):
        #Delete this particular limit level
        if self.left_child and self.right_child:
            succ = self.right_child.min
            
            self.left_child, succ.left_child = succ.left_child, self.left_child
            self.right_child, succ.right_child = succ.right_child, self.right_child
            self.parent, succ.parent = succ.parent, self.parent
            self.remove()
            self.balace_grandpa()

        elif self.left_child:
            self._replace_node_in_parent(self.left_child)
        elif self.right_child:
            self._replace_node_in_parent(self.right_child)
        else:
            self._replace_node_in_parent(None)

    def balance_grandpa(self):
        #checks if grandparent needs replacing

        if self.grandpa and self.grandpa.is_root:
            pass 
        elif self.grandpa and not self.grandpa.is_root:
            self.grandpa.balance()
        elif self.grandpa is None:
            pass
        else :
            raise NotImplementedError
        return 
    def balance(self):
        #Rotation method for the node's balance factor 
        if self.balance_factor>1:
        #right subtree heavier 
            if self.right_child.balance_factor<0:
            #right_child.left is heavier 
                self._rl_case()
            elif self.right_child.balance_factor>0:
            #right_child.right is heavier 
                self._rr_case()
        elif self.balance_factor<-1
        #left is heavier 
            if self.left_child.balance_factor<0:
                self._ll_case()
            elif self.left_child.balance_factor>0:
                self._lr_case()
        
        else :
            pass 

        if not self.is_root and not self.parent.is_root:
            self.parent.balance()


    def _ll_case(self):
        #rotate nodes for ll case
        child= self.left_child
        if self.parent.is_root or self.price>self.parent.price:
            self.parent.right_child = child 
        else :
            self.parent.left_child = child 

        child.parent, self.parent = self.parent , child 
        child.right_child , self.left_child  = self, child.right_child 

    def _rr_case(self):
        #rotate nodes for rr case

        child = self.right_child
        if self.parent.is_root or self.price >self.parent.price:
            self.parent.right_child = child
        else :
            self.parent.left_child = child 
        

        child.parent, self.parent = self.parent, child
        child.left_child, self.right_child = self, child.left_child
    
    def _lr_case(self):
        #rotate nodes for lr case 
        child, grand_child = self.left_child, self.left_child.right_child 
        child.parent, grand_child.parent = grand_child, self
        child.right_child = grand_child.left_child 
        self.left_child, grand_child.left_child = grand_child, child
        self._ll_case()


    def _rl_case(self):
        #rotate nodes in rl case
        child, grand_child = self.right_child, self.right_child.left_child 
        child.parent, grand_child.parent = grand_child, self
        child.left_child = grand_child.right_child 
        self.right_child,grand_child.right_child = grand_child, child
        self._rr_case()


    def __str__(self):
        if not self.is_root:
            s = 'Node Value %s\n'%self.price
            s+='Node left_child value: %s\n'%(self.left_child.price if self.left_child else 'None')
            s+='Node right child value: %s\n\n'%(self.right_child.price if self.right_child else 'None')
        else : 
            s = ''

        left_side_print =self.left_child.__str__() if self.left_child else ''
        right_side_print = self.right_child.__str__() if self.right_child else ''
        return s + left_side_print +right_side_print 
    
    


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
                    current_node.right_child = limit_level
                    current_node.right_child.parent = current_node
                    current_node.right_child.balance_grandpa()
                    break
                else :
                    current_node - current_node.right_child
                    continue
            elif limit_level.price< current_node.price:
                if current_node.left_child is None :
                    current_node.left_child = limit_level
                    current_node.left_child.parent = current_node
                    current_node.left_child.balace_grandpa()
                    break
                else :
                    current_node = current_node.left_child
                    continue
            else :
                break
            
        

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
    
    def append (self,order):
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



            


