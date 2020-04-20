var ProductSearchModal = document.getElementById('ProductSearchModal');
var NotFoundModal = document.getElementById('NotFoundModal');
var storeModal = document.getElementById("StoreSearchModal");
var btnAddProduct = document.getElementById('btnAddProduct');
var btnAddStore = document.getElementById('btnStoreAdd');
var btnCancelProduct = document.getElementById('btnCancelProduct');
var listStores = [];
var listProducts = [];

//Initial and static data infrastructure is created here    
var storeContent =  document.getElementById('storeContent');

var strForm = document.createElement('div');
strForm.setAttribute('class','d-none d-md-inline-block form-inline ml-auto mr-0 mr-md-3 my-2 my-md-0');
var storeSelect = document.createElement('select');
storeSelect.setAttribute('class','form-control');
var option = document.createElement('option');
option.text = 'Select one store';
option.value = -1;
storeSelect.add(option);
strForm.appendChild(storeSelect);

storeContent.appendChild(strForm);
populateStoreSelect();

//Create the search box for the product
var productContent = document.getElementById('productContent');
var prdForm =  document.createElement('form');
prdForm.setAttribute('class','d-none d-md-inline-block form-inline ml-auto mr-0 mr-md-3 my-2 my-md-0');
var prdSrcBox = document.createElement('input');
prdSrcBox.setAttribute('class','form-control');
prdSrcBox.setAttribute('placeholder','Search by product SKU');
var prdSrcBtn = document.createElement('button');
prdSrcBtn.setAttribute('class','btn btn-primary');
prdSrcBtn.setAttribute('type','button');
var prdSrcBtnLi = document.createElement('li');
prdSrcBtnLi.setAttribute('class','fa fa-search');

prdSrcBtn.appendChild(prdSrcBtnLi);
prdForm.appendChild(prdSrcBox);
prdForm.appendChild(prdSrcBtn);

productContent.appendChild(prdForm);



const div1 = document.createElement('div');
div1.setAttribute('class','card mb-3');
const div2 = document.createElement('card-header');
div2.setAttribute('class','card-header');
div2.textContent = "Product list";
const div3 = document.createElement('div');
div3.setAttribute('class','card-body');
const div4 = document.createElement('div');
div4.setAttribute('class','table-responsive');
const table = document.createElement('table');
table.setAttribute('class','table table-bordered');
table.setAttribute('width','100%');
table.setAttribute('cellspacing','0');
const thead = document.createElement('thead');
const tfoot = document.createElement('tfoot');
const tr = document.createElement('tr');
const th1 = document.createElement('th');
th1.textContent = 'Description';
const th2 = document.createElement('th');
th2.textContent = 'SKU';
const th3 = document.createElement('th');
th3.textContent = 'URL';
const th4 = document.createElement('th');
th4.textContent = 'Actions';          

const productContentBody = document.createElement('tbody');

productContent.appendChild(div1);
div1.appendChild(div2);
div2.appendChild(div3);
div3.appendChild(div4);
div4.appendChild(table);
table.appendChild(thead);
table.appendChild(tfoot);
table.appendChild(productContentBody);
tfoot.appendChild(tr);
thead.appendChild(tr);
tr.appendChild(th1);
tr.appendChild(th2);
tr.appendChild(th3);    
tr.appendChild(th4); 

const div1_1 = document.createElement('div');
div1_1.setAttribute('class','card mb-3');
const div2_1 = document.createElement('card-header');
div2_1.setAttribute('class','card-header');
div2_1.textContent = "Store Detail";
const div3_1 = document.createElement('div');
div3_1.setAttribute('class','card-body');
const div4_1 = document.createElement('div');
div4_1.setAttribute('class','table-responsive');
const table_1 = document.createElement('table');
table_1.setAttribute('class','table table-bordered');
table_1.setAttribute('width','100%');
table_1.setAttribute('cellspacing','0');
const thead_1 = document.createElement('thead');
const tfoot_1 = document.createElement('tfoot');
const tr_1 = document.createElement('tr');
const th1_1 = document.createElement('th');
th1_1.textContent = 'Name';
const th2_1 = document.createElement('th');
th2_1.textContent = 'Number';
const th3_1 = document.createElement('th');
th3_1.textContent = 'Location';
const th4_2 = document.createElement('th');
th4_2.textContent = 'Address';
const th5_1 = document.createElement('th');
th5_1.textContent = 'Postal Code';
const th6_1 = document.createElement('th');
th6_1.textContent = 'Active';
const th4_1 = document.createElement('th');
th4_1.textContent = 'Actions';          

const storeContentBody = document.createElement('tbody');

storeContent.appendChild(div1_1);
div1_1.appendChild(div2_1);
div2_1.appendChild(div3_1);
div3_1.appendChild(div4_1);
div4_1.appendChild(table_1);
table_1.appendChild(thead_1);
table_1.appendChild(tfoot_1);
table_1.appendChild(storeContentBody);
tfoot_1.appendChild(tr_1);
thead_1.appendChild(tr_1);
tr_1.appendChild(th1_1);
tr_1.appendChild(th2_1);
tr_1.appendChild(th3_1);    
tr_1.appendChild(th4_2);
tr_1.appendChild(th5_1);
tr_1.appendChild(th6_1);
tr_1.appendChild(th4_1);

storeSelect.onchange = ()=>
{
    listProducts = [];
    listStores = [];
    appendStoreToTable(storeSelect.value);
    populateProductsPerStore(storeSelect.value);
    
}

prdSrcBtn.onclick = () =>
{    
    let sku = prdSrcBox.value;    
    searchProduct(sku);
}

//Here I will search for the stores in the database
strSrcBtn.onclick = ()=>{
    
    let storeNumber = strStoreSrchBx.value;
    searchStore(storeNumber);
}

btnAddStore.onclick = ()=>
{
    console.log('This is where and store is added');    
    var storeNumber = document.getElementById('txtStoreNumberModal');
    var result = appendStoreToTable(storeNumber.innerText);

    console.log(result);
}

btnCancelStoreAdd.onclick = ()=>{
    storeModal.style.display = 'none';
    var storeName = document.getElementById('txtStoreNameModal');
    var storeNumber = document.getElementById('txtStoreNumberModal');
    var storeLocation = document.getElementById('txtStoreLocationModal');
    storeName.textContent = "";
    storeNumber.textContent = "";
    storeLocation.textContent = "";
};

btnCancelProduct.onclick = ()=>{
    ProductSearchModal.style.display = 'none';
    var prdTitle = document.getElementById('txtProductTitleModal');
    var prdSKU = document.getElementById('txtProductSKUModal');
    var prdURL = document.getElementById('txtProductURLModal');
    prdTitle.textContent = '';
    prdSKU.textContent = '';
    prdURL.textContent = '';
}

commitList.onclick = () =>{
    alert('Send the products to the table');
}

function removeElement(arr, value)
{
    return arr.filter(function(ele){
        return ele.SKU != value.SKU;
    });    
}

function containElement(arr, value)
{
    var res =  arr.filter((ele)=>{
        return ele.SKU == value.SKU;
    });
    if (res.length > 0)
    {
        return true;
    }
    else{
        return false;
    }
}

function removeElementStore(arr, value)
{
    return arr.filter(function(ele){
        return ele.Number != value.Number;
    });    
}

function containElementStore(arr, value)
{
    var res =  arr.filter((ele)=>{
        return ele.Number == value.Number;
    });
    if (res.length > 0)
    {
        return true;
    }
    else{
        return false;
    }
}