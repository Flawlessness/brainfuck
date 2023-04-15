package ru.nsu.perminov.main;

public interface IContext
{
    int getCurrentPositionInInputFile();

    void setCurrentPositionInInputFile(int positionInInputFile);

    int getCurrentPositionInArray();

    void setCurrentPositionInArray(int currentPositionInArray);

    int getValueInArray(int currentPositionInArray);

    void setValueInArray(int currentPositionInArray, int value);

    int peekValueFromCallStack();

    void pushValueInCallStack(int value);

    int popValueFromCallStack();

    boolean emptyCallStack();
}
