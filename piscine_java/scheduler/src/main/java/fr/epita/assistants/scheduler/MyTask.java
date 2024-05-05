package fr.epita.assistants.scheduler;

import java.util.concurrent.CompletableFuture;
import java.util.concurrent.TimeUnit;
import java.util.function.Function;
import java.util.function.Supplier;

public class MyTask<INPUT_TYPE, RETURN_TYPE> implements Task<RETURN_TYPE> {
    CompletableFuture<RETURN_TYPE> myFutur;

    public MyTask(CompletableFuture<RETURN_TYPE> futur) {
        this.myFutur = futur;
    }

    static <RETURN_TYPE> Task<RETURN_TYPE> of(Supplier<RETURN_TYPE> actionSupplier) {
        return new MyTask(CompletableFuture.supplyAsync(actionSupplier));
    }

    @Override
    public CompletableFuture<RETURN_TYPE> build() {
        return myFutur;
    }

    @Override
    public Task<RETURN_TYPE> onErrorRecoverWith(Function<Throwable, RETURN_TYPE> recoveryFunction) {
        return new MyTask(myFutur.handle((e ,x) -> recoveryFunction.apply(x)));

    }

    @Override
    public <NEW_RETURN_TYPE> Task<NEW_RETURN_TYPE> andThenDo(Function<RETURN_TYPE, NEW_RETURN_TYPE> action) {
       return new MyTask(myFutur.thenApplyAsync(action));
    }

    @Override
    public Task<RETURN_TYPE> andThenWait(long number, TimeUnit timeUnit) {
        return new MyTask(myFutur.thenApplyAsync(i -> i, CompletableFuture.delayedExecutor(number , timeUnit)));
    }
}
