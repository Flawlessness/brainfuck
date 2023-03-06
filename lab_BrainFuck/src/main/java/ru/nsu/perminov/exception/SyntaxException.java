package ru.nsu.perminov.exception;
public class SyntaxException extends Exception
{
    public SyntaxException(String message)
    {
        super(message);
    }
    public SyntaxException(String message, Throwable cause)
    {
        super(message, cause);
    }
}