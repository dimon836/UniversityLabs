import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.util.ArrayList;

import static org.mockito.Mockito.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest(Polynomial.class)
class PolynomialTest {

    private static final ArrayList<Integer> numerator = new ArrayList<>();

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

    @Test
    void isEmpty_CheckingEmptyOrNotPolynomialArray_TrueOrFalse_MockitoCorrectTest() {
        View view = mock(View.class);
        Polynomial polynomial = mock(Polynomial.class);
        numerator.add(1); numerator.add(2); numerator.add(3);
        Polynomial somePolynomial = new Polynomial(numerator);
        String s = somePolynomial.toString();
        // need input 3
        when(view.input(polynomial).toString()).thenReturn(s);
        verify(view);
    }

    @Test
    void isEmpty_CheckingEmptyOrNotPolynomialArray_TrueOrFalse_MockitoIncorrectTest() {
        View view = mock(View.class);
        Polynomial polynomial = mock(Polynomial.class);
        when(view.input(polynomial).toString()).thenReturn("1");

        verify(view);
    }
}