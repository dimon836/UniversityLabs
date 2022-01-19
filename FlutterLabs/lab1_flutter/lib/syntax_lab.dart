import 'dart:math';

abstract class Calculator<T extends num> {
  T _a;
  T _b;

  Calculator({required T a, required T b})
      : _a = a,
        _b = b;

  get sum => _a + _b;

  get subtraction => _a - _b;

  get multiply => _a * _b;

  get division => _b == 0 ? print('Cannot divide by zero') : _a / _b;

  get a => _a;

  get b => _b;

  double mySqrt(num x);

  set a(a) => _a = a;

  set b(b) => _b = b;

  @override
  String toString() {
    return 'Calculator numbers {a: $_a; b: $_b}\n';
  }
}

class CalculatorAddSqrt<T extends num> extends Calculator {
  CalculatorAddSqrt({required T a, required T b}) : super(a: a, b: b);

  @override
  double mySqrt(num x) {
    return sqrt(x);
  }

  @override
  String toString() {
    return 'CalculatorAddSqrt class have only one method: mySqrt(num x) {}.\n';
  }
}

int myFactorial(int x) {
  return x <= 1 ? 1 : x * myFactorial(x - 1);
}

class Person {
  String name;

  Person(this.name);

  void display() {
    print("Name: $name");
  }
}

mixin Worker {
  String company = "";

  void work() {
    print("Work in $company");
  }
}

class Employee extends Person with Worker {
  Employee(name, comp) : super(name) {
    company = comp;
  }
}

class Application {
  String name;
  static Application app = Application.fromName("");

  Application.fromName(this.name);

  factory Application(String name) {
    if (app.name == "") {
      app = Application.fromName(name);
      print("Application $name started");
    } else {
      print("In application ${app.name} was opened new window");
    }
    return app;
  }

  void about() {
    print("Application $name");
  }
}
