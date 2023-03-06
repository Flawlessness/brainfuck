package ru.nsu.perminov.main;

import java.util.Stack;

public class IncrementPointerCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }
        if (currentPosition.inArray == Constant.arraySize - 1)
        {
            throw new ArrayIndexOutOfBoundsException("Index 30000 out of bounds for length 30000");
        }
        currentPosition.inArray++;
    }
}
