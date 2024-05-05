window.END_SESSION_URL = new URL('https://cri.epita.fr/end-session');

async function fetchUserInfo(code) {
    const formData = new FormData();
    formData.append('client_id', 'assistants-atelier-js');
    formData.append('redirect_uri', 'http://localhost:8080/complete/epita/');
    formData.append('grant_type', 'authorization_code');
    formData.append('code', code);

    const tokenResponse = await fetch('/auth-api', {
        method: 'POST',
        body: formData,
    });

    const tokenData = await tokenResponse.json();
    return tokenData;
}

async function displayUserInfo() {
    const urlParams = new URLSearchParams(window.location.search);
    const code = urlParams.get('code');
    if (code) {
        try {
            const userInfo = await fetchUserInfo(code);
            const idToken = userInfo.id_token;
            const userClaims = JSON.parse(atob(idToken.split('.')[1])); // Decode JWT payload

            document.getElementById('name').innerText = userClaims.name;
            document.getElementById('campus').innerText = userClaims.zoneinfo;
            document.getElementById('grad-year').innerText = userClaims.graduation_years.join(', ');
            if (userClaims.picture_square) {
                document.getElementById('image').src = `https://cri.epita.fr${userClaims.picture_square}`;
            }

            const grooups = document.getElementById('list');
            userClaims.groups.forEach(group => {
                let Items = document.createElement('li');
                Items.textContent = `${group.slug} ${group.name}`;
                grooups.appendChild(Items);
            });

        } catch (error) {
            console.error('Failed to fetch or display user info:', error);
        }
    }
}

document.getElementById('RequestBtn').addEventListener('click', displayUserInfo);
document.getElementById('EndBtn').addEventListener('click', () => window.location.href = window.END_SESSION_URL.href);