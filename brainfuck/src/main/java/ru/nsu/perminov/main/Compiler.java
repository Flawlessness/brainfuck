package ru.nsu.perminov.main;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import ru.nsu.perminov.exception.*;

import java.io.IOException;
import java.io.Reader;
import java.util.HashMap;
import java.util.Scanner;
import java.util.Stack;

public class Compiler
{
    private final IContext context;
    private static final Logger LOG = LogManager.getLogger(Compiler.class);
    private final CommandFactory factory;
    private final Reader inputFile;
    private final HashMap<Character, ICommand> availableCommands;

    public Compiler(Reader configFile, Reader inputFile) throws FileFormatException
    {
        LOG.debug("{} class constructor is running", LOG.getName());
        this.context = new Context();
        this.factory = new CommandFactory(configFile);
        this.inputFile = inputFile;
        availableCommands = new HashMap<>();
        LOG.debug("{} class constructed successfully", LOG.getName());
    }

    public void runProgram() throws IOException, ClassNotFoundException, InstantiationException, IllegalAccessException, UndefinedCommandException, SyntaxException, FileFormatException
    {
        LOG.debug("Starting program execution");
        Scanner inputFileScanner = new Scanner(this.inputFile);
        if (!inputFileScanner.hasNextLine())
        {
            throw new FileFormatException("Code is missing");
        }
        String inputCommands = inputFileScanner.nextLine();
        Character currentCommand;
        while (context.getCurrentPositionInInputFile() != inputCommands.length())
        {
            currentCommand = inputCommands.charAt(context.getCurrentPositionInInputFile());
            LOG.trace("Current position in the executable file: \"{}\"", context.getCurrentPositionInInputFile());
            LOG.trace("The current value in {} cell of the array: \"{}\"", context.getCurrentPositionInArray(), context.getValueInArray(context.getCurrentPositionInArray()));
            LOG.trace("Run command execution: \"{}\"", currentCommand);
            if (!this.availableCommands.containsKey(currentCommand))
            {
                availableCommands.put(currentCommand, factory.create(currentCommand));
            }
            availableCommands.get(currentCommand).run(context);
        }
        LOG.debug("The program was successfully implemented");
    }
}

class Position
{
    Position(int inArray, int inInputFile)
    {
        this.inArray = inArray;
        this.inInputFile = inInputFile;
    }

    public int inArray;
    public int inInputFile;
}

class Constant
{
    final static int arraySize = 30000;
    final static int maxNumber = 256;
}

class Context implements IContext
{
    private final int[] array;
    private final Position currentPosition;
    private final Stack<Integer> callStack;

    Context()
    {
        this.array = new int[Constant.arraySize];
        this.currentPosition = new Position(0, 0);
        this.callStack = new Stack<>();
    }

    public int getCurrentPositionInInputFile()
    {
        return currentPosition.inInputFile;
    }

    public void setCurrentPositionInInputFile(int positionInInputFile)
    {
        currentPosition.inInputFile = positionInInputFile;
    }

    public int getCurrentPositionInArray()
    {
        return currentPosition.inArray;
    }

    public void setCurrentPositionInArray(int currentPositionInArray)
    {
        currentPosition.inArray = currentPositionInArray;
    }

    public int getValueInArray(int currentPositionInArray)
    {
        return array[currentPositionInArray];
    }

    public void setValueInArray(int currentPositionInArray, int value)
    {
        array[currentPositionInArray] = value;
    }

    public int peekValueFromCallStack()
    {
        return callStack.peek();
    }

    public void pushValueInCallStack(int value)
    {
        callStack.push(value);
    }

    public int popValueFromCallStack()
    {
        return callStack.pop();
    }

    public boolean emptyCallStack()
    {
        return callStack.empty();
    }
}