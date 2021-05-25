import java.util.ArrayList;

/**
 * <p>
 * 1. Створити базовий і похідний класи згідно до варіанту індивідуального завдання.
 * Визначити конструктори, методи доступу, віртуальні методи (хоча б toString()).
 * Показати використання конструкторів похідного і базового класу. Можна визначити деякі константи або enum.
 * </p><p>
 * 2. Розробити анотацію, позначити, нею метод(и) в класі,За допомогою рефлексії обійти методи класу і
 * викликати відмічені анотацією методи за допомогою invoke().
 * </p><p>
 * 3. За допомогою рефлексії вивести ім'я класу.Також здійснити використання рефлексії відповідно
 * до варіанта індивідуального завдання з Таблиці 1.1.
 * </p><p>
 * 4. Зробити для класу проксі (для незмінності),
 * який пропускає звернення до getter-ів, там, де setter-и -
 * породжує виключну ситуацію (Exception).
 * </p>
 */

public class Main {

    public static void main(String[] args) {
        ArrayList<Integer> numerator = new ArrayList<>();
        numerator.add(2);
        numerator.add(2);   
        numerator.add(3);

        ArrayList<Integer> denominator = new ArrayList<>(numerator);
        denominator.remove(denominator.size() - 1);
        denominator.set(1, 3);
        denominator.add(4);

        Polynomial polynomialNumerator = new Polynomial(numerator);
        Polynomial polynomialDenominator = new Polynomial(denominator);
        MathematicalDoingsOfPolynomials mathematicalDoingsOfPolynomials =
                                        new MathematicalDoingsOfPolynomials(polynomialNumerator, polynomialDenominator);
//        System.out.println(polynomialDenominator);

        View view = new View(polynomialNumerator, polynomialDenominator);
        view.view();
        view.view("n"); // numerator

        /*
        System.out.println(mathematicalDoingsOfPolynomials.toString());
        System.out.println(polynomialDenominator.toString());

        System.out.println("------------Task 1.2----------------");
        System.out.println();

        Class<?> clazz = polynomialDenominator.getClass();
        for (Method method: clazz.getMethods()){
            if (method.isAnnotationPresent(SomeAnnotation.class)) {
                try {
                    System.out.println("SomeAnnotation (" + method.getName() + "): "
                            + method.invoke(polynomialDenominator));
                } catch (IllegalAccessException | InvocationTargetException e) {
                    e.printStackTrace();
                }
            }
        }

        System.out.println("------------Task 1.3----------------");
        System.out.println("Add task 4");

        // 4. Список полів з іменами, типами таи модифікаторами доступу.
        System.out.println(" Class name: " + clazz.getName());
        Field[] fid = clazz.getDeclaredFields();
        for (Field i : fid) {
            System.out.println(" " + i);
        }

        System.out.println("-------------------------------------");
        System.out.println("Add task 9");

        // 9. Список анотацій класу
        Method [] m = clazz.getMethods();
        for (Method i: m) {
            Annotation anno = i.getAnnotation(SomeAnnotation.class);
            if(anno != null) {
                System.out.println(" Method name: " + i.getName() + "\n Annotation: " + anno);
            }
        }

        System.out.println("------------Task 1.4----------------");
        System.out.println();

        DivisionInterface proxy = (DivisionInterface) SomeProxy.newProxyInstance(mathematicalDoingsOfPolynomials);
        Polynomial obj = proxy.getDenominator();
        System.out.println(obj.toString());
        try {
            proxy.setDenominator(polynomialNumerator);
        }
        catch (Exception e){
            e.printStackTrace();
        }
*/
    }
}
