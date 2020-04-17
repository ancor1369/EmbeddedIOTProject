
// make a call to the backend database.
const app = document.getElementById('content-wraper');
const container = document.createElement('div');
var btnCreate = document.createElement('button');
btnCreate.setAttribute('type','button');
btnCreate.setAttribute('class','btn btn-primary');
btnCreate.setAttribute('id','btnCreate');
btnCreate.textContent = 'Create Product';

    app.append(btnCreate);
    app.append(container);
var buttonCreate = document.getElementById('btnCreate');
var CreateModal = document.getElementById('createModal');
var CancelModal = document.getElementById('btnCancel');

buttonCreate.onclick = function()
{
    CreateModal.style.display = "block";
}
CancelModal.onclick = function()
{
    CreateModal.style.display = "none";
}
loadProductsTable();
