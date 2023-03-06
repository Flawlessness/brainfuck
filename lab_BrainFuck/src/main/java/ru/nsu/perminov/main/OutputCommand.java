package ru.nsu.perminov.main;

import java.util.Stack;

public class OutputCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }
        System.out.printf("%c", array[currentPosition.inArray]);
    }
}
