// FIXME: This file should handle the room canvas API
// Link buttons to their respective functions
// Functions may include:
// - getCanvas (get the canvas of a room and deserialize it)
// - subscribeToRoom (subscribe to the stream of a room)
// - getPixelInfo (get the pixel info of a room)
// - placePixel (place a pixel in a room)

import { refreshtoken, redirectToLogin } from "../../pages";

async function fetchCanvas() {
    let token = window.localStorage.getItem('token');
    const slug = window.localStorage.getItem('slug');

    const headers = {Authorization : `Bearer ${token}`}
    let response = await fetch(`/api/rooms/${slug}/canvas`, {
        headers: headers
    });
    return response;
}

function stringToBinary(input) {
    if (input === '' || input === null || typeof input !== 'string'){
        return '';
    }
    return input.split('').map(function(char) {
        return char.charCodeAt(0).toString(2).padStart(8, '0');
    }).join('');
}

function decodeCanvas(encode) {
    let canvas = [];
    let encodeBinaireString = stringToBinary(encode);

    let encodeBinaire = [];
    for(let i = 0; i < encodeBinaireString.length; i += 5) {
        encodeBinaire.push(encodeBinaireString.substr(i, 5));
    }

    for (let i = 0; i < encodeBinaire.length; i++) {
        if (encodeBinaire[i].length === 5) {
        let color = parseInt(encodeBinaire[i], 2);
        canvas.push(color);
        }
    }

    return canvas
}

export async function getCanvas() {
    let response = await fetchCanvas();
    let data = await response.json();
    if (response.status !== 200){
        if (data.message.includes('Token expired')){
            await refreshtoken();
            response = await fetchCanvas();
            data = await response.json();
        }
        else {
            console.log('refresh wrong refresh token')
            localStorage.removeItem('token');
            localStorage.removeItem('refresh_token');
            redirectToLogin()
        }
    }
    return decodeCanvas(data.pixels);
}


