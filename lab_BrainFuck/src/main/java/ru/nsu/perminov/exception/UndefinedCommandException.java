package ru.nsu.perminov.exception;
public class UndefinedCommandException extends Exception
{
    public UndefinedCommandException(String message)
    {
        super(message);
    }
    public UndefinedCommandException(String message, Throwable cause)
    {
        super(message, cause);
    }
}
