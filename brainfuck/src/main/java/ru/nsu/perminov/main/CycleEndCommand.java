package ru.nsu.perminov.main;

import ru.nsu.perminov.exception.SyntaxException;

public class CycleEndCommand implements ICommand
{
    @Override
    public void run(IContext context) throws SyntaxException
    {
        if (!context.emptyCallStack() && context.peekValueFromCallStack() < 0 || context.getValueInArray(context.getCurrentPositionInArray()) == 0)
        {
            if (context.emptyCallStack())
            {
                throw new SyntaxException("Unexpected closing bracket");
            }
            context.popValueFromCallStack();
            context.setCurrentPositionInInputFile(context.getCurrentPositionInInputFile() + 1);
            return;
        }
        context.setCurrentPositionInInputFile(context.popValueFromCallStack());
    }
}
