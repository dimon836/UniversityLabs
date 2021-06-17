package mvc;

import main.Polynomial;
import main.MathematicalDoingsOfPolynomials;

public class Model {
    protected Polynomial numeratorObj;
    protected Polynomial denominatorObj;
    protected MathematicalDoingsOfPolynomials model;
    public String model_name;

    public String getModelName() {
        return model_name;
    }

}
