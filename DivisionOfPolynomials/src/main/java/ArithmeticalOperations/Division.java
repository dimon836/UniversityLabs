package ArithmeticalOperations;

import main.MathematicalDoingsOfPolynomials;
import org.springframework.stereotype.Component;

@Component
public class Division implements Operation {

    private Division() {}

    public static Division getAdd() {
        return new Division();
    }

    @Override
    public double doOperation() {
        controller.input();
        MathematicalDoingsOfPolynomials obj = new MathematicalDoingsOfPolynomials(
                controller.getNumeratorObj(),
                controller.getDenominatorObj());
        return obj.division(1, 1);
    }
}
