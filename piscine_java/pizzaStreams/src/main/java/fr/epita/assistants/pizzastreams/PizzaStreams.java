package fr.epita.assistants.pizzastreams;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Stream;

import fr.epita.assistants.pizzastreams.Topping.*;

import static java.lang.Double.NaN;

public class PizzaStreams {
    /**
     * @return The sum of the prices of all the pizzas in the stream
     */
    public static Integer getTotalPrice(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return pizzaStream.map(i -> i.getPrice()).reduce(0, Integer::sum);
    }

    /**
     * @return The average price of the pizzas in the stream, or the
     * double NaN if the stream is empty
     */
    public static Double getAveragePrice(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return pizzaStream.map(i -> i.getPrice()).mapToDouble(i -> i).average().orElse(NaN);
    }

    /**
     * @return Names of the pizzas, sorted by price in ascending order
     */
    public static List<String> sortByPrice(Stream<Pizza> pizzaStream) {
        return (List<String>) pizzaStream.sorted((i, j) -> i.getPrice().equals(j.getPrice()) ? i.getName().compareTo(j.getName()) : i.getPrice().compareTo(j.getPrice())).map(i -> i.getName()).toList();
    }

    /**
     * @return The Pizza object that has the lowest price, or null by default
     */
    public static Pizza getCheapest(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return pizzaStream.min(Comparator.comparing(Pizza::getPrice)).orElse(null);
    }

    /**
     * @return Names of the pizzas with meat (Protein)
     */
    public static List<String> getCarnivorous(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return (List<String>) pizzaStream.filter(i -> i.getTopping().getProtein().isPresent()).map(i -> i.getName()).toList();
    }

    /**
     * @return Names of the pizzas with at least one Vegetable and no Proteins
     */
    public static List<String> getVeggies(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return (List<String>) pizzaStream.filter(i -> !i.getTopping().getProtein().isPresent() && i.getTopping().getVegetablesPrice() != 0).map(i -> i.getName()).toList();
    }

    /**
     * @return true if all the pizzas with a nature dough are based with tomato
     * and mozzarella (italian pizza criteria), false otherwise
     */
    public static boolean areAllNatureItalians(Stream<Pizza> pizzaStream) {
        /* FIXME */
        return pizzaStream.filter(i -> i.getDough() == Dough.NATURE).allMatch(i -> i.getTopping().getSauce() == Sauce.TOMATO && i.getTopping().getCheese() == Cheese.MOZZARELLA);
    }
}
