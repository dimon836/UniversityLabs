import java.util.List;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadClass extends Thread {
    public List<ArrayList<Double>> arrayA = new ArrayList<>();
    private final int del_i;
    private final int del_j;
    private final double delElem;

    ThreadClass(List<ArrayList<Double>> a, int del_i, int del_j, double delElem) {
        for (int i = 0; i < a.size(); i++) {
            ArrayList<Double> arr1 = new ArrayList<>();
            for (int j = 0; j < a.size(); j++) {
                arr1.add(a.get(i).get(j));
            }
            arrayA.add(arr1);
        }
        this.del_i = del_i;
        this.del_j = del_j;
        this.delElem = delElem;
    }

    @Override
    public void run() {
        double maxCheck = arrayA.get(0).get(0);
        for (ArrayList<Double> o : arrayA) {
            for (double i : o) {
                if (i > maxCheck) {
                    maxCheck = i;
                }
            }
        }
        if (delElem == maxCheck) {
            System.out.println("\nIt's correct, you can continue...");
        }
    }
}
