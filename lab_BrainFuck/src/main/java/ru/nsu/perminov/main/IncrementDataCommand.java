package ru.nsu.perminov.main;

import java.util.Stack;

public class IncrementDataCommand implements ICommand
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

        context.setValueInArray(currentPositionInArray, context.getValueInArray(currentPositionInArray) + 1);
        if (context.getValueInArray(currentPositionInArray) > Constant.maxNumber - 1)
        {
            context.setValueInArray(currentPositionInArray, context.getValueInArray(currentPositionInArray) - Constant.maxNumber);
        }
    }
}
