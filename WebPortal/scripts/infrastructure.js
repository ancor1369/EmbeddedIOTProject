
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

var emptyCreateAlert = document.getElementById('createIncompletealert');
emptyCreateAlert.style.display = "none";



buttonCreate.onclick = function()
{
    CreateModal.style.display = "block";
}
CancelModal.onclick = function()
{
    CreateModal.style.display = "none";
}
// button id for creating a new product. 
var CreateProduct = document.getElementById('btnCreateProduct');
CreateProduct.onclick = function()
{
    var prdID = document.getElementById('txtProductID');
    var prdName = document.getElementById('txtProductName');
    var prdPriceDollar= document.getElementById('txtPriceDollar');
    var prdPriceCent = document.getElementById('txtPriceCent');
    var prDescription = document.getElementById('txtDescription');
    var prdURL = document.getElementById('txtURL');
    var prdSKU = document.getElementById('txtSKU');
    var prdModel = document.getElementById('txtModel');
    var prdDueDate = document.getElementById('txtDueDate');
    var prdLayout = document.getElementById('txtLayoutName');
    var prdUpdate = document.getElementById('txtUpdate');
    var prdBlink = document.getElementById('txtBlink');

    if(prdID.value == ''|| prdName.value == ''|| prdPriceDollar.value == ''|| prdPriceCent.value == '' || prDescription.value == ''||
        prdURL.value == '' || prdSKU.value == '' ||prdModel.value == '' ||prdLayout.value == '' ||prdDueDate.value == '' ||
        prdUpdate.value == '' || prdUpdate.value == '' || prdBlink.value == '')
    {
        emptyCreateAlert.style.display ="block";
        setTimeout(()=>{
        emptyCreateAlert.style.display = "none";
        },3000);
        
     } 
    
    
}


loadProductsTable();
