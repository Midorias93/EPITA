package fr.epita.assistants.throwback;

public class ShortStringException extends StringException {
    ShortStringException (String args)
    {
        this.args = args;
    }
    @Override
    public String getMessage() {

        return "StringException: ShortStringException: " + args + " (length: " + args.length() + ")";
    }
}