class Parent {
    void print() {
        System.out.println("Dynamic binding in class Parent");
    }
}

class Child extends Parent {
    void print() {
        System.out.println("Dynamic binding in class Child");
    }
}

class Binding {
    static void test(Parent obj) {
        System.out.println("Static binding for class T");
    }

    static void test(Child obj) {
        System.out.println("Static binding for class T1");
    }

    static void testParent(Object obj, String name) {
        System.out.printf("Is %s a Parent? " + (obj instanceof Parent) + "\n", name);
    }

    static void testChild(Object obj, String name) {
        System.out.printf("Is %s a Child? " + (obj instanceof Child) + "\n", name);
    }
}

class BindingTest {
    public static void main(String[] args) {
        Parent parent = new Parent();
        Child child = new Child();
        Parent casted = new Child();

        Binding.testParent(parent, "parent");
        Binding.testChild(parent, "parent");
        Binding.testParent(child, "child");
        Binding.testChild(child, "child");
        Binding.testParent(casted, "casted");
        Binding.testChild(casted, "casted");
        System.out.println();

        parent.print();
        child.print();
        casted.print();
        System.out.println();

        Binding.test(parent);
        Binding.test(child);
        Binding.test(casted);
        System.out.println();
    }
}
