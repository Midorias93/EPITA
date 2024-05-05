package fr.epita.assistants.seq;

import java.util.*;
import java.util.function.*;
import java.util.stream.*;

public interface Seq<T> extends ExtendedStream<T> {
    Stream<T> getStream();

    static Seq of(Stream stream) {
        return () -> stream;
    }
    static Seq of(List stream) {
        return () -> stream.stream();
    }
    static <I> Seq of(I... stream) {
        return () -> List.of(stream).stream();
    }

    @Override
    default <KEY_TYPE> Map<KEY_TYPE, T> toMap(final Function<T, KEY_TYPE> keyMapper) {
        Map<KEY_TYPE, T> map = new HashMap<>();
        this.forEach(i -> map.put(keyMapper.apply(i), i));
        return map;
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE, MAP_TYPE extends Map<KEY_TYPE, VALUE_TYPE>> MAP_TYPE toMap(final MAP_TYPE map,
                                                                                              final Function<T,
                                                                                                      KEY_TYPE> keyMapper, final Function<T, VALUE_TYPE> valueMapper) {
        this.forEach(i -> map.put(keyMapper.apply(i), valueMapper.apply(i)));
        return map;
    }

    @Override
    default <KEY_TYPE, VALUE_TYPE> Map<KEY_TYPE, VALUE_TYPE> toMap(final Function<T, KEY_TYPE> keyMapper,
                                                                   final Function<T, VALUE_TYPE> valueMapper) {
        Map<KEY_TYPE, VALUE_TYPE> map = new HashMap<>();
        this.forEach(i -> map.put(keyMapper.apply(i), valueMapper.apply(i)));
        return map;
    }

    @Override
    default List<T> toList() {
        List<T> list = new ArrayList<>();
        this.forEach(i -> list.add(i));
        return list;
    }

    @Override
    default <LIST extends List<T>> LIST toList(final LIST list) {
        this.forEach(i -> list.add(i));
        return list;
    }

    @Override
    default Set<T> toSet() {
        Set<T> set = new HashSet<>();
        this.forEach(i -> set.add(i));
        return set;
    }

    @Override
    default <SET extends Set<T>> SET toSet(final SET set) {
        this.forEach(i -> set.add(i));
        return set;
    }

    @Override
    default <ASSOCIATED_TYPE> ExtendedStream<Pair<T, ASSOCIATED_TYPE>> associate(final Supplier<ASSOCIATED_TYPE> supplier) {
        List<Pair<T, ASSOCIATED_TYPE >> pairList = new ArrayList<>();
        this.forEach(i -> pairList.add(new Pair(i, supplier.get())));
        return Seq.of(pairList.stream());
    }

    @Override
    default <ASSOCIATED_TYPE> ExtendedStream<Pair<T, ASSOCIATED_TYPE>> associate(final Stream<ASSOCIATED_TYPE> supplier) {
        List<Pair<T, ASSOCIATED_TYPE >> pairList = new ArrayList<>();
        List<T> list1 = this.toList();
        List<ASSOCIATED_TYPE> list2 = supplier.toList();
        if (list1.size() < list2.size())
        {
            int i = 0;
            for(T element:list1)
            {
                pairList.add(new Pair(element, list2.get(i++)));
            }
        }
        else
        {
            int i = 0;
            for(ASSOCIATED_TYPE element:list2)
            {
                pairList.add(new Pair(list1.get(i++), element));
            }
        }
        return Seq.of(pairList.stream());
    }

    @Override
    default ExtendedStream<T> print() {
        Stream<T> caca = this;
        System.out.println(caca.toString());
        return Seq.of(caca);

    }

    @Override
    default ExtendedStream<T> plus(final Stream<T> stream) {
        return Seq.of(Stream.concat(this, stream));
    }

    @Override
    default String join(final String delimiter) {
        List<T> list = this.toList();
        String value  = list.get(0).toString() + delimiter;
        for (int i = 1; i < list.size() - 1; i++)
            value += list.get(i).toString() + delimiter;
        value += list.get(list.size() - 1);
        return value;
    }

    @Override
    default String join() {
        List<T> list = this.toList();
        String value  = list.get(0).toString();
        for (int i = 1; i < list.size() - 1; i++)
            value += list.get(i).toString();
        value += list.get(list.size() - 1);
        return value;
    }

    @Override
    default <KEY_TYPE> ExtendedStream<Pair<KEY_TYPE, ExtendedStream<T>>> partition(final Function<T, KEY_TYPE> pivot) {
        List<Pair<KEY_TYPE, ExtendedStream<T>>> list = new ArrayList<>();
        Map<KEY_TYPE, ExtendedStream<T>> map = new HashMap<>();

        this.forEach(i -> map.put(pivot.apply(i), map.get(pivot.apply(i)) != null ? map.get(pivot.apply(i)).plus(List.of(i).stream()) : Seq.of(List.of(i).stream())));


        map.forEach((i, j) -> list.add(new Pair(i, j)));
        return Seq.of(list.stream());
    }

    @Override
    default Stream<T> filter(Predicate<? super T> predicate) {
        return getStream().filter(predicate);
    }
    default <R> Stream<R> map(Function<? super T, ? extends R> mapper) {
        return getStream().map(mapper);
    }

    @Override
    default IntStream mapToInt(ToIntFunction mapper) {
        return getStream().mapToInt(mapper);
    }

    @Override
    default LongStream mapToLong(ToLongFunction mapper) {
        return getStream().mapToLong(mapper);
    }

    @Override
    default DoubleStream mapToDouble(ToDoubleFunction mapper) {
        return getStream().mapToDouble(mapper);
    }

    @Override
    default <R> Stream<R> flatMap(Function<? super T, ? extends Stream<? extends R>> mapper) {
        return getStream().flatMap(mapper);
    }

    @Override
    default IntStream flatMapToInt(Function<? super T, ? extends IntStream> mapper) {
        return getStream().flatMapToInt(mapper);
    }

    @Override
    default LongStream flatMapToLong(Function<? super T, ? extends LongStream> mapper) {
        return getStream().flatMapToLong(mapper);
    }

    @Override
    default DoubleStream flatMapToDouble(Function<? super T, ? extends DoubleStream> mapper) {
        return getStream().flatMapToDouble(mapper);
    }

    @Override
    default Stream<T> distinct() {
        return getStream().distinct();
    }

    @Override
    default Stream<T> sorted() {
        return getStream().sorted();
    }

    @Override
    default Stream<T> sorted(Comparator<? super T> comparator) {
        return getStream().sorted(comparator);
    }

    @Override
    default Stream<T> peek(Consumer<? super T> action) {
        return getStream().peek(action);
    }

    @Override
    default Stream<T> limit(long maxSize) {
        return getStream().limit(maxSize);
    }

    @Override
    default Stream<T> skip(long n) {
        return getStream().skip(n);
    }

    @Override
    default void forEach(Consumer<? super T> action) {
        getStream().forEach(action);

    }

    @Override
    default void forEachOrdered(Consumer<? super T> action) {
        getStream().forEachOrdered(action);

    }

    @Override
    default Object[] toArray() {
        return getStream().toArray();
    }

    @Override
    default <A> A[] toArray(IntFunction<A[]> generator) {
        return getStream().toArray(generator);
    }

    @Override
    default T reduce(T identity, BinaryOperator<T> accumulator) {
        return getStream().reduce(identity, accumulator);
    }

    @Override
    default Optional<T> reduce(BinaryOperator<T> accumulator) {
        return getStream().reduce(accumulator);
    }

    @Override
    default <U> U reduce(U identity, BiFunction<U, ? super T, U> accumulator, BinaryOperator<U> combiner) {
        return getStream().reduce(identity, accumulator, combiner);
    }

    @Override
    default <R> R collect(Supplier<R> supplier, BiConsumer<R, ? super T> accumulator, BiConsumer<R, R> combiner) {
        return getStream().collect(supplier, accumulator, combiner);
    }

    @Override
    default <R, A> R collect(Collector<? super T, A, R> collector) {
        return getStream().collect(collector);
    }

    @Override
    default Optional<T> min(Comparator<? super T> comparator) {
        return getStream().min(comparator);
    }

    @Override
    default Optional<T> max(Comparator<? super T> comparator) {
        return getStream().max(comparator);
    }

    @Override
    default long count() {
        return getStream().count();
    }

    @Override
    default boolean anyMatch(Predicate<? super T> predicate) {
        return getStream().anyMatch(predicate);
    }

    @Override
    default boolean allMatch(Predicate<? super T> predicate) {
        return getStream().allMatch(predicate);
    }

    @Override
    default boolean noneMatch(Predicate<? super T> predicate) {
        return getStream().noneMatch(predicate);
    }

    @Override
    default Optional<T> findFirst() {
        return getStream().findFirst();
    }

    @Override
    default Optional<T> findAny() {
        return getStream().findAny();
    }

    @Override
    default Iterator<T> iterator() {
        return getStream().iterator();
    }

    @Override
    default Spliterator<T> spliterator() {
        return getStream().spliterator();
    }

    @Override
    default boolean isParallel() {
        return getStream().isParallel();
    }

    @Override
    default Stream<T> sequential() {
        return getStream().sequential();
    }

    @Override
    default Stream<T> parallel() {
        return getStream().parallel();
    }

    @Override
    default Stream<T> unordered() {
        return getStream().unordered();
    }

    @Override
    default Stream<T> onClose(Runnable closeHandler) {
        return getStream().onClose(closeHandler);
    }

    @Override
    default void close() {
        getStream().close();

    }
}