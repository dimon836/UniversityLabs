import annotations.SomeAnnotation;

import java.util.ArrayList;
import java.util.stream.Collectors;

public class Polynomial {
    private final ArrayList<Integer> coefficients;

    Polynomial (ArrayList<Integer> arr) {
        coefficients = arr;
    }

    public Polynomial() {
        coefficients = new ArrayList<>();
    }

    public float calculation (int x) {
        if(isEmpty() || x == 0) {
            return 0;
        }
        int sum = 0;
        int i = 1;
        for(int num: getCoefficients()) {
            sum += num * Math.pow(x, i);
            i++;
        }
        return sum;
    }

    public ArrayList<Integer> getCoefficients() {
        return coefficients;
    }

    @SomeAnnotation
    public boolean isEmpty(){
        return this.coefficients.size() == 0;
    }

    @Override
    public String toString() {
        return "Polynomial{" +
                "coefficients=" + coefficients.stream().limit(coefficients.size()).collect(Collectors.toList()) +
                "}";
    }
}