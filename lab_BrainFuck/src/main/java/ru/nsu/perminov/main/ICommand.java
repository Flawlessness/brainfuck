package ru.nsu.perminov.main;

import ru.nsu.perminov.exception.SyntaxException;
import java.util.Stack;

public interface ICommand
{
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition) throws SyntaxException;
}
