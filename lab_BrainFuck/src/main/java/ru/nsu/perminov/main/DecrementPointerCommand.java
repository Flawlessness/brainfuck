package ru.nsu.perminov.main;
import java.util.Stack;

public class DecrementPointerCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }
        if (currentPosition.inArray == 0)
        {
            throw new ArrayIndexOutOfBoundsException("Index -1 out of bounds for length 30000");
        }
        currentPosition.inArray--;
    }
}
