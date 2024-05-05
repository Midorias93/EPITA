from . import tree
from typing import Any

def name_contains(name: str) -> Any:
    """
    Filter to check if a person's name contains the given string.

    Parameters:
        - name: The string to use for the filter

    Returns:
        - Depends of your implementation
    """
    def check_person(tree: tree.Tree):
        return name in tree.person.name
    return check_person

def older_than(age: int) -> Any:
    """
    Filter to check if a person's age is greater than or equal to the given
    integer.

    Parameters:
        - age: minimum age

    Returns:
        - Depends of your implementation
    """
    def check_age(tree: tree.Tree):
        return tree.person.age >= age
    return check_age
    


def has_profession(profession: str) -> Any:
    """
    Filter to check if a person has a given profession.

    Parameters:
        - name: The profession to check

    Returns:
        - Depends of your implementation
    """
    def check_profession(tree: tree.Tree):
        #print(tree.person.profession,profession,tree.person.profession == profession) 
        return tree.person.profession == profession
    return check_profession

def at_least_nb_children(nb_children: int) -> Any:
    """
    Filter to check if a person has a least `nb_children` children.

    Parameters:
        - nb_children: minimum number of children to have

    Returns:
        - Depends of your implementation
    """
    def check_nb_children(tree: tree.Tree):
        return len(tree.children) >= nb_children
    return check_nb_children


def negation(subfilter: Any) -> Any:
    """
    Invert the given filter

    Parameters:
        - subfilter: type depends of your implementation -> The filter to invert

    Returns:
        - Depends of your implementation
    """
    def check_negation(parametre_sub: Any):
        return not(subfilter(parametre_sub))
    return check_negation
