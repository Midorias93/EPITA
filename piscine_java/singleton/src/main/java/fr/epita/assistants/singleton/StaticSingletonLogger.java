package fr.epita.assistants.singleton;

import fr.epita.assistants.logger.Logger;

public class StaticSingletonLogger implements Logger {
    static int counter_info = 0;
    static int counter_war = 0;
    static int counter_err = 0;

    private StaticSingletonLogger() {
    }

    @Override
    public void log(Level level, String message) {
        if (level == level.ERROR)
            counter_err++;
        if (level == level.INFO)
            counter_info++;
        if (level == level.WARN)
            counter_war++;
            System.err.println("[" + level +"] "+ message);
    }

    @Override
    public int getInfoCounter() {
        return counter_info;
    }

    @Override
    public int getWarnCounter() {
        return counter_war;
    }

    @Override
    public int getErrorCounter() {
        return counter_err;
    }

    @Override
    public void reset() {
        counter_war = 0;
        counter_info = 0;
        counter_err = 0;

    }

    private static class InstanceHolder {
        private static final StaticSingletonLogger _INSTANCE = new StaticSingletonLogger();
    }

    public static StaticSingletonLogger getInstance() {
        return InstanceHolder._INSTANCE;
    }

}