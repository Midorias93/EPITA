function deepCopy(x) {
    if (x === null || typeof x !== 'object') {
        return x;
    }

    if (x instanceof Date) {
        return new Date(x.getTime());
    }

    if (Array.isArray(x)) {
        let copy = [];
        for (let item of x) {
            copy.push(deepCopy(item));
        }
        return copy;
    }

    if (x instanceof Object) {
        let copy = {};
        for (let key in x) {
            if (x.hasOwnProperty(key)) {
                copy[key] = deepCopy(x[key]);
            }
        }
        return copy;
    }

    throw new Error("Unable to copy x! Its type isn't supported.");
}

function deepEquality(a, b) {
    if (a === b) {
        return true;
    }

    if (typeof a != 'object' || typeof b != 'object' || a == null || b == null) {
        return false;
    }

    if (a.constructor !== b.constructor) {
        return false;
    }

    if (a instanceof Date && b instanceof Date) {
        return a.getTime() === b.getTime();
    }

    if (Array.isArray(a) && Array.isArray(b)) {
        if (a.length !== b.length) {
            return false;
        }
        for (let i = 0; i < a.length; i++) {
            if (!deepEquality(a[i], b[i])) {
                return false;
            }
        }
        return true;
    }

    let keysA = Object.keys(a);
    let keysB = Object.keys(b);
    if (keysA.length !== keysB.length) {
        return false;
    }

    for (let key of keysA) {
        if (!keysB.includes(key) || !deepEquality(a[key], b[key])) {
            return false;
        }
    }

    return true;
}

module.exports = { deepCopy, deepEquality };