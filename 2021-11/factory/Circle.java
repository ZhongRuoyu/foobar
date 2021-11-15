public class Circle extends Shape {
    private final double radius;

    Circle() {
        this.radius = 1.0;
    }

    @Override
    double getArea() {
        return Math.PI * radius * radius;
    }

    @Override
    public String toString() {
        return "Circle";
    }
}
