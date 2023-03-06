package ru.nsu.perminov.main;


import ru.nsu.perminov.exception.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.Stack;

public class Compiler
{
    private final CommandFactory factory;
    private final File inputFile;
    private final int[] array;
    private final Position currentPosition;
    private final HashMap<Character, ICommand> availableCommands;
    private final Stack<Integer> callStack;
    public Compiler(File configFile, File inputFile) throws FileNotFoundException, FileFormatException
    {
        this.factory = new CommandFactory(configFile);
        this.inputFile = inputFile;
        this.array = new int[Constant.arraySize];
        this.currentPosition = new Position(0, 0);
        availableCommands = new HashMap<>();
        callStack = new Stack<>();
    }

    public void runProgram() throws FileNotFoundException, ClassNotFoundException, InstantiationException, IllegalAccessException, UndefinedCommandException, SyntaxException, FileFormatException
    {
        Scanner inputFileScanner = new Scanner(this.inputFile);
        if (!inputFileScanner.hasNextLine())
        {
            throw new FileFormatException("Code is missing");
        }
        String inputCommands = inputFileScanner.nextLine();
        Character currentCommand;
        while (currentPosition.inInputFile != inputCommands.length())
        {
            currentCommand = inputCommands.charAt(currentPosition.inInputFile);
            if (!this.availableCommands.containsKey(currentCommand))
            {
                availableCommands.put(currentCommand, factory.create(currentCommand));
            }
            availableCommands.get(currentCommand).run(this.array, this.callStack, this.currentPosition);
            //System.out.println(this.currentPosition.inArray + " : array value is " + array[this.currentPosition.inArray] + "pos in file: " + currentPosition.inInputFile);
        }
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