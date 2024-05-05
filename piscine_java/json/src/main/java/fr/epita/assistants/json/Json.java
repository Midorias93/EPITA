package fr.epita.assistants.json;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.node.ObjectNode;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Json {


    public Json() {
    }

    public static void addToJson(String obj1, String obj2, String fileName) {
        File file = new File(Paths.get(fileName).toUri());
        if (!file.isFile()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        if (file.length() == 0) {
            try {
                Files.writeString(Paths.get(fileName), "{}");
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
        final ObjectMapper mapper = new ObjectMapper();
        ObjectNode node = null;
        try {
            node = mapper.readValue(file, ObjectNode.class);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        node.put(obj1, obj2);
        try {
            mapper.writer().writeValue(file, node);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}