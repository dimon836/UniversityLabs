import static java.lang.Thread.sleep;

public class CPUProcess {
    private static final int MIN_TIME_TO_NEXT = 100;
    private static final int MAX_TIME_TO_NEXT = 500;

    public static CPUProcess generate_process() {
        int timeToNext = (int) (Math.random() * (MAX_TIME_TO_NEXT - MIN_TIME_TO_NEXT) + MIN_TIME_TO_NEXT);
        try {
            sleep(timeToNext);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return new CPUProcess();
    }
}
