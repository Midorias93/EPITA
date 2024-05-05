package fr.epita.assistants.throwback;

public class PositiveIntegerException extends IntegerException {
    PositiveIntegerException (String args)
    {
        this.args = args;
    }
    @Override
    public String getMessage() {
        return "IntegerException: PositiveIntegerException: " + args;
    }
}