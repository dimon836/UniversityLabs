package ArithmeticalOperations;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class Calculator {
    private final int id;
    private ArithmeticalOperations arithmeticalOperations;

    @Autowired
    public Calculator(ArithmeticalOperations arithmeticalOperations) {
        this.id = 1;
        this.arithmeticalOperations = arithmeticalOperations;
    }

    @Override
    public String toString() {
        return "Calculator " + id + " " + arithmeticalOperations.doOperation();
    }
}
