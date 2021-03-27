import java.util.ArrayDeque;

public class Main {
    private static final int NUMBER_OF_CPU = 1;
    private static final int NUMBER_OF_FLOWS = 1;
    public static final int NUMBER_OF_QUEUE = 2;
    public static final int NUMBER_OF_PROCESS = 15;



    public static void main(String[] args) {
        ArrayDeque<CPUProcess> queue1 = new ArrayDeque<>();
        ArrayDeque<CPUProcess> queue2 = new ArrayDeque<>();

        queue1.push(CPUProcess.generate_process());
        queue1.push(CPUProcess.generate_process());
        queue1.push(CPUProcess.generate_process());
        queue1.push(CPUProcess.generate_process());

        queue2.push(CPUProcess.generate_process());
        queue2.push(CPUProcess.generate_process());
        queue2.push(CPUProcess.generate_process());
        queue2.push(CPUProcess.generate_process());
        queue2.push(CPUProcess.generate_process());
        queue2.push(CPUProcess.generate_process());

        CPUQueue cpuQueue1 = new CPUQueue(queue1);
        CPUQueue cpuQueue2 = new CPUQueue(queue2);

        ThreadClass thread = new ThreadClass(NUMBER_OF_PROCESS, cpuQueue1, cpuQueue2);
        CPU cpu = new CPU(NUMBER_OF_PROCESS);

        thread.start();
        cpu.start();
    }
}
