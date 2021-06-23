package ArithmeticalOperations;

import main.MathematicalDoingsOfPolynomials;
import org.springframework.stereotype.Component;

@Component
public class Multiplication implements Operation {
    private Multiplication() {}

    @Override
    public double doOperation() {
        controller.input();
        MathematicalDoingsOfPolynomials obj = new MathematicalDoingsOfPolynomials(
                controller.getNumeratorObj(),
                controller.getDenominatorObj());
        return obj.multiplication(1, 1);
    }
}
