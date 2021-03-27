public class ThreadClass extends Thread {

    private final int numOfProcess;
    static CPUQueue cpuQueue1;
    static CPUQueue cpuQueue2;

    public ThreadClass(int numOfProcess, CPUQueue cpuQueue1, CPUQueue cpuQueue2) {
        this.numOfProcess = numOfProcess;
        ThreadClass.cpuQueue1 = cpuQueue1;
        ThreadClass.cpuQueue2 = cpuQueue2;
    }

    public int getNumOfProcess() {
        return numOfProcess;
    }

    public static CPUQueue getCpuQueue1() {
        return cpuQueue1;
    }

    public static CPUQueue getCpuQueue2() {
        return cpuQueue2;
    }

    @Override
    public void run() {
        for (int i = 0; i < getNumOfProcess(); i++) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if (cpuQueue1.getQueue().size() <= cpuQueue2.getQueue().size()) {
                cpuQueue1.getQueue().push(CPUProcess.generate_process());
                System.out.println("Add process to queue1");
            } else {
                cpuQueue2.getQueue().push(CPUProcess.generate_process());
                System.out.println("Add process to queue2");
            }

        }
    }
}
