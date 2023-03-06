package ru.nsu.perminov.main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

import ru.nsu.perminov.exception.FileFormatException;
import ru.nsu.perminov.exception.UndefinedCommandException;

public class CommandFactory
{
    private final HashMap<Character, String> existingCommands;
    CommandFactory (File configFile) throws FileNotFoundException, FileFormatException
    {
        Scanner configFileScanner = new Scanner(configFile);
        if (!configFileScanner.hasNextLine())
        {
            throw new FileFormatException("Configuration data is missing");
        }
        this.existingCommands = new HashMap<>();
        while (configFileScanner.hasNextLine())
        {
            String configCommand = configFileScanner.nextLine();
            String[] configCommandSeparated = configCommand.split(":");
            if (configCommandSeparated.length != 2)
            {
                throw new FileFormatException("Incorrect format of configuration file");
            }
            existingCommands.put(configCommandSeparated[0].charAt(0), configCommandSeparated[1]);
        }
    }
    public ICommand create(Character commandName) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UndefinedCommandException
    {
        String className;
        className = existingCommands.get(commandName);
        if (className == null)
        {
            throw new UndefinedCommandException(commandName.toString());
        }
        return (ICommand) Class.forName(className).newInstance();
    }
}
/*
class A
{
    private int a;
    public A (int a)
    {
        this.a = a;
    }
}*/
