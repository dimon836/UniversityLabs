public class CPU extends Thread {
    private static final int MIN_DURATION = 100;
    private static final int MAX_DURATION = 500;
    private static int firstQueueProcess = 0;
    private int thatSize;

    CPU(int num) {
        thatSize = num;
    }

    @Override
    public void run() {
        thatSize += ThreadClass.getCpuQueue1().getQueue().size() + ThreadClass.getCpuQueue2().getQueue().size();
        int i = 1;
        while(ThreadClass.getCpuQueue1().getQueue().size() != 0 && ThreadClass.getCpuQueue2().getQueue().size() != 0)
        {
            try {
                Thread.sleep((long) (Math.random() * (MAX_DURATION - MIN_DURATION) + MIN_DURATION));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            if(ThreadClass.getCpuQueue1().getQueue().size() > ThreadClass.getCpuQueue2().getQueue().size()) {
                ThreadClass.getCpuQueue1().getQueue().pop();
                System.out.println("|Pop process from queue1");
                CPU.firstQueueProcess++;
            } else {
                ThreadClass.getCpuQueue2().getQueue().pop();
                System.out.println("|Pop process from queue2");
            }
            if(ThreadClass.getCpuQueue1().getQueue().size() == 0 || ThreadClass.getCpuQueue2().getQueue().size() == 0) {
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            i++;
            if (i == thatSize)
                break;
        }
        System.out.println("Answer about first queue: " + ((float)CPU.firstQueueProcess/(float)thatSize)*100 + '%');
    }
}
