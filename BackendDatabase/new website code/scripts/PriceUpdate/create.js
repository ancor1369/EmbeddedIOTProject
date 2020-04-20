const app = document.getElementById('content-wraper');


var searchForm = document.createElement('form');
searchForm.setAttribute('class','d-none d-md-inline-block form-inline ml-auto mr-0 mr-md-3 my-2 my-md-0');
var skuSearchBox = document.createElement('input');
skuSearchBox.setAttribute('type','input');
skuSearchBox.setAttribute('class','form-control');
skuSearchBox.setAttribute('placeholder','Search SKU');
skuSearchBox.setAttribute('id','skuSearchBox');
var searchButton = document.createElement('button');
searchButton.setAttribute('class','btn btn-primary');
searchButton.setAttribute('id','searchButton');
searchButton.setAttribute('type','button');
var icon = document.createElement('i');
icon.setAttribute('class','fa fa-search');
searchButton.appendChild(icon);

searchForm.appendChild(skuSearchBox);
searchForm.appendChild(searchButton);
//app.appendChild(searchForm);

const containder = document.createElement('div');
containder.setAttribute('class','containe-fluid');
containder.appendChild(searchForm);
app.appendChild(containder);

var modalUpdate = document.getElementById('createPrice');
var updatePrice = document.getElementById('btnUpdatePrice');
var cancelUpdate = document.getElementById('btnCancelUpdate');

var udtPrice = document.getElementById('txtPrice');
var udtType = document.getElementById('ddlPriceType');
var udtStartDate = document.getElementById('datePiStartDate');
var udtDueDate = document.getElementById('dateDueDate');

//Prevents the warning window to appear
var emptyCreateAlert = document.getElementById('createIncompleteAlert');
emptyCreateAlert.style.display = "none";

var ProductSKU;

searchButton.onclick = function()
{
    ProductSKU = skuSearchBox.value;
    searchOnePrice(ProductSKU);    
}


updatePrice.onclick = function()
{
    console.log('update the price');
    modalUpdate.style.display = 'block';
    if(udtPrice.value == ''|| udtType.value  == '' || udtStartDate.value == ''|| udtDueDate.value == '')
    {
        emptyCreateAlert.style.display = 'block';
        
        setTimeout(()=>{
            emptyCreateAlert.style.display = 'none';
        },3000);
    }
    else{
        
        var priceToUse = parseFloat(udtPrice.value);        
        if(isNaN(priceToUse))
        {
            alert('Please, use a number for the price');
            return;
        }
        saveNewPrice();
        searchOnePrice(ProductSKU);
        modalUpdate.style.display = 'none';
    }

}

cancelUpdate.onclick = function()
{
    modalUpdate.style.display = 'none';
}