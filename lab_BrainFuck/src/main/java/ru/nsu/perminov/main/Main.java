package ru.nsu.perminov.main;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import ru.nsu.perminov.exception.FileFormatException;
import ru.nsu.perminov.exception.SyntaxException;
import ru.nsu.perminov.exception.UndefinedCommandException;

import java.io.*;
import java.util.Scanner;
public class Main
{
    private static final Logger LOG = LogManager.getLogger(Main.class);

    public static void main(String[] args)
    {
        LOG.info("*************************** The program started ***************************");
        String inputFileName = null;
        String configFileName = null;

        switch (args.length)
        {
            case 0 ->
            {
                LOG.warn("Too few arguments: enter the name of the executable and configuration file.");
                System.err.println("Too few arguments: enter the name of the executable and configuration file.");
                Scanner filesName = new Scanner(System.in);
                inputFileName = filesName.nextLine();
                configFileName = filesName.nextLine();
            }
            case 1 ->
            {
                LOG.warn("Too few arguments: enter the name of the configuration file.");
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

        LOG.info("Input files opened successfully: executable file - \"{}\"  configuration file - \"{}\"", inputFileName, configFileName);

        try (Reader input = new FileReader(inputFileName);
             Reader config = new FileReader(configFileName))
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
            LOG.info("The program ended successfully" );
        }
        catch (FileNotFoundException exception)
        {
            LOG.error("File opening error: {}", exception.getMessage(), exception);
            System.err.println("File opening error: " + exception.getMessage());
            System.out.println("Enter executable and config file");
        }
        catch (UndefinedCommandException exception)
        {
            LOG.error("Undefined interpreter command: \"{}\"", exception.getMessage(), exception);
            System.err.println("Undefined interpreter command: \"" + exception.getMessage() + "\"");
        }
        catch (ClassNotFoundException exception)
        {
            LOG.error("Failed to create class: \"{}\" does not exist", exception.getMessage(), exception);
            System.err.println("Failed to create class: \"" + exception.getMessage() + "\" does not exist");
        }
        catch (InstantiationException exception)
        {
            LOG.error("Failed to create class: it is not possible to apply the newInstance method to the class \"{}\"", exception.getMessage(), exception);
            System.err.println("Failed to create class: it is not possible to apply the newInstance method to the class \"" + exception.getMessage() + "\"");
        }
        catch (IllegalAccessException exception)
        {
            LOG.error("Failed to create class: {}", exception.getMessage(), exception);
            System.err.println("Failed to create class: " + exception.getMessage());
        }
        catch (FileFormatException exception)
        {
            LOG.error("Unable to run the program: {}", exception.getMessage(), exception);
            System.err.println("Unable to run the program: " + exception.getMessage());
        }
        catch (ArrayIndexOutOfBoundsException exception)
        {
            LOG.error("Index out of bounds: {}", exception.getMessage(), exception);
            System.err.println("Index out of bounds: " + exception.getMessage());
        }
        catch (SyntaxException exception)
        {
            LOG.error("Syntax error: {}", exception.getMessage(), exception);
            System.err.println("Syntax error: " + exception.getMessage());
        }
        catch (IOException exception)
        {
            LOG.error("Data entry error: {}", exception.getMessage(), exception);
            System.err.println("Data entry error: " + exception.getMessage());
        }
    }
}