package mvc;

import java.util.ArrayList;
import java.util.Scanner;

import Singleton.Singleton;
import main.MathematicalDoingsOfPolynomials;
import main.Polynomial;

public class Controller extends Model {

    public Controller() {
        numeratorObj = new Polynomial();
        denominatorObj = new Polynomial();
    }

    public Controller (Polynomial n, Polynomial d) {
        numeratorObj = n;
        denominatorObj = d;
    }

    public View controller_view() {
        return new View(numeratorObj, denominatorObj);
    }

    public void createModel () {
        System.out.print("Enter model name: ");
        Scanner in = new Scanner(System.in);
        model_name = in.nextLine();
        model = new MathematicalDoingsOfPolynomials(numeratorObj, denominatorObj);
    }

    public Polynomial input(int a) {
        ArrayList<Integer> arrayList = new ArrayList<>();
        String s;
        Scanner in = new Scanner(System.in);
        System.out.print("input or use const? ");
        s = in.nextLine();
        if (s.equals("input")) {
            System.out.print("Enter size of array: ");
            int n = in.nextInt();
            for (int i = 0; i < n; i++) {
                arrayList.add(i+1);
            }
        } else {
            for (int i = 0; i < a; i++) {
                arrayList.add(i+1);
            }
        }
        return new Polynomial(arrayList);
    }

    public void input() {
        ArrayList<Integer> numerator = new ArrayList<>();
        ArrayList<Integer> denominator = new ArrayList<>();
        Scanner in = new Scanner(System.in);
        System.out.print("Input a size of array(numerator): ");
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            numerator.add(i+1);
        }
        System.out.print("Input a size of array(denominator): ");
        n = in.nextInt();
        for (int i = 0; i < n; i++) {
            denominator.add(i+1);
        }
        numeratorObj = new Polynomial(numerator);
        denominatorObj = new Polynomial(denominator);
        Singleton.getSingleton().addPolynomial(numeratorObj.toString());
        Singleton.getSingleton().addPolynomial(denominatorObj.toString());
//        createModel();
    }

    @Override
    public Polynomial getNumeratorObj() {
        return numeratorObj;
    }

    @Override
    public Polynomial getDenominatorObj() {
        return denominatorObj;
    }
    //TODO
    // create test for rewriting polynomial
    // if polynomial isn't empty, ask if you wanna rewrite it
    private boolean rewritePolynomialCheck() {
        return true;
    }

}