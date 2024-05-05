package fr.epita.assistants.throwback;

public class LongStringException extends StringException {
    LongStringException (String args) {
        this.args = args;
    }
    @Override
    public String getMessage() {
        return "StringException: LongStringException: " + args + " (length: " + args.length() + ")";
    }
}