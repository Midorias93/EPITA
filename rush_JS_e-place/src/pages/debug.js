import $ from 'jquery';
import debugHtml from '../components/debug.html';

function refreshLocalStorage() {
  $('#token').text(localStorage.getItem('token')?? 'N/A');
  $('#refresh_token').text(localStorage.getItem('refresh_token') ?? 'N/A');
}

if (import.meta.env.MODE === 'debug') {
  $.get(debugHtml, function(response) {
    $('body').html(response);
    refreshLocalStorage();
  }).fail(function(xhr, status, error) {
    console.error('Error fetching debug HTML:', error);
  });


  $(document).on('click', '#errorBtn', function() {
    // Make a call to VITE_URL/tests/error using your own api call function
  });

  $(document).on('click', '#expiredTokenBtn', function() {
    // Make a call to VITE_URL/tests/expired using your own api call function
  });

  $(document).on('click', '#deleteTokenBtn', function() {
    localStorage.removeItem('token');
    refreshLocalStorage();
  });

  $(document).on('click', '#deleteRefreshTokenBtn', function() {
    localStorage.removeItem('refresh_token');
    refreshLocalStorage();
  });
}
