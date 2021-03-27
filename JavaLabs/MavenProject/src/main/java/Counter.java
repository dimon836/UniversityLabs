public class Counter {
    static int count(int N) {
        int result = 0;
        for (int i = 0;i < N;i++) {
            result += i;
        }
        return result;
    }
}
