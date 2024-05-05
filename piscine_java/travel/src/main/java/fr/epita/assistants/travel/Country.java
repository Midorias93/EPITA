package fr.epita.assistants.travel;
import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.time.ZoneId;
import java.util.*;

public class Country {
    String countryName;
    ZoneId countryZone;
    public Map<String, Integer> travelTimes;

    public Country(String countryName, String countryZone, String inputFieldPath) {
        this.countryName = countryName;
        this.countryZone = ZoneId.of(countryZone);
        this.travelTimes = initTravelTimes(inputFieldPath);
    }

    public Map initTravelTimes(String inputFieldPath) {

        List<List<String>> records = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(inputFieldPath))) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                records.add(Arrays.asList(values));
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        Map<String, Integer> travel = new HashMap<>();
            for (int i = 1; i < records.size(); i++) {
                if(records.get(i).get(0).compareTo(this.countryName) == 0) {
                    travel.put(records.get(i).get(1), Integer.valueOf(records.get(i).get(2)));
                }
                if (records.get(i).get(1).compareTo(this.countryName) == 0)
                    travel.put(records.get(i).get(0), Integer.valueOf(records.get(i).get(2)));
            }
    return travel;
    }
}