package main;

import interfaces.DivisionInterface;

import java.util.stream.Collectors;

public class MathematicalDoingsOfPolynomials extends Polynomial implements DivisionInterface {
    private Polynomial numerator;
    private Polynomial denominator;

    public MathematicalDoingsOfPolynomials(Polynomial a, Polynomial b) {
        super();
        numerator = a;
        denominator = b;
    }

    public float addition(int numeratorX1, int denominatorX2) {
        return numerator.calculation(numeratorX1) + denominator.calculation(denominatorX2);
    }

    public float subtraction(int numeratorX1, int denominatorX2) {
        return numerator.calculation(numeratorX1) - denominator.calculation(denominatorX2);
    }

    public float multiplication(int numeratorX1, int denominatorX2) {
        return numerator.calculation(numeratorX1) * denominator.calculation(denominatorX2);
    }

    public float division(int numeratorX1, int denominatorX2) {
        if (denominator.calculation(denominatorX2) == 0) {
            throw new ArithmeticException("Divide by zero");
        }
        return numerator.calculation(numeratorX1) / denominator.calculation(denominatorX2);
    }

    @Override
    public Polynomial getDenominator() {
        return denominator;
    }

    @Override
    public Polynomial getNumerator() {
        return numerator;
    }

    @Override
    public void setDenominator(Polynomial denominator) {
        this.denominator = denominator;
    }

    @Override
    public void setNumerator(Polynomial numerator) {
        this.numerator = numerator;
    }

    public String toString() {
        return "Division{" +
                "numerator=" + numerator.getCoefficients().stream().
                limit(numerator.getCoefficients().size()).collect(Collectors.toList()) +
                ", denominator=" + denominator.getCoefficients().stream().
                limit(denominator.getCoefficients().size()).collect(Collectors.toList()) +
                "}";
    }
}
