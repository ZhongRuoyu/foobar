import java.lang.reflect.Field;

class Reflection {
    public static void setPrivateFinal(Object object, Field field, Object value)
        throws Exception {
        boolean accessible = field.canAccess(object);
        field.setAccessible(true);
        field.set(object, value);
        field.setAccessible(accessible);
    }

    public static void main(String[] args) throws Exception {
        Test test = new Test();
        System.out.println(test);
        setPrivateFinal(test, test.getClass().getDeclaredField("i"), 2);
        System.out.println(test);
        test = new Test();
        System.out.println(test);
    }
}
