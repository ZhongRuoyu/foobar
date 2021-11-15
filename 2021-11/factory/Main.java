public class Main {
    public static void getShapeAndPrint(String option) {
        Shape shape = ShapeFactory.getShape(option);
        if (shape != null) {
            System.out.println(shape);
            System.out.println(shape.getArea());
        }
        System.out.println();
    }

    public static void main(String[] args) {
        getShapeAndPrint("C");
        getShapeAndPrint("S");
        getShapeAndPrint("A");
    }    
}
