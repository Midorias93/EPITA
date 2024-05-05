from __future__ import annotations
from . import person
from pathlib import Path

class Tree:
    """
    A class used to represent a general Tree.

    Attributes:
        - person: Person -> The person associated with this node
        - children: list[Tree] -> List of children nodes
    """

    def __init__(self, person: person.Person, children: list[Tree] | None = None):
        """
        Parameters:
            - person: The person associated with this node
            - children: List of children nodes, None by default. If None, the
            attribute need to be initialized with an empty list
        """
        self.person: Person = person
        if children == None:
            self.children = []
        else:
            self.children = children



    def add_child(self, child: Tree) -> None:
        """
        Add a new child to the node.

        Parameters:
            - child: The node to add
        """
        self.children.append(child)



    def pretty_print(self) -> None:
        """
        Print the tree on the standard output.
        """
        def profondeur(self, p = 0):
            if self == None:
                print()
            else:
                print(p*"  "+self.person.name)
                for x in self.children:
                    profondeur(x,p+1)
        profondeur(self)



    def find_child(self, name: str) -> Tree | None:
        """
        Returns This node's child that matches `name`.

        Parameters:
            - name: the name of the chid to find

        Returns:
            - The child named `name` or None if not found
        """
        if self == None:
            return None
        else: 
            for x in self.children:
                if x.person.name == name:
                    return x
            return None



    def find_child_index(self, name: str) -> int:
        """
        Returns this node's child index that matches `name`.

        Parameters:
            - name: the name of the child to find

        Returns:
            - The index of the child named `name` or -1 if not found
        """
        if self == None:
            return -1
        for i in range(len(self.children)):
            if self.children[i].person.name == name:
                return i
        return -1


def list_de_tous(path):
    chemin = [path.__str__()]
    for x in path.iterdir():
        chemin.append(x.__str__())
        if x.is_dir():
            list_de_tous(x)
    return chemin
def path_valid(L):
    dic = {}
    for x in L:
        if "info" in x:
            dic[x] = 0
    for x in L:
        if not("info" in x):
            for cle in dic:
                if x in cle:
                    dic[cle]=x
    for cle in dic:
        if dic[cle] == 0 :
            return False
    return True

def construct(src_path: Path) -> Tree | None:
    """
    Build a new Tree from `src_path`.

    Parameters:
        - src_path: The source path for the new tree

    Returns:
        - The built tree using `src_path` or None if `src_path` does not
        correspond to a valid tree
    """
    l=[]
    arbre = None
    if not(src_path.exists()):
        return None
    if path_valid(list_de_tous(src_path)):

        for x in src_path.iterdir():
            if x.is_file():
                arbre = Tree(person.person_from_file(x))
            if x.is_dir():
                cont=construct(x)
                a=True
                i = 0
                while a and i<len(l):
                    if l[i].person.name>cont.person.name:
                        l.insert(i,cont)
                        a=False
                    i += 1
                if a:
                    l.append(cont)
        for x in l:
            arbre.add_child(x)
        return arbre
    else :
        return None
