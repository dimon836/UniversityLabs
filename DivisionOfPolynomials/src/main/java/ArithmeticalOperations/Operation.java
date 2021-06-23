package ArithmeticalOperations;

import main.Polynomial;
import mvc.*;

public interface Operation {
    Polynomial numerator = new Polynomial();
    Polynomial denominator = new Polynomial();
    Controller controller = new Controller(numerator, denominator);
    Model model = new Model();

    double doOperation();
}
