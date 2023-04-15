package ru.nsu.perminov.main;

public class CycleBeginCommand implements ICommand
{
    @Override
    public void run(IContext context)
    {
        int currentPositionInInputFile = context.getCurrentPositionInInputFile();

        if (!context.emptyCallStack() && context.peekValueFromCallStack() < 0 || context.getValueInArray(context.getCurrentPositionInArray()) == 0)
        {
            context.setCurrentPositionInInputFile(++currentPositionInInputFile);
            context.pushValueInCallStack(-1);
            return;
        }
        context.pushValueInCallStack(currentPositionInInputFile);
        context.setCurrentPositionInInputFile(++currentPositionInInputFile);
    }
}
