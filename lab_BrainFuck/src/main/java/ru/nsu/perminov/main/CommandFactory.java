package ru.nsu.perminov.main;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jetbrains.annotations.NotNull;
import ru.nsu.perminov.exception.FileFormatException;
import ru.nsu.perminov.exception.UndefinedCommandException;

public class CommandFactory
{
    private static final Logger LOG = LogManager.getLogger(CommandFactory.class);
    private final HashMap<Character, String> existingCommands;

    CommandFactory(File configFile) throws FileNotFoundException, FileFormatException
    {
        LOG.debug("{} class constructor is running", LOG.getName());
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
        LOG.debug("{} class constructed successfully", LOG.getName());
    }

    @NotNull
    public ICommand create(Character commandName) throws ClassNotFoundException, InstantiationException, IllegalAccessException, UndefinedCommandException
    {
        LOG.trace("Creating an executable command: \"{}\"", commandName);
        String className;
        className = existingCommands.get(commandName);
        if (className == null)
        {
            throw new UndefinedCommandException(commandName.toString());
        }
        return (ICommand) Class.forName(className).getClassLoader().loadClass(className).newInstance();
    }
}

