import java.util.concurrent.locks.ReentrantLock;

public class ReadersWriters {

    static ReentrantLock readLock = new ReentrantLock();
    static ReentrantLock writeLock = new ReentrantLock();
    static int readCount = 0;

    static class Read implements Runnable {
        @Override
        public void run() {
            try {
                readLock.lock();
                readCount++;
                if (readCount == 1) {
                    writeLock.lock();
                }

                System.out.println("Thread " + Thread.currentThread().getName() + " is READING");
                Thread.sleep(1500);
                System.out.println("Thread " + Thread.currentThread().getName() + " has FINISHED READING");

                readCount--;
                if(readCount == 0) {
                    writeLock.unlock();
                }
                readLock.unlock();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    static class Write implements Runnable {
        @Override
        public void run() {
            try {
                writeLock.lock();
                System.out.println("Thread " + Thread.currentThread().getName() + " is WRITING");
                Thread.sleep(2500);
                System.out.println("Thread " + Thread.currentThread().getName() + " has finished WRITING");
                writeLock.unlock();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        Read read = new Read();
        Write write = new Write();
        Thread t1 = new Thread(read);
        t1.setName("thread1");
        Thread t2 = new Thread(read);
        t2.setName("thread2");
        Thread t3 = new Thread(write);
        t3.setName("thread3");
        Thread t4 = new Thread(read);
        t4.setName("thread4");
        t1.start();
        t2.start();
        t3.start();
        t4.start();
    }
}