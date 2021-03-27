import static org.junit.jupiter.api.Assertions.*;

class CounterTest {

    @org.junit.jupiter.api.Test
    void count() {
        Counter counter = new Counter();
        int actual = counter.count(5);
        int expected = 10;
        assertEquals(expected, actual);
    }
}