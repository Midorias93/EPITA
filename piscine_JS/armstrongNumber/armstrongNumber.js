module.exports = {
    armstrongNumber,
}

function armstrongNumber(number) {

    if (typeof number !== "number") {
        return false;
    }

        let sum = 0;
        let tmp = number;
        let len = number.toString().length;

        while (tmp > 0)
        {
            let n = tmp % 10;
            sum += Math.pow(n, len);
            tmp = Math.floor(tmp / 10);
        }

        return sum === number;
}