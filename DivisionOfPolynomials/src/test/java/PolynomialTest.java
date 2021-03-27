import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;

class PolynomialTest {

    ArrayList<Integer> numerator = new ArrayList<>();

    @Test
    void calculationPolynomial_CalculationPolynomialWithX_EqualsNumbers() {
        numerator.add(1);
        numerator.add(2);
        numerator.add(3);
        Polynomial testObj = new Polynomial(numerator);
        int x = 3;
        Assertions.assertEquals(x + 2*x*x + 3*x*x*x, testObj.calculation(x));
    }

    @Test
    void isEmpty_CheckingEmptyOrNotPolynomialArray_TrueOrFalse() {
        numerator.add(1);
        Polynomial testObj = new Polynomial(numerator);
        Assertions.assertFalse(testObj.isEmpty());

        numerator.clear();
        testObj = new Polynomial(numerator);
        Assertions.assertTrue(testObj.isEmpty());
    }
}