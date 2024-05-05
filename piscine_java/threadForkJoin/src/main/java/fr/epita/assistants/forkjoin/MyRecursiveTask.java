package fr.epita.assistants.forkjoin;

import java.util.concurrent.RecursiveTask;

public class MyRecursiveTask extends RecursiveTask<Double> {
    final private double[][] matrix;
    final  private  int xLower;
    final private int xUpper;
    final private int yLower;
    final private int yUpper;

    public MyRecursiveTask(double[][] matrix, int xLower, int xUpper, int yLower, int yUpper) {
        this.matrix = matrix;
        this.xLower = xLower;
        this.xUpper = xUpper;
        this.yLower = yLower;
        this.yUpper = yUpper;
    }

    @Override
    protected Double compute() {
        if(matrix == null || matrix.length == 0 || matrix[0].length == 0)
            return 0.0;

        if (xUpper - xLower <= 5 && yUpper - yLower <= 5) {
            return computeAverage();
        } else {
            int xMid = (xUpper + xLower) / 2;
            int yMid = (yUpper + yLower) / 2;

            MyRecursiveTask topLeft = new MyRecursiveTask(matrix, xLower, xMid, yLower, yMid);
            MyRecursiveTask topRight = new MyRecursiveTask(matrix, xMid, xUpper, yLower, yMid);
            MyRecursiveTask bottomLeft = new MyRecursiveTask(matrix, xLower, xMid, yMid, yUpper);
            MyRecursiveTask bottomRight = new MyRecursiveTask(matrix, xMid, xUpper, yMid, yUpper);

            topLeft.fork();
            topRight.fork();
            bottomLeft.fork();
            double bottomRightResult = bottomRight.compute();

            return (topLeft.join() + topRight.join() + bottomLeft.join() + bottomRightResult) / 4;
        }
    }
    private double computeAverage() {
        double sum = 0;
        for (int i = xLower; i < xUpper; i++) {
            for (int j = yLower; j < yUpper; j++) {
                sum += matrix[j][i];
            }
        }
        int totalElements = (xUpper - xLower) * (yUpper - yLower);
        return sum / totalElements;
}
}