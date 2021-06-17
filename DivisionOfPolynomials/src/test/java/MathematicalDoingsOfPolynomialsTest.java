import main.MathematicalDoingsOfPolynomials;
import main.Polynomial;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.powermock.core.classloader.annotations.PrepareForTest;
import org.powermock.modules.junit4.PowerMockRunner;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.Mockito.*;

@RunWith(PowerMockRunner.class)
@PrepareForTest(Polynomial.class)
class MathematicalDoingsOfPolynomialsTest {

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
        MathematicalDoingsOfPolynomials testMathematicalDoingsOfPolynomials =
                new MathematicalDoingsOfPolynomials(testNumerator, testDenominator);
        int x1 = 2;
        int x2 = 3;
        assertEquals(testNumerator.calculation(x1) / testDenominator.calculation(x2),
                testMathematicalDoingsOfPolynomials.division(x1, x2));
    }

    @Test
    void calculationDivision_DivideByZero_TrueOrFalse() {
        numerator.add(1);
        denominator.add(3);
        MathematicalDoingsOfPolynomials mathematicalDoingsOfPolynomials =
                new MathematicalDoingsOfPolynomials(new Polynomial(numerator), new Polynomial(denominator));
        Exception exception =
                assertThrows(ArithmeticException.class, () -> mathematicalDoingsOfPolynomials.division(1, 0));

        String expectedMessage = "Divide by zero";
        String actualMessage = exception.getMessage();

        Assertions.assertTrue(actualMessage.contains(expectedMessage));
    }

    @Test
    void calculationMultiplication_NumeratorMultiDenominator_EqualsNumbers() {
        numerator.add(1);
        numerator.add(2);
        numerator.add(3);
        denominator = numerator;
        denominator.add(4);
        Polynomial testNumerator = new Polynomial(numerator);
        Polynomial testDenominator = new Polynomial(denominator);
        MathematicalDoingsOfPolynomials testMathematicalDoingsOfPolynomials =
                new MathematicalDoingsOfPolynomials(testNumerator, testDenominator);
        int x1 = 2;
        int x2 = 3;
        Assertions.assertEquals(testNumerator.calculation(x1) * testNumerator.calculation(x2),
                testMathematicalDoingsOfPolynomials.multiplication(x1, x2));
    }

    @Test
    void calculationAddition_NumeratorAddDenominator_EqualsNumbers() {
        numerator.add(1);
        numerator.add(2);
        numerator.add(3);
        denominator = numerator;
        denominator.add(4);
        Polynomial testNumerator = new Polynomial(numerator);
        Polynomial testDenominator = new Polynomial(denominator);
        MathematicalDoingsOfPolynomials testMathematicalDoingsOfPolynomials =
                new MathematicalDoingsOfPolynomials(testNumerator, testDenominator);
        int x1 = 2;
        int x2 = 3;
        Assertions.assertEquals(testNumerator.calculation(x1) + testNumerator.calculation(x2),
                testMathematicalDoingsOfPolynomials.addition(x1, x2));
    }

    @Test
    void calculationSubtraction_NumeratorSubtractDenominator_EqualsNumbers() {
        numerator.add(1);
        numerator.add(2);
        numerator.add(3);
        denominator = numerator;
        denominator.add(4);
        Polynomial testNumerator = new Polynomial(numerator);
        Polynomial testDenominator = new Polynomial(denominator);
        MathematicalDoingsOfPolynomials testMathematicalDoingsOfPolynomials =
                new MathematicalDoingsOfPolynomials(testNumerator, testDenominator);
        int x1 = 2;
        int x2 = 3;
        Assertions.assertEquals(testNumerator.calculation(x1) - testNumerator.calculation(x2),
                testMathematicalDoingsOfPolynomials.subtraction(x1, x2));
    }

    @Test
    void calculationDivision_NumeratorDivideDenominator_EqualsNumbers_MockitoTest() {
        Polynomial numeratorMock = mock(Polynomial.class);
        Polynomial denominatorMock = mock(Polynomial.class);
        MathematicalDoingsOfPolynomials mathMock = mock(MathematicalDoingsOfPolynomials.class);
        float numeratorCalc = numeratorMock.calculation(3);
        float denominatorCalc = denominatorMock.calculation(4);
        when(mathMock.division(3, 4)).
                thenReturn(numeratorCalc / denominatorCalc);
        Throwable throwable = new ArithmeticException("Divide by zero");
        when(mathMock.division(3, 0)).
                thenThrow(throwable);
        when(mathMock.multiplication(3, 4)).
                thenReturn(numeratorCalc * denominatorCalc);
        when(mathMock.addition(3, 4)).
                thenReturn(numeratorCalc + denominatorCalc);
        when(mathMock.division(3, 4)).
                thenReturn(numeratorCalc - denominatorCalc);

        verify(mathMock);
    }
}