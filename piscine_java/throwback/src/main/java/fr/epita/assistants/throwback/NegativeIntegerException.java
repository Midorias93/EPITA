package fr.epita.assistants.throwback;

public class NegativeIntegerException extends IntegerException {
    public NegativeIntegerException(String args) {
        this.args = args;
    }
    @Override
    public String getMessage() {
       return "IntegerException: NegativeIntegerException: " + args;
    }
}