import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import ru.nsu.perminov.exception.FileFormatException;
import ru.nsu.perminov.exception.SyntaxException;
import ru.nsu.perminov.exception.UndefinedCommandException;
import ru.nsu.perminov.main.Compiler;

import java.io.*;


public class mainTest {
    @Test
    void helloWorldTest () throws FileFormatException, IOException, SyntaxException, UndefinedCommandException, ClassNotFoundException, InstantiationException, IllegalAccessException {
        File input = new File("src/test/resources/helloWorld_test");
        File config = new File("src/test/resources/configDefault");
        Compiler exe = new Compiler(config, input);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        exe.runProgram();
        System.out.flush();

        Assertions.assertEquals("Hello World!", baos.toString());
    }

    @Test
    void factorialsTest () throws FileFormatException, IOException, SyntaxException, UndefinedCommandException, ClassNotFoundException, InstantiationException, IllegalAccessException {
        File input = new File("src/test/resources/factorials_test");
        File config = new File("src/test/resources/configDefault");
        Compiler exe = new Compiler(config, input);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        exe.runProgram();
        System.out.flush();

        Assertions.assertEquals("1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89", baos.toString());
    }

    @Test
    void inputTest () throws FileFormatException, IOException, SyntaxException, UndefinedCommandException, ClassNotFoundException, InstantiationException, IllegalAccessException {
        File input = new File("src/test/resources/input_test");
        File config = new File("src/test/resources/configDefault");
        Compiler exe = new Compiler(config, input);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        String inputChar = "1";
        InputStream in = new ByteArrayInputStream(inputChar.getBytes());
        PrintStream ps = new PrintStream(baos);

        System.setIn(in);
        System.setOut(ps);
        exe.runProgram();
        System.out.flush();

        Assertions.assertEquals("1", baos.toString());
    }

    @Test
    void outputTest () throws FileFormatException, IOException, SyntaxException, UndefinedCommandException, ClassNotFoundException, InstantiationException, IllegalAccessException {
        File input = new File("src/test/resources/output_test");
        File config = new File("src/test/resources/configDefault");
        Compiler exe = new Compiler(config, input);
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        exe.runProgram();
        System.out.flush();

        Assertions.assertEquals("0", baos.toString());
    }

    @Test
    void fileNotFoundExceptionTest1 ()
    {
        File input = new File("src/test/resources/nonexistent_file");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);
        System.setOut(ps);
        Assertions.assertThrows(FileNotFoundException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "FileNotFoundException was expected");
        System.out.flush();
    }

    @Test
    void fileNotFoundExceptionTest2 ()
    {
        File input = new File("src/test/resources/input_test");
        File config = new File("src/test/resources/nonexistent_file");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);
        System.setOut(ps);
        Assertions.assertThrows(FileNotFoundException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "FileNotFoundException was expected");
        System.out.flush();
    }

    @Test
    void undefinedCommandExceptionTest ()
    {
        File input = new File("src/test/resources/undefinedCommandException_test");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(UndefinedCommandException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "UndefinedCommandException was expected");
        System.out.flush();
    }

    @Test
    void classNotFoundExceptionTest ()
    {
        File input = new File("src/test/resources/helloWorld_test");
        File config = new File("src/test/resources/classNotFoundException_test");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(ClassNotFoundException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "ClassNotFoundException was expected");
        System.out.flush();
    }

    @Test
    void fileFormatExceptionTest1 ()
    {
        File input = new File("src/test/resources/helloWorld_test");
        File config = new File("src/test/resources/fileFormatException_test_1");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(FileFormatException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "FileFormatException was expected");
        System.out.flush();
    }

    @Test
    void fileFormatExceptionTest2 ()
    {
        File input = new File("src/test/resources/helloWorld_test");
        File config = new File("src/test/resources/fileFormatException_test_2");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(FileFormatException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "FileFormatException was expected");
        System.out.flush();
    }

    @Test
    void fileFormatExceptionTest3 ()
    {
        File input = new File("src/test/resources/fileFormatException_test_3");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(FileFormatException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "FileFormatException was expected");
        System.out.flush();
    }

    @Test
    void arrayIndexOutOfBoundsExceptionTest1 ()
    {
        File input = new File("src/test/resources/arrayIndexOutOfBoundsException_test_1");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(ArrayIndexOutOfBoundsException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "ArrayIndexOutOfBoundsException was expected");
        System.out.flush();
    }
    @Test
    void arrayIndexOutOfBoundsExceptionTest2 ()
    {
        File input = new File("src/test/resources/arrayIndexOutOfBoundsException_test_2");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(ArrayIndexOutOfBoundsException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "ArrayIndexOutOfBoundsException was expected");
        System.out.flush();
    }

    @Test
    void syntaxExceptionTest ()
    {
        File input = new File("src/test/resources/syntaxException_test");
        File config = new File("src/test/resources/configDefault");
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        PrintStream ps = new PrintStream(baos);

        System.setOut(ps);
        Assertions.assertThrows(SyntaxException.class, () ->
        {
            Compiler exe = new Compiler(config, input);
            exe.runProgram();
        }, "SyntaxException was expected");
        System.out.flush();
    }
}
