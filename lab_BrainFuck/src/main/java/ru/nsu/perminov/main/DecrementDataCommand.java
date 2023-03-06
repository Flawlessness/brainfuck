package ru.nsu.perminov.main;

import java.util.Stack;

public class DecrementDataCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }

        array[currentPosition.inArray]--;
        if (array[currentPosition.inArray] < 0)
        {
            array[currentPosition.inArray] += Constant.maxNumber;
        }
    }
}
