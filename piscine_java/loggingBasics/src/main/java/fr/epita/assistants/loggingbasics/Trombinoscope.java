package fr.epita.assistants.loggingbasics;

import ch.qos.logback.classic.Level;
import ch.qos.logback.classic.Logger;
import org.slf4j.LoggerFactory;

import java.util.*;

public class Trombinoscope {
    private final Logger LOGGER;
    private final HashMap<String, Long> map;

    public Trombinoscope() {
        // FIXME: Instantiate logger with level TRACE
        this.LOGGER = (Logger) LoggerFactory.getLogger(this.getClass());
        // FIXME: Add logging here
        LOGGER.setLevel(Level.TRACE);
        LOGGER.trace("Instantiating new Trombinoscope");

        map = new HashMap<>();
    }

    public Long putPerson(String name, long photoId) {
        // FIXME: Add logging here
        LOGGER.debug("Putting person (\"" + name + "\", " + photoId + ")");


        Long oldPhotoId = map.put(name,
                                  photoId);

        // FIXME: Add logging here
        if (oldPhotoId == null) {
            LOGGER.trace("Added entry for person \"" + name +"\"" );
        }
        else
        {
            LOGGER.trace("Updated entry for person \"" + name + "\"");
        }


        return oldPhotoId;
    }
}
