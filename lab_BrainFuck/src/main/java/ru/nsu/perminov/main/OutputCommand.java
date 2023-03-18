package ru.nsu.perminov.main;

public class OutputCommand implements ICommand
{
    @Override
    public void run(IContext context)
    {
        context.setCurrentPositionInInputFile(context.getCurrentPositionInInputFile() + 1);
        if (!context.emptyCallStack() && context.peekValueFromCallStack() < 0)
        {
            return;
        }
        System.out.printf("%c", context.getValueInArray(context.getCurrentPositionInArray()));
    }
}
