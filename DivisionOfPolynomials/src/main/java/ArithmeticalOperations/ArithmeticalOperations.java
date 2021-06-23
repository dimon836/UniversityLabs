package ArithmeticalOperations;

import main.Polynomial;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component
public class ArithmeticalOperations {
    private Operation operation;

    public ArithmeticalOperations(@Qualifier("add") Operation operation) {
        this.operation = operation;
    }

    public String doOperation() {
        return "Operation: " + operation.doOperation();
    }
}
