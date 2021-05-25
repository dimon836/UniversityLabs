import annotations.SomeAnnotation;

import java.util.ArrayList;

public class Polynomial {
    private final ArrayList<Integer> coefficients;

    Polynomial (ArrayList<Integer> arr) {
        coefficients = arr;
    }

    public Polynomial() {
        coefficients = new ArrayList<>();
    }

    public float calculation (int x) {
        // TODO: 24.05.2021
        // in if() statement was isEmpty() check
        if(x == 0) {
            return 0F;
        }
        float sum = 0;
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

    static String power(Integer x) {
        String s = Integer.toString(x);
        StringBuilder retS = new StringBuilder();
        String unicodeCharactersOfPower = "\u2070" + "\u00B9" + "\u00B2" + "\u00B3" + "\u2074" + "\u2075" + "\u2076" +
                "\u2077" + "\u2078" + "\u2079";
        for (int i = 0; i < s.length(); i++) {
            retS.append(unicodeCharactersOfPower.charAt(Character.getNumericValue(s.charAt(i))));
        }
        return retS.toString();
    }

    @SomeAnnotation
    public boolean isEmpty(){
        return this.coefficients.size() == 0;
    }

    @Override
    public String toString() {
        StringBuilder retS = new StringBuilder("P(x) = " + coefficients.get(0) + "x" + power(coefficients.get(0)));
        for (int i = 1; i < coefficients.size(); i++) {
            retS.append(" + ").append(coefficients.get(i)).append("x").append(power(coefficients.get(i)));
        }
        return retS.toString();
    }
}
