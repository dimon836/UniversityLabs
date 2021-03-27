import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class DivisionTest {

    ArrayList<Integer> numerator = new ArrayList<>();
    ArrayList<Integer> denominator = new ArrayList<>();

    @Test
    void calculationDivision_NumeratorDivideDenominator_EqualsNumbers() {
        numerator.add(1);
        numerator.add(2);
        numerator.add(3);
        denominator = numerator;
        denominator.add(4);
        Polynomial testNumerator = new Polynomial(numerator);
        Polynomial testDenominator = new Polynomial(denominator);
        Division testDivision = new Division(testNumerator, testDenominator);
        int x1 = 2;
        int x2 = 3;
        Assertions.assertEquals(testNumerator.calculation(x1) / testDenominator.calculation(x2),
                testDivision.calculation(x1, x2));
    }

    @Test
    void calculationDivision_DivideByZero_TrueOrFalse() {
        numerator.add(1);
        denominator.add(3);
        Division division = new Division(new Polynomial(numerator), new Polynomial(denominator));
        Exception exception = assertThrows(ArithmeticException.class, () -> division.calculation(1, 0));

        String expectedMessage = "Divide by zero";
        String actualMessage = exception.getMessage();

        Assertions.assertTrue(actualMessage.contains(expectedMessage));
    }
}