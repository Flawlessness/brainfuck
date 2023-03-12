package ru.nsu.perminov.main;

import java.util.Stack;

public class OutputCommand implements ICommand
{
    @Override
    public void run(Compiler.IContext context)
    {
        context.setCurrentPositionInInputFile(context.getCurrentPositionInInputFile() + 1);
        if(!context.emptyCallStack() && context.peekValueFromCallStack() < 0)
        {
            return;
        }
        System.out.printf("%c", context.getValueInArray(context.getCurrentPositionInArray()));
    }
}
