document.getElementById('addButton').addEventListener('click', function() {
    var inputText = document.getElementById('textBox').value.trim();
    if (inputText !== '') {
        var li = document.createElement('li');
        li.className = 'todoItem';
        
        var span = document.createElement('span');
        span.className = 'todoText';
        span.textContent = inputText;
        
        var deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.onclick = function() {
            li.parentNode.removeChild(li);
        };
        
        li.appendChild(span);
        li.appendChild(deleteButton);
        document.getElementById('todoList').appendChild(li);
        
        document.getElementById('textBox').value = '';
    }
});