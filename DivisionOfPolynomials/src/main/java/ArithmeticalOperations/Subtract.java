package ArithmeticalOperations;

import main.MathematicalDoingsOfPolynomials;
import org.springframework.stereotype.Component;

@Component
public class Subtract implements Operation {
    private Subtract() {}

    @Override
    public double doOperation() {
        controller.input();
        MathematicalDoingsOfPolynomials obj = new MathematicalDoingsOfPolynomials(
                controller.getNumeratorObj(),
                controller.getDenominatorObj());
        return obj.subtraction(1, 1);
    }
}
