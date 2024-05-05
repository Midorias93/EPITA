package fr.epita.assistants.throwback;

public class UnknownException extends Exception {
    String args;
    UnknownException (String args)
    {
        this.args = args;
    }
    public String getMessage() {
        return "UnknownException: "+ args;
    }
}