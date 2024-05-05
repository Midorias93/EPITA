function comparaison(a, b) {
    if (typeof a === 'number' && typeof b === 'number') {
        return a - b;
    }
    else if (typeof a === 'string' && typeof b === 'string') {
        return a.localeCompare(b);
    }
    else if (typeof a === 'string' && typeof b === 'number') {
        return 1;
    }
    else if (typeof a === 'number' && typeof b === 'string') {
        return -1;
    }
    else if (typeof a === 'object' && typeof b === 'object') {
        if (a.lentgh === 0) 
        {
            return -1;
        }
        else if (b.length === 0)
        {
            return 1;
        }
        else
        {
            return Math.min.apply(Math, a) - Math.min.apply(Math, b); 
        }
    }
    else if (typeof a === 'object' && typeof b === 'number') {
        return 1;
    }
    else if (typeof a === 'number' && typeof b === 'object') {
        return -1;
    }
    else if (typeof a === 'object' && typeof b === 'string') {
        return 1;
    }
    else if (typeof a === 'string' && typeof b === 'object') {
        return -1;
    }
    else {
        return 0;
    }
}


function sortArray(arr) {
    let i, key, j;  
    let n = arr.length;
    if (arr.length == 1)
    {
        if (typeof arr[0] == "object")
        {
            sortArray(arr[0]);
        }
    }
    for (i = 0; i < n; i++) 
    {  
        key = arr[i];  
        j = i - 1;
        if (i == 0) {
            if (typeof key === 'object') {
                sortArray(key);
            }
            continue;
        }

        if (typeof key === 'object') {
            sortArray(key);
        }
        
  
        while (j >= 0 && comparaison(arr[j], key) > 0) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}

function find_keyword(array) {
    for(let i = 0; i < array.length; i++) {
        if (array[i] === 'activate' || array[i] === 'disperse') {
            return i;
        }
    }
    return -1;
}


function changeArray(array) {
    let index = find_keyword(array);
    let disperse = false;
    let activate = true;
    while (index !== -1) {
        let keyword = array.splice(index, 1)[0];
            if (keyword === 'activate' && activate) {
                activate = false;
                for (let i = 0; i < array.length; i++) {
                    if (typeof array[i] === 'number') {
                        array[i] = array[i] ** 2;
                    }
                    if (typeof array[i] === 'string' && array[i] !== "activate" && array[i] !== "disperse") {
                        array[i] = "super " + array[i];
                    }
                    if (typeof array[i] === 'object') {
                        array[i] = changeArray(array[i]);
                    }
                }
            }
            else {
                disperse = true;
            }
            index = find_keyword(array);
    }
    if (disperse) {
                let arr_int = [];
                let arr_string = [];
                let arr_list = [];
                for(let i = 0; i < array.length ; i++) {
                    if (typeof array[i] === 'number') {
                        arr_int.push(array[i]);
                    }
                    else if (typeof array[i] === 'string' && array[i] !== "disperse") {
                        arr_string.push(array[i]);
                    }
                    else if (typeof array[i] === 'object') {
                        arr_list.push(array[i]);
                    }
                }
                array = [];
                if (arr_int.length !== 0) {
                    array.push(arr_int);
                }
                if (arr_string.length !== 0) {
                    array.push(arr_string);
                }
                if (arr_list.length !== 0) {
                    array.push(arr_list);
                }
            }
    return array;

}



module.exports = { 
    sortArray,
    changeArray
};