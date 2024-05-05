// FIXME: This is the entry point of the application, write your code here

import { calculateLayout } from "./utils";
import './debug';
import io from 'socket.io-client'

import { fetchRoomConfig } from "../rooms";
import { getCanvas } from "../rooms/canvas";
import { initCanvas, renderCanvasUpdate } from '../rooms/canvas/utils';

// Initialize the layout
calculateLayout();

//-------------------------------------Utils------------------------------------------------

export async function refreshtoken() {
    let refresh_token = window.localStorage.getItem("refresh_token");
    const formData = new FormData();
    formData.append('client_id', `${import.meta.env.VITE_CLIENT_ID}`);
    formData.append('redirect_uri', 'http://localhost:8080/complete/epita/');
    formData.append('grant_type', 'refresh_token');
    formData.append('refresh_token', refresh_token);

    const response = await fetch('/auth-api/token', {
        method: 'POST',
        body: formData,
    });


    if (response.status === 400){
        console.log("error bat refresh_token")
        localStorage.removeItem('token');
        localStorage.removeItem('refresh_token');
        redirectToLogin();
    }

    const data = await response.json();

    window.localStorage.setItem("token", data.id_token);
    window.localStorage.setItem("refresh_token", data.refresh_token);
}

function afficheInfo(data) {        
    document.getElementById("room-name").innerText = data.metadata.name;
    document.getElementById("room-description").innerHTML = data.metadata.description;
    document.getElementById("room-description").style.display = "block";
}

//-------------------------------------Redirection------------------------------------------

//window.LOGIN_URL = new URL('https://cri.epita.fr/authorize');
window.LOGIN_URL = new URL(import.meta.env.VITE_AUTH_URL + '/authorize');

window.LOGIN_URL.searchParams.append('client_id', import.meta.env.VITE_CLIENT_ID);
window.LOGIN_URL.searchParams.append('scope', 'epita profile picture');
window.LOGIN_URL.searchParams.append('redirect_uri', 'http://localhost:8080/complete/epita/');
window.LOGIN_URL.searchParams.append('response_type', 'code');


export function redirectToLogin() {
    window.localStorage.setItem("url", window.location.href);
    window.location.href = window.LOGIN_URL.href;
}

let token = window.localStorage.getItem("token");
if (!token) {
    let refresh_token = window.localStorage.getItem("refresh_token");
    if (refresh_token)
    {
        await refreshtoken();
    }
    else
    {
        redirectToLogin();
    }
}
else {

//-------------------------------------Client Socket------------------------------------------


let update = false;
let unUpdatePixels = [];


let ws = io(import.meta.env.VITE_URL, { extraHeaders: { Authorization: `Bearer ${window.localStorage.getItem('token')}`}});

ws.on('connect', () => {
    window.localStorage.setItem("slug", window.location.pathname.split('/')[1] === "" ? "epi-place" : window.location.pathname.split('/')[1]);
    let connect = {
        id: 2312324,
        method: 'subscription',
        params: {
        path: 'rooms.canvas.getStream',
            input: {
                json: {
                    roomSlug: window.localStorage.getItem('slug'),
                },
            },
        },
    }
    console.log("Client connect");
    ws.send(connect);
});

ws.on ('message', async() => {
    let response = await fetchRoomConfig();
    let data = await response.json();


    if (response.status !== 200){
        if (data.message.includes('Token expired')){
            await refreshtoken()
            response = await fetchRoomConfig();
            data = await response.json();
        }
        else {
            console.log('refresh wrong refresh token');
            localStorage.removeItem('token');
            localStorage.removeItem('refresh_token');
            redirectToLogin()
        }
    }

    afficheInfo(data);

    let canva = await getCanvas();
    initCanvas(data, canva);

    update = true;
    unUpdatePixels.forEach((value) => {
        renderCanvasUpdate(value.color, value.posX, value.posY) } );
});

ws.on ("pixel-update", (data) => {
    const value = data.result.data.json;
    if (!update)
    {
        unUpdatePixels.push(value);
    }
    else
    {
        renderCanvasUpdate(value.color, value.posX, value.posY)
    }
});
}


