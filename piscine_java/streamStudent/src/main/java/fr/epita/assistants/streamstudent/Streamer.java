package fr.epita.assistants.streamstudent;

import java.util.Comparator;
import java.util.Optional;
import java.util.stream.Stream;

public class Streamer {
    public Stream<Pair<Integer, String>> validator(Stream<Pair<Integer, String>> stream) {
        return stream.filter(i -> (i.getKey().compareTo(0) >= 0 && i.getKey().compareTo(100) <= 0) && i.getValue().matches("^[^._]*(\\.|_)[^._]*$"));
    }
    public Stream<Pair<Integer, String>> orderGrade(Stream<Pair<Integer, String>> stream)
    {
        return stream.sorted((i ,j) -> i.getKey().equals(j.getKey()) ? i.getValue().compareTo(j.getValue()) : i.getKey().compareTo(j.getKey()));
    }
    public Stream<Pair<Integer, String>> lowercase(Stream<Pair<Integer, String>> stream)
    {
        return stream.map(i -> {if (i.getValue().matches("^.*[A-Z].*$")) {return new Pair(i.getKey() / 2, i.getValue());} else {return i;}}).map(i -> new Pair(i.getKey(), i.getValue().toString().toLowerCase()));
    }

    public Optional<Pair<Integer, String>> headOfTheClass(Stream<Pair<Integer, String>> stream)
    {
        return stream.max(Comparator.comparing(Pair::getKey));
    }

    public Stream<Pair<Integer, String>> quickFix(Stream<Pair<Integer, String>> stream)
    {
        return stream.map(i -> {if (i.getValue().matches("^(ma|MA|Ma|mA).*$") || i.getValue().matches("^(l|L).*(x|X)$")){return new Pair(i.getKey() * 2 > 100 ? 100 : i.getKey() * 2, i.getValue());}else {return i;}});
    }

    public Stream<Pair<Integer, String>> encryption(Stream<Pair<Integer, String>> stream)
    {
       return stream.map(i -> new Pair(i.getKey(), i.getValue().substring(i.getValue().length() / 2, i.getValue().length()) + i.getValue().substring(0, i.getValue().length() / 2)));
    }
}