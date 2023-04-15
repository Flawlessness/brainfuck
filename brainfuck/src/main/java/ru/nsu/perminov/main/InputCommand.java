package ru.nsu.perminov.main;

import java.io.IOException;


public class InputCommand implements ICommand
{
    @Override
    public void run(IContext context) throws IOException
    {
        context.setCurrentPositionInInputFile(context.getCurrentPositionInInputFile() + 1);
        if (!context.emptyCallStack() && context.peekValueFromCallStack() < 0)
        {
            return;
        }
        context.setValueInArray(context.getCurrentPositionInArray(), System.in.read());
    }
}
