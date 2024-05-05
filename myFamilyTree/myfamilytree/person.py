from pathlib import Path

class Person:
    """
    A class used to represent a family member

    Attributes:
        - name: str -> The person's name
        - age: int -> The person's age
        - profession: str -> The person's profession
    """

    def __init__(self, name: str, age: int, profession: str = "Unemployed"):
        """
        Parameters:
            - name: The person's name
            - age: The person's age
            - profession: The person's profession
        """
        self.name: str = name
        self.age: int  = age
        self.profession: str = profession


    def pretty_print(self) -> None:
        """
        Print the person's information.
        """
        print(self.name,"("+str(self.age)+"):",self.profession)



def person_from_file(path: Path) -> Person:
    """
    Build a new Person from a Path object

    Parameters:
        - path: The source path for the file containing the person's
        information.

    Returns:
        - The built person using the file's information.

    """
    path_str = path.__str__()
    file = open(path_str,"r")
    contenu_file = []
    for ligne in file.readlines():
        contenu_file.append(ligne[:len(ligne)-1])
    return Person(str(contenu_file[0]),int(contenu_file[1]),str(contenu_file[2]))
 

def person_to_file(person: Person, path: Path) -> None:
    """
    Save a person's information into a file under the given directory.

    Parameters:
        - person: The Person whose information will be saved
        - path: The path to the directory that will contain the file

    """


    file = open(path.__str__()+"/{name}.info".format(name = person.name),"x")
    file.write("{name}\n{age}\n{profession}\n".format(name = person.name, age = person.age, profession = person.profession))


