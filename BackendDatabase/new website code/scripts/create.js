
//Object creation
//const app = document.getElementById('root');
const app = document.getElementById('content-wraper');

var btnCreate = document.createElement('button');
btnCreate.setAttribute('type','button');
btnCreate.setAttribute('class','btn btn-primary');
btnCreate.setAttribute('id','btnCreate');
btnCreate.textContent = 'Create';

const containder = document.createElement('div');
//containder.setAttribute('class','container');
containder.setAttribute('class','containe-fluid');
app.appendChild(btnCreate);
app.appendChild(containder);

var productForm = document.createElement('form');
productForm.setAttribute('class','mb3');
var fset = document.createElement('fieldset');

productForm.appendChild(fset);
app.appendChild(productForm);

//Main controls of the window1
var CreateModal = document.getElementById('createModal');
var buttonCreate = document.getElementById('btnCreate');
var EditModal = document.getElementById('editModal');
var alertSuccess = document.getElementById('Advertise');

///Modal windows getter
var btnCreatePRoduct = document.getElementById('btnCreateProduct');
var btnCancelProduct = document.getElementById('btnCancel');

var btnProdEdit = document.getElementById('btnEditProduct');
var bntPrdEditCancel = document.getElementById('btnEditCancel');

//Delete product variables
var deleteModal = document.getElementById('deleteWarningModal');
var SKUtoDelete;
var acceptDelete = document.getElementById('btnDeleteAccept');
var candelDelete =  document.getElementById('btnDeleteCancel');

var emptyCreateAlert = document.getElementById('createIncompleteAlert');
emptyCreateAlert.style.display = "none";
//accept the product deletion
acceptDelete.onclick = function()
{
    dltProductReq(SKUtoDelete);
}

candelDelete.onclick = function()
{
    deleteModal.style.display = "none";
}

//Show creation modal
buttonCreate.onclick = function()
{
    CreateModal.style.display = "block";
}

//Hide product creation window without any changes
btnCancelProduct.addEventListener('click',()=>{
    CreateModal.style.display = "none";
});

//Hide edition modal
bntPrdEditCancel.onclick = function(){
    EditModal.style.display = "none";
}

//Populates the page with products
//loadProductsCards();
loadProductsTable();

//Clcik events
btnProdEdit.onclick = function()
{    
    var edtDesc = document.getElementById('txtEditDesc');
    var edtSku = document.getElementById('txtEditSKU');
    var edtUPC = document.getElementById('txtEditUPC');
    var edtUrl = document.getElementById('txtEditURL');
    var edtModel = document.getElementById('txtEditModel');    
    var edtTecSpect = document.getElementById('txtEditTecSpect');
  
    var message = JSON.stringify({        
        Title: edtDesc.value,
        URL: edtUrl.value,
        SKU: edtSku.value,
        UPC: edtUPC.value,
        Model: edtModel.value,        
        TechSpect: edtTecSpect.value
        });
        console.log(message);
        edtProductReq(message);

        edtDesc = "";
        edtSku = "";
        edtUrl = "";
        edtModel = "";        
        edtTecSpect = "";       
}



btnCreatePRoduct.onclick = function(){
        var Title = document.getElementById('txtDesc');
        var SKU = document.getElementById('txtSKU');
        var URL = document.getElementById('txtURL');
        var UPC = document.getElementById('txtUPC');
        var Model = document.getElementById('txtModel');        
        var tecSpect = document.getElementById('txtTecSpect');
        
        
        if(  Title.value == '' ||   SKU.value == '' ||   URL.value == '' || 
        Model.value == '' || UPC.value == '' || tecSpect.value == '')
        {
            emptyCreateAlert.style.display = "block";
            setTimeout(()=>{
                emptyCreateAlert.style.display = "none";
            },3000)
        }
        else{
           
                var message = JSON.stringify({
                   
                    Title: Title.value,
                    URL: URL.value,
                    SKU:SKU.value,
                    UPC:UPC.value,
                    Model:Model.value,                    
                    TechSpect: tecSpect.value,
                    });     
            console.log(message);
            crtProductReq(message);
            Title.value = "";
            SKU.value = "";
            URL.value = "";
            UPC.value = "";
            Model.value = "";            
            tecSpect.value = "";            
        }           
}

function clearScreen()
{
    var element =  document.getElementById('root');
    console.log(element);
    element.parentNode.removeChild(element);
}

