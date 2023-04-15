package ru.nsu.perminov.main;

import ru.nsu.perminov.exception.SyntaxException;

import java.io.IOException;

public interface ICommand
{
    void run(IContext context) throws SyntaxException, IOException;
}
