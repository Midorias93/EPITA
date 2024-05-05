window.LOGIN_URL = new URL('https://cri.epita.fr/authorize');

window.LOGIN_URL.searchParams.append('client_id', 'assistants-atelier-js');
window.LOGIN_URL.searchParams.append('scope', 'openid profile email');
window.LOGIN_URL.searchParams.append('redirect_uri', 'http://localhost:8080/complete/epita/');
window.LOGIN_URL.searchParams.append('response_type', 'code');

function redirectToLogin() {
    window.location.href = window.LOGIN_URL.href;
}

document.getElementById('redirectBtn').addEventListener('click', redirectToLogin);
