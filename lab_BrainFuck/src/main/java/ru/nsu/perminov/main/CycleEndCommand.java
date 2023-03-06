package ru.nsu.perminov.main;

import java.util.Stack;
import ru.nsu.perminov.exception.SyntaxException;
public class CycleEndCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition) throws SyntaxException
    {
        if(!callStack.empty() && callStack.peek() < 0 || array[currentPosition.inArray] == 0)
        {
            if (callStack.empty())
            {
                throw new SyntaxException("Unexpected closing bracket");
            }
            callStack.pop();
            currentPosition.inInputFile++;
            return;
        }
        currentPosition.inInputFile = callStack.pop();
    }
}
