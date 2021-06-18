package Singleton;

public class Singleton {
    private static Singleton singleton;
    private static String allPolynomials = "All polynomials: \n";

    public static Singleton getSingleton() {
        if (singleton == null) {
            singleton = new Singleton();
        }
        return singleton;
    }

    private Singleton() {

    }

    public void addPolynomial(String polynomial) {
        allPolynomials += polynomial + "\n";
    }

    public void showAllPolynomials() {
        System.out.println(allPolynomials);
    }
}
