package ArithmeticalOperations;

import main.MathematicalDoingsOfPolynomials;
import main.Polynomial;
import org.springframework.stereotype.Component;

@Component
public class Add implements Operation {

    private Add() {}

    public static Add getAdd() {
        return new Add();
    }

    public void init() {
        System.out.println("Class Add initialization");
    }

    public void destructor() {
        System.out.println("Class Add destruction");
    }

    @Override
    public double doOperation() {
        controller.input();
        MathematicalDoingsOfPolynomials obj = new MathematicalDoingsOfPolynomials(
                controller.getNumeratorObj(),
                controller.getDenominatorObj());
        return obj.addition(1, 1);
    }
}
