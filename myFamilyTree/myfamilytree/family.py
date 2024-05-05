from . import person as mftperson
from . import tree as mfttree
import shutil
from pathlib import Path
import pathlib
from typing import Any

class Family:
    """
    A class used to represent a family.

    Attributes:
        - tree: Tree -> The family tree
        - path: Path -> The path to the parent directory of the first node of
        the tree
    """

    def __init__(self, path: Path, tree: mfttree.Tree | None = None):
        """
        Parameters:
            - path: The path to the parent directory of the first node
            of `tree`
            - tree: The family tree, None by default
        """
        self.path: Path = path
        self.tree: mfttree.Tree = tree


    def add_child(self, child: mftperson.Person, path: Path) -> None:
        """
        Add a new child to the person at the given path. If the family is
        empty, you have to create a new one.

        Parameters:
            - child: The new child to add
            - path: The path to the parent of the child
        """
        if not path.exists():
            return None
        if self.tree == None:
            self.tree = mfttree.Tree(child)
            chemin_str = path.__str__() + "/" + child.name
            chemin = Path(chemin_str)
            chemin.mkdir()
            path_str = path.__str__()+"/"+child.name 
            mftperson.person_to_file(child,Path(path_str))
        else:
            tree_endroit = self.tree
            ancestors = list(path.relative_to(self.path).parts)
            chemin = self.path.joinpath(ancestors[0])
            for x in ancestors[1:]:
                chemin = chemin.joinpath(x)
                tree_endroit = tree_endroit.find_child(x)
                if tree_endroit == None:
                    return None
            tree_endroit.add_child(mfttree.Tree(child))
            chemin_str = path.__str__() + "/" + child.name
            chemin = Path(chemin_str)
            chemin.mkdir()
            path_str = path.__str__() + "/" + child.name
            mftperson.person_to_file(child,Path(path_str))




    def reunite(self, path: Path) -> None:
        """
        Copy every 'name.info' file in the family into the
        target directory.

        Parameters:
            - path: The path to the target directory
        """
        def aux(path_src,path_dst):
            for x in path_src.iterdir():
                if x.is_file():
                    shutil.copy(x,path_dst)
                if x.is_dir():
                    aux(x,path_dst)
        aux(self.path.joinpath(self.tree.person.name),path)

    def apply_filters(self, filters: list[Any]) -> list[mftperson.Person]:
        """
        Return a list of filtered family members.

        Parameters:
            - filters: list of filters to apply

        Returns:
            - A list of filtered members

        """
        def creation_list(abr,L):
            L.append(abr)
            for x in abr.children:
                creation_list(x,L)
            
        L=[]
        creation_list(self.tree,L)
        for w in filters:
            M=[]
            for x in L:
                if w(x):
                    M.append(x)
            L=M   
        M=[] 
        for x in L:
            M.append(x.person)
        return M



def from_path(path: Path) -> Family | None:
    """
    Build a new Family from the given Path.

    The given path points to the parent directory of the tree which contains the
    first family member.

    Parameters:
        - path: The path pointing to the root directory of the family

    Returns:
        - The built Family using the given path. None if the given path does
           not correspond to a valid family.

    """
    tree = mfttree.construct(path)
    if tree == None:
        return None
    return Family(path.parent,tree)
