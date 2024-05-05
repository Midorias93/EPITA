// FIXME: This file should handle the auth redirection
// Get the code from the URL parameters and redirect to the relevant page

const urlParams = new URLSearchParams(window.location.search);
const code = urlParams.get('code');

const formData = new FormData();
formData.append('client_id', `${import.meta.env.VITE_CLIENT_ID}`);
formData.append('redirect_uri', 'http://localhost:8080/complete/epita/');
formData.append('grant_type', 'authorization_code');
formData.append('code', code);

const response = await fetch('/auth-api/token', {
    method: 'POST',
    body: formData,
});


if (code) {
  const data = await response.json();
  if (response.status !== 200) {
    localStorage.removeItem('token');
    localStorage.removeItem('refresh_token');
  } else {
    localStorage.setItem('token', data.id_token);
    localStorage.setItem('refresh_token', data.refresh_token);

  }
}


window.location.href = window.localStorage.getItem('url');