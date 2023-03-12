package ru.nsu.perminov.main;

import ru.nsu.perminov.exception.SyntaxException;

import java.io.IOException;
import java.util.Stack;

public interface ICommand
{
    public void run(Compiler.IContext context) throws SyntaxException, IOException;
}
