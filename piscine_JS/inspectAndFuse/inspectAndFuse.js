function getNumberFields(inputObject) {
    if (!inputObject || typeof inputObject !== 'object') {
        return [];
    }
    return Object.keys(inputObject).filter(key => typeof inputObject[key] === 'number' );
}

function incrementCounters(inputObject) {
    if (!inputObject || typeof inputObject !== 'object') {
        return;
    }

    Object.keys(inputObject).forEach(key => {
        if (key.toLowerCase().includes('counter') && typeof inputObject[key] === 'number') {
            inputObject[key]++;
        }
    });
}

function deleteUppercaseProperties(inputObject) {
    if (!inputObject || typeof inputObject !== 'object') {
        return;
    }

    for (let key in inputObject) {
        if (key === key.toUpperCase()) {
            delete inputObject[key];
        } else if (typeof inputObject[key] === 'object') {
            deleteUppercaseProperties(inputObject[key]);
        }
    }
}

function fusion(...objects) {
    if (objects.length === 0) return {};

    const merged = {};

    for (const obj of objects) {
        if (typeof obj !== 'object') continue;

        for (const key in obj) {
            if (obj.hasOwnProperty(key)) {
                if (merged.hasOwnProperty(key)) {
                    const mergedVal = merged[key];
                    const objVal = obj[key];

                    if (Array.isArray(mergedVal) && Array.isArray(objVal)) {
                        merged[key] = mergedVal.concat(objVal);
                    } else if (typeof mergedVal === 'object' && typeof objVal === 'object') {
                        merged[key] = fusion(mergedVal, objVal);
                    } else if (typeof mergedVal === 'boolean' || typeof objVal === 'boolean' || typeof mergedVal !== typeof objVal) {
                        merged[key] = objVal;
                    } else {
                        merged[key] = mergedVal + objVal;
                    }
                } else {
                    merged[key] = obj[key];
                }
            }
        }
    }

    return merged;
}

module.exports = {
    getNumberFields,
    incrementCounters,
    deleteUppercaseProperties,
    fusion
};