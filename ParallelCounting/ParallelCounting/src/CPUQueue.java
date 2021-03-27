import java.util.ArrayDeque;

public class CPUQueue {
    private ArrayDeque<CPUProcess> queue;

    CPUQueue(ArrayDeque<CPUProcess> queue) {
        this.queue = queue;
    }

    public ArrayDeque<CPUProcess> getQueue() {
        return queue;
    }

}
