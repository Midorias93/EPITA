package fr.epita.assistants;

import fr.epita.assistants.loggingbasics.*;
import org.slf4j.*;


public class Main {
    private final static Logger logger = LoggerFactory.getLogger(Main.class);

    public static void main(String[] args) {
        // FIXME: Add logging here
        logger.info("Entering application");

        Trombinoscope trombi = new Trombinoscope();

        trombi.putPerson("Bob", 1);
        trombi.putPerson("Bob", 2);
    }
}
