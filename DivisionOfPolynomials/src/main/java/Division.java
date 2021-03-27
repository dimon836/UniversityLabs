import java.util.stream.Collectors;

public class Division extends Polynomial implements DivisionInterface {
    private Polynomial numerator;
    private Polynomial denominator;

    Division (Polynomial a, Polynomial b) {
        super();
        numerator = a;
        denominator = b;
    }

    public float calculation(int x1, int x2) {
        if (denominator.calculation(x2) == 0) {
            throw new ArithmeticException("Divide by zero");
        }
        return numerator.calculation(x1) / denominator.calculation(x2);
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
