package interfaces;

import main.Polynomial;

public interface DivisionInterface {
    Polynomial getDenominator();
    Polynomial getNumerator();

    void setDenominator(Polynomial denominator);
    void setNumerator(Polynomial numerator);
}
