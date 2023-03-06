package ru.nsu.perminov.main;

import ru.nsu.perminov.exception.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main
{
    public static void main(String[] args)
    {
        String inputFileName = null;
        String configFileName = null;

        switch (args.length)
        {
            case 0 ->
            {
                System.err.println("Too few arguments: enter the name of the executable and configuration file.");
                Scanner filesName = new Scanner(System.in);
                inputFileName = filesName.nextLine();
                configFileName = filesName.nextLine();
            }
            case 1 ->
            {
                System.err.println("Too few arguments: enter the name of the configuration file.");
                Scanner filesName = new Scanner(System.in);
                inputFileName = args[0];
                configFileName = filesName.nextLine();
            }
            default ->
            {
                inputFileName = args[0];
                configFileName = args[1];
            }
        }

        File input = new File(inputFileName);
        File config = new File(configFileName);

        try
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }
        catch (FileNotFoundException exception)
        {
            System.err.println("File opening error: " + exception.getMessage());
        }
        catch (UndefinedCommandException exception)
        {
            System.err.println("Undefined interpreter command: \"" + exception.getMessage() + "\"");
        }
        catch (ClassNotFoundException exception)
        {
            System.err.println("Failed to create class: \"" + exception.getMessage() + "\"" + " does not exist");
        }
        catch (InstantiationException exception)
        {
            System.err.println("Failed to create class: it is not possible to apply the newInstance method to the class \"" + exception.getMessage() + "\"");
        }
        catch (IllegalAccessException exception)
        {
            System.err.println("Failed to create class: " + exception.getMessage());
        }
        catch (FileFormatException exception)
        {
            System.err.println("Unable to run the program: " + exception.getMessage());
        }
        catch (ArrayIndexOutOfBoundsException exception)
        {
            System.err.println("Index out of bounds: " + exception.getMessage());
        }
        catch (SyntaxException exception)
        {
            System.err.println("Syntax error: " + exception.getMessage());
        }
    }
}