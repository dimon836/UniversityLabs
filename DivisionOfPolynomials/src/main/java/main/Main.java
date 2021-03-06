package main;

import java.util.ArrayList;

import ArithmeticalOperations.*;
import Command.InputCommand;
import Proxy.*;
import mvc.*;
import Singleton.Singleton;
import org.springframework.context.support.ClassPathXmlApplicationContext;

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

        // Lab3 starts

//        View view = new View(polynomialNumerator, polynomialDenominator);
//        view.view();
//        view.view("n"); // numerator
//
//        System.out.println("******************CONTROLLER INPUT CHECK******************");
//        Polynomial input_numerator = new Polynomial();
//        Polynomial input_denominator = new Polynomial();
//        Controller check_controller = new Controller(input_numerator, input_denominator);
//        check_controller.input();
//        view = check_controller.controller_view();
//        view.view();
//
//        Polynomial new_pol;
//        new_pol = check_controller.input(15);
//        System.out.println(new_pol);

        // Lab3 Ends
        // Lab4 Starts
        // Command pattern +
        // Singleton pattern +
        // Proxy pattern +

//        Controller controller = new Controller();
//        User user = new User(new InputCommand(controller));
//        user.inputRecord();
//        View view = controller.controller_view();
//        view.view();
//        Singleton.getSingleton().showAllPolynomials();
//        Project project = new ProxyProject("https://github.com/dimon836/UniversityLabs/tree/main/DivisionOfPolynomials");
//        project.run();
//        /// Lab4 Ends
//
//
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext(
                "appConf.xml"
        );
        Calculator calculator = context.getBean("calculator", Calculator.class);
        System.out.println(calculator);


//        ArithmeticalOperations arithmeticalOperations =
//                context.getBean("arithmeticalOperations", ArithmeticalOperations.class);
//        System.out.println(arithmeticalOperations.doOperation());


//        Operation operation = context.getBean("add", Operation.class);
//        ArithmeticalOperations arithmeticalOperations = new ArithmeticalOperations(operation);
//        arithmeticalOperations.doOperation();
//
//        Operation operation2 = context.getBean("division", Operation.class);
//        ArithmeticalOperations arithmeticalOperations2 = new ArithmeticalOperations(operation2);
//        arithmeticalOperations2.doOperation();


//        Operation operation = context.getBean("divisionBean", Operation.class);
//        ArithmeticalOperations arithmeticalOperations = new ArithmeticalOperations(operation);
//        System.out.println(arithmeticalOperations.doOperation());

        context.close();
    }
}
