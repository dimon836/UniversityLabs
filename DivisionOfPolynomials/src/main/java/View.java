import java.util.ArrayList;
import java.util.Scanner;

public class View {

    private Polynomial numeratorObj;
    private Polynomial denominatorObj;

    View() {
        numeratorObj = new Polynomial();
        denominatorObj = new Polynomial();
    }

    View(Polynomial numerator, Polynomial denominator) {
        numeratorObj = numerator;
        denominatorObj = denominator;
    }

    @SuppressWarnings("DuplicatedCode")
    Polynomial input(Polynomial obj) {
        ArrayList<Integer> arrayList = new ArrayList<>();
        Scanner in = new Scanner(System.in);
        System.out.print("Input a size of array(numerator): ");
        for (int i = 0; i < in.nextInt(); i++) {
            arrayList.add(i+1);
        }
        obj = new Polynomial(arrayList);
        return obj;
    }

    @SuppressWarnings("DuplicatedCode")
    void input() {
        ArrayList<Integer> numerator = new ArrayList<>();
        ArrayList<Integer> denominator = new ArrayList<>();
        Scanner in = new Scanner(System.in);
        System.out.print("Input a size of array(numerator): ");
        for (int i = 0; i < in.nextInt(); i++) {
            numerator.add(i+1);
        }
        System.out.print("Input a size of array(denominator): ");
        for (int i = 0; i < in.nextInt(); i++) {
            denominator.add(i+1);
        }
        numeratorObj = new Polynomial(numerator);
        denominatorObj = new Polynomial(denominator);
    }

    void view(String s) {
        if(s.equals("numerator") || s.charAt(0) == 'n')
            System.out.println(numeratorObj.toString());
        else if(s.equals("denominator") || s.charAt(0) == 'd')
            System.out.println(denominatorObj.toString());
        else
            view();
    }

    void view() {
        System.out.println(numeratorObj.toString());
        System.out.println(denominatorObj.toString());
    }

    public Polynomial getNumeratorObj() {
        return numeratorObj;
    }

    public Polynomial getDenominatorObj() {
        return denominatorObj;
    }
}
