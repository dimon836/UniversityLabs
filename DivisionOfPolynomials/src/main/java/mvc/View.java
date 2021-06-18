package mvc;

import main.Polynomial;

public class View extends Controller {

    public View() {
        super();
    }

    public View(Polynomial n, Polynomial d) {
        super(n, d);
    }

    public void view(String s) {
        System.out.println(" IN VIEW CLASS ");
        if(s.equals("numerator") || s.charAt(0) == 'n')
            System.out.println(numeratorObj.toString());
        else if(s.equals("denominator") || s.charAt(0) == 'd')
            System.out.println(denominatorObj.toString());
        else
            view();
        System.out.println(" VIEW CLASS ENDS ");
    }

    public void view() {
        System.out.println(" IN VIEW CLASS ");
        System.out.println(numeratorObj.toString());
        System.out.println(denominatorObj.toString());
        System.out.println(" VIEW CLASS ENDS ");
    }
}
