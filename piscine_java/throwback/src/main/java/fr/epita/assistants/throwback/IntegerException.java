package fr.epita.assistants.throwback;

abstract public class IntegerException extends Exception {
    String args;
    abstract public String getMessage ();

}