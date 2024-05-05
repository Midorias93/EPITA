package fr.epita.assistants.test2;

import fr.epita.assistants.server.MyServer;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

public class Test2Test {
    @Test
    void divisionParZero() {
        assertThrows(ArithmeticException.class, () -> Test2.division(1 ,0));
    }
    @Test
    void divisionDeZero() {
        assertEquals(0, Test2.division(0, 1));
    }
    @Test
    void divisionIntPositif() {
        assertEquals(2, Test2.division(4, 2));

    }
    @Test
    void divisionIntNegatif() {
        assertEquals(-2,Test2.division(-4, 2) );
    }

    @Test
    void divisionFloatPositif() {
       assertEquals(1, Test2.division(3,2));
    }
    @Test
    void divisionFloatNegatif() {
       assertEquals(-1, Test2.division(-3, 2));
    }
    @Test
    void tribonacciNegatif () {
        assertThrows(IllegalArgumentException.class, () -> Test2.tribonacci(-1));

    }
    @Test
    void tribonacciPetit() {
        assertEquals(504, Test2.tribonacci(12));
    }
    @Test
    void tribonacciTresGrand() {
        assertEquals(1,Test2.tribonacci(123));
    }
    @Test
    @Timeout(1)
    void tribonacciTimeOut() {
        assertEquals(1, Test2.tribonacci(Integer.MAX_VALUE));
    }
    @Test
    void tribonacciZero() {
        assertEquals(0, Test2.tribonacci(0));
    }
    @Test
    void tribonacciUn () {
        assertEquals(1, Test2.tribonacci(1));

    }
    @Test
    void tribonacciDeux () {
        assertEquals(1, Test2.tribonacci(2));
    }
    @Test
    void tribonacciDTrois () {
        assertEquals(2, Test2.tribonacci(3));
    }
    @Test
    void serverIOError() {
       assertThrows(IOException.class, () -> Test2.serverGetResponseCode());
    }

    @Test
    void sererRunnig() {
        try {
            MyServer.launchServer();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        long resCode;
        try {
            resCode = Test2.serverGetResponseCode();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assertEquals(200, resCode);
    }
    @Test
    void sererStopted() {
        try {
            MyServer.launchServer();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        long resCode;
        try {
            resCode = Test2.serverGetResponseCode();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        MyServer.stopServer();
        assertThrows(IOException.class, () -> Test2.serverGetResponseCode());
    }
    @Test
    @Timeout(1)
    void serverDelay() {
        try {
            MyServer.launchServer();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        long resCode;
        try {
            resCode = Test2.serverGetResponseCode();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        assertEquals(200, resCode);
    }
}