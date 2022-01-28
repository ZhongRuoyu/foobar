import java.util.stream.IntStream;

public class Luhn {
    private Luhn() {}

    public static int getCheckDigit(String incompleteCardNumber) {
        int n = incompleteCardNumber.length() + 1;
        if (n < 12 || n > 19 || !incompleteCardNumber.chars()
            .allMatch(c -> Character.isDigit(c))) {
            throw new IllegalArgumentException("Illegal card number.");
        }
        return (10 - IntStream.range(0, n - 1)
            .map(i -> (n - i) % 2 == 0
                ? (incompleteCardNumber.charAt(i) - '0') * 2
                : (incompleteCardNumber.charAt(i) - '0'))
            .map(x -> x > 9 ? x / 10 + x % 10 : x).sum() % 10) % 10;
    }

    public static boolean isValid(String cardNumber) {
        int n = cardNumber.length();
        if (n < 12 || n > 19
            || !cardNumber.chars().allMatch(c -> Character.isDigit(c))) {
            throw new IllegalArgumentException("Illegal card number.");
        }
        return getCheckDigit(
            cardNumber.substring(0, n - 1)) == cardNumber.charAt(n - 1) - '0';
    }

    public static void main(String[] args) {
        System.out.println(isValid("4111111111111111"));
    }
}
