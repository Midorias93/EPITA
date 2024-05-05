package fr.epita.assistants.throwback;

abstract public class StringException extends Exception{
   String args;
   abstract public String getMessage();
}