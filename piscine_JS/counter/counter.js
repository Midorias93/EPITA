document.addEventListener('DOMContentLoaded', function() {
    const countElement = document.getElementById('count');
    const plusButton = document.getElementById('plus');
    const minusButton = document.getElementById('minus');

    plusButton.addEventListener('click', function() {
        let currentValue = parseInt(countElement.innerHTML);
        countElement.innerHTML = currentValue + 1;
    });

    minusButton.addEventListener('click', function() {
        let currentValue = parseInt(countElement.innerHTML);
        countElement.innerHTML = currentValue - 1;
    });
});
