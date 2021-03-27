import java.util.ArrayList;
import java.util.List;

import static java.lang.Math.abs;
import static java.lang.Thread.sleep;

public class Main {

    //answers list
    static ArrayList<Double> x = new ArrayList<>();

    static void gauss(List<ArrayList<Double>> a, ArrayList<Double> b, int n) throws InterruptedException {
        // indexes deleting element and value of this element
        int del_i = 0;
        int del_j = 0;
        double delElem = a.get(0).get(0);

        // searching max element in array A
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (abs(a.get(i).get(j)) > abs(delElem)) {
                    delElem = abs(a.get(i).get(j));
                    del_i = i;
                    del_j = j;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (i != del_i) {
                b.set(i, b.get(i) + (-a.get(i).get(del_j) / a.get(del_i).get(del_j)) * b.get(del_i));
                for (int j = 0; j < n; j++) {
                    a.get(i).set(j, a.get(i).get(j) + (-a.get(i).get(del_j) /
                            a.get(del_i).get(del_j)) * a.get(del_i).get(j));
                }
            }
        }
        List<ArrayList<Double>> copyA = a;
        Thread thread = new ThreadClass(copyA, del_i, del_j, delElem);
        thread.start();
        sleep(500);

        ArrayList<Double> aErased = a.get(del_i);
        a.remove(del_i);
        Double bErased = b.get(del_i);
        b.remove(del_i);

        for (ArrayList<Double> o : a) {
            o.remove(del_j);
        }

        if(a.size() == 1) {
            x.add(b.get(0) / a.get(0).get(0));
            x.add(bErased / aErased.get(1) - x.get(x.size() - 1) * aErased.get(0) / aErased.get(1));
            return;
        }
        gauss(a, b, a.size());
        if(aErased.size() == 3) {
            x.add((bErased - x.get(x.size() - 2) * aErased.get(0) -
                    x.get(x.size() - 1) * aErased.get(1)) / aErased.get(2));
        }
        if(aErased.size() == 4) {
            x.add((bErased - x.get(x.size() - 3) * aErased.get(0) - x.get(x.size() - 2) * aErased.get(1)
                    - x.get(x.size() - 1) * aErased.get(2)) / aErased.get(3));
        }
    }

    public static void main(String[] args) throws InterruptedException {
        int n = 4;
        List<ArrayList<Double>> a = new ArrayList<>();
        ArrayList<Double> b = new ArrayList<>();
        double [][] arr = {{1, 5, 3, -4},
                {3, 1, -2, 0},
                {5, -7, 0, 10},
                {0, 3, -5, 0}};
        for (int i = 0; i < n; i++) {
            ArrayList<Double> arr1 = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                arr1.add(arr[i][j]);
            }
            a.add(arr1);
        }

        b.add(0, 20.0);
        b.add(1, 9.0);
        b.add(2, -9.0);
        b.add(3, 1.0);

    /*cout <<"\n input matrix a \n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    cout <<"\n input vector b\n";
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }*/ //input vectors
    /*cout << "\n matrix a: ";
    for (i = 0; i < n; i++) {
        cout << "\n";
        for (j = 0; j < n; j++) {
            cout <<" "<< a[i][j];
        }
    }

    cout << "\n vector b: ";
    for (i=0; i<n; i++) {
        cout << "\n " << b[i];
    }*/ // show vectors

        ///Call gauss
        gauss(a, b, n);

        System.out.println("vector x: ");
        int i = 0;
        System.out.print('[');
        while(i < n) {
            System.out.printf("%.2f", x.get(i));
            System.out.print(", ");
            i++;
        }
        System.out.println(']');
    }
}
