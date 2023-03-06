package ru.nsu.perminov.main;

import java.util.Scanner;
import java.util.Stack;

public class InputCommand implements ICommand
{
    @Override
    public void run(int[] array, Stack<Integer> callStack, Position currentPosition)
    {
        currentPosition.inInputFile++;
        if(!callStack.empty() && callStack.peek() < 0)
        {
            return;
        }
        String inputString;
        Scanner scanner = new Scanner(System.in);
        inputString = scanner.nextLine();
        if (inputString.length() == 0)
        {
            array[currentPosition.inArray] = 0;
        }
        else
        {
            array[currentPosition.inArray] = inputString.charAt(0);
        }
    }
}
