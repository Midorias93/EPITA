const { fibo } = require('./fibo');

describe ("fibo basic test", () => {


    test("fibo(0) should return 0", () => {
        expect(fibo(0)).toBe(0);
    });

    test("fibo(1) should return 1", () => {
        expect(fibo(1)).toBe(1);
    });

    test("fibo(2) should return 2", () => {
        expect(fibo(2)).toBe(1);
    });

    test("fibo(-12) should return -1", () => {
        expect(fibo(-12)).toBe(-1);
    });

    test("fibo(3) should return 3", () => {
        expect(fibo(3)).toBe(2);
    });

    test("fibo('number') should return -1", () => {
        expect(fibo('number')).toBe(-1);
    });

    test("fibo(12) should return 144", () => {
        expect(fibo(12)).toBe(144);
    });
});