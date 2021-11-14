import java.util.ArrayList;
import java.util.List;

public class SleepSort {
    private SleepSort() {}

    public static List<Integer> sort(List<Integer> orig) {
        List<Integer> result = new ArrayList<>();
        List<Thread> threads = new ArrayList<>();
        for (Integer i : orig) {
            threads.add(new Thread(() -> {
                try {
                    Thread.sleep(i * 100);
                    result.add(i);
                } catch (InterruptedException e) {}
            }));
        }
        for (Thread t : threads) {
            t.start();
        }
        for (Thread t : threads) {
            try {
                t.join();
            } catch (InterruptedException e) {}
        }
        return result;
    }

    public static void main(String[] args) {
        System.out.println(SleepSort.sort(List.of(1, 5, 2, 7, 3, 6, 4)));
    }
}
