import main.Polynomial;
import mvc.Controller;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.util.ArrayList;

import static org.mockito.Matchers.anyInt;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

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
//        mvc.View view = mock(mvc.View.class);
        Controller check_controller = new Controller();
//        check_controller.input();
//        view = check_controller.controller_view();
        numerator.add(1); numerator.add(2); numerator.add(3);
        Polynomial polynomial = new Polynomial(numerator);
        String s = polynomial.toString();
        Assertions.assertEquals(s, check_controller.input(3).toString());
//        when(check_controller.input(any()).toString()).thenReturn(s);
//        verify(check_controller);
    }

    @Test
    void isEmpty_CheckingEmptyOrNotPolynomialArray_TrueOrFalse_MockitoIncorrectTest() {
        Controller controller = new Controller();
        Polynomial polynomial = controller.input(4);
//        Assertions.assertNotEquals(polynomial.toString(), "tututu");
        when(controller.input(anyInt()).toString()).thenReturn("1");
        verify(controller);
    }
}