package ru.nsu.perminov.main;

import java.util.Stack;

public class IncrementDataCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }
        array[currentPosition.inArray]++;
        if (array[currentPosition.inArray] > Constant.maxNumber - 1)
        {
            array[currentPosition.inArray] -= Constant.maxNumber;
        }
    }
}
