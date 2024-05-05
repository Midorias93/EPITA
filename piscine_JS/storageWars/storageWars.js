
document.getElementById('addToken').addEventListener('click', addToken);

function parseJWT(token) {
    try {
        const base64Url = token.split('.')[1];
        const base64 = base64Url.replace(/-/g, '+').replace(/_/g, '/');
        const jsonPayload = decodeURIComponent(atob(base64).split('').map(function(c) {
            return '%' + ('00' + c.charCodeAt(0).toString(16)).slice(-2);
        }).join(''));
        return JSON.parse(jsonPayload);
    } catch (e) {
        return null;
    }
}

function updateUserInfo(userData) {
    const userInfoDiv = document.getElementById('userInfo');
    const errorDiv = document.getElementById('error');
    if (userData) {
        document.getElementById('name').textContent = userData.name || "No name";
        document.getElementById('email').textContent = userData.email || "No email";
        document.getElementById('age').textContent = userData.age || "No age";
        userInfoDiv.style.display = 'block';
        errorDiv.textContent = '';
    } else {
        userInfoDiv.style.display = 'none';
        errorDiv.textContent = 'Invalid token';
    }
}

function addToken() {
    const token = document.getElementById('inputJWT').value;
    const userData = parseJWT(token);


    if (userData) {
        localStorage.setItem('token', token);
        updateUserInfo(userData);
    } else {
        updateUserInfo(null);
    }
}

const storedToken = localStorage.getItem('token');
if (storedToken) {
    const userData = parseJWT(storedToken);
    updateUserInfo(userData);
} 
else {
    document.getElementById('userInfo').style.display = 'none';
}