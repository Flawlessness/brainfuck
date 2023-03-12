package ru.nsu.perminov.main;

import java.util.Stack;

public class CycleBeginCommand implements ICommand
{
    @Override
    public void run(Compiler.IContext context)
    {
        int currentPositionInInputFile = context.getCurrentPositionInInputFile();

        if(!context.emptyCallStack() && context.peekValueFromCallStack() < 0 || context.getValueInArray(context.getCurrentPositionInArray()) == 0)
        {
            context.setCurrentPositionInInputFile(++currentPositionInInputFile);
            context.pushValueInCallStack(-1);
            return;
        }
        context.pushValueInCallStack(currentPositionInInputFile);
        context.setCurrentPositionInInputFile(++currentPositionInInputFile);
    }
}
