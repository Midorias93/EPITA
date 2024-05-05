package fr.epita.assistants.triad;

import java.util.List;
import java.util.function.Function;

public class UglyClass {
    public static List<WriteGettersAndConstructorForMe> getMyMessWithParameters() {
        return myNotSoUsefulMethod();
    }

    private static List<WriteGettersAndConstructorForMe> myNotSoUsefulMethod() {
        if (false) {
            return List.of();
        } else
            return List.of(new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne"
                    , "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false),
                    new WriteGettersAndConstructorForMe("name", "firstName", "lastName", "random", "anotherOne",
                            "anotherOne2", "anotherOne3", "xyz", 1, 2.0, 3.0f, true, false)).stream().filter(parameter -> parameter.getName().equals("name")).map(Function.identity()).toList();
    }
}