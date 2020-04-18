
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
// button id for creating a new product. 
var CreateProduct = document.getElementsById('btnCreateProduct');
CreateProduct.onclick = function()
{
    var prdID = document.getElementsById('txtProductID');
    var prdName = document.getElementsById('txtProductName');
    var prdPriceDollar= document.getElementsById('txtPriceDollar');
    var prdPriceCent = document.getElementsById('txtPriceCent');
    var prDescription = document.getElementsById('txtDescription');
    var prdURL = document.getElementsById('txtURL');
    var prdSKU = document.getElementsById('txtSKU');
    var prdModel = document.getElementsById('txtModel');
    var prdDueDate = document.getElementsById('txtDueDate');
    var prdLayout = document.getElementsById('txtLayoutName');
    var prdUpdate = document.getElementsById('txtUpdate');
    var prdBlink = document.getElementsById('txtBlink');

    if(prdID.value == ''|| prdName.value == ''|| prdPriceDollar.value == ''|| prdPriceCent.value == '' || prdDescription.value == ''||
     prdUpdate.value == '' || prdUpdate.value == '' || prdBlink)
     {

        
     } 
    
    
}


loadProductsTable();
