public class Square extends Circle {
    private final double side;

    Square() {
        this.side = 1.0;
    }

    @Override
    double getArea() {
        return side * side;
    }

    @Override
    public String toString() {
        return "Square";
    }
}
