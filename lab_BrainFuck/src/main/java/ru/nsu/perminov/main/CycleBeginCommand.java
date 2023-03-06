package ru.nsu.perminov.main;

import java.util.Stack;

public class CycleBeginCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        if(!callStack.empty() && callStack.peek() < 0 || array[currentPosition.inArray] == 0)
        {
            currentPosition.inInputFile++;
            callStack.push(-1);
            return;
        }
        callStack.push(currentPosition.inInputFile++);
    }
}
