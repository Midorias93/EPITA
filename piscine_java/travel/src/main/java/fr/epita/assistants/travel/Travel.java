package fr.epita.assistants.travel;

import javax.swing.text.DateFormatter;
import java.text.DateFormat;
import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;

import static java.time.format.DateTimeFormatter.RFC_1123_DATE_TIME;

public class Travel {
    public static void travelTo(Country source, Country destination)
    {
        LocalDateTime instant = LocalDateTime.now();
        String dateSource= instant.atZone(source.countryZone).format(RFC_1123_DATE_TIME);

        String  dateDest = instant.plusHours(source.travelTimes.get(destination.countryName)).atZone(destination.countryZone).format(DateTimeFormatter.RFC_1123_DATE_TIME);

        System.out.println("Boarding in "+ source.countryName +  ", local date and time is: " + dateSource);
        System.out.println("Landing in " + destination.countryName + ", local date and time on arrival will be: " + dateDest);
    }
}