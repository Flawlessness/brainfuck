package ru.nsu.perminov.main;
import java.util.Stack;

public class DecrementPointerCommand implements ICommand
{
    @Override
    public void run(Compiler.IContext context)
    {
        context.setCurrentPositionInInputFile(context.getCurrentPositionInInputFile() + 1);
        if(!context.emptyCallStack() && context.peekValueFromCallStack() < 0)
        {
            return;
        }

        int currentPositionInArray = context.getCurrentPositionInArray();

        if (currentPositionInArray == 0)
        {
            throw new ArrayIndexOutOfBoundsException("Index -1 out of bounds for length 30000");
        }
        context.setCurrentPositionInArray(--currentPositionInArray);
    }
}
