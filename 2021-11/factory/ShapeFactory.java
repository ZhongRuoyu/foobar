import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

public class ShapeFactory {
    private static Path CONFIGURATION_PATH = Paths.get("configuration.txt");

    private static final Map<String, Class<?>> OPTION_TO_CLASS_MAP;

    static {
        OPTION_TO_CLASS_MAP = new HashMap<>();

        try (BufferedReader reader =
            Files.newBufferedReader(CONFIGURATION_PATH)) {
            String line = null;
            while ((line = reader.readLine()) != null) {
                if (line.isBlank()) {
                    continue;
                }
                String[] options = line.split("=");
                if (options.length != 2) {
                    throw new RuntimeException("Invalid configuration file");
                }
                String option = options[0];
                String className = options[1];
                Class<?> c;
                try {
                    c = Class.forName(className);
                } catch (ClassNotFoundException e) {
                    throw new RuntimeException(String.format(
                        "option %s corresponds to class %s, but the class is not found",
                        option, className));
                }
                if (!Shape.class.isAssignableFrom(c)) {
                    throw new RuntimeException(String
                        .format("%s is not a subclass of Shape", className));
                }
                OPTION_TO_CLASS_MAP.put(option, c);
            }
        } catch (IOException ioe) {
            throw new RuntimeException(
                String.format("%s: the configuration file cannot be read",
                    CONFIGURATION_PATH.toString()));
        }
    }

    static Shape getShape(String option) {
        Class<?> c = OPTION_TO_CLASS_MAP.get(option);
        if (c == null) {
            System.err.printf("%s: unknown option%n", option);
            return null;
        }
        try {
            Shape shape = (Shape) c.getDeclaredConstructor().newInstance();
            System.out.printf("Created shape %s%n", c.getName());
            return shape;
        } catch (Exception e) {
            System.err.printf("%s: shape %s cannot be created%n",
                e.getClass().getName(), c.getName());
            return null;
        }
    }
}
