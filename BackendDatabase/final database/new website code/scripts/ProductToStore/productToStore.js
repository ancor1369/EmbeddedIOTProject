
function searchProduct(sku)
{
    console.log(sku);
    if(sku=='')
    {
        alert('Please type a SKU');
        return;
    }
    var query = 'products' +'/'+sku;
    var resultQuery = queryToAPI(query,'get');
    resultQuery.then((result)=>
    {
        var resJSON = JSON.parse(result.target.response);
        showModalProduct(resJSON);
    }).catch((err)=>
    {
        console.log(err);
    });
}

//This window allow the user to see what is the product that was found
function showModalProduct(product)
{    
    if(product.length != 0)
    {
        var prdTitle = document.getElementById('txtProductTitleModal');
        var prdSKU = document.getElementById('txtProductSKUModal');
        var prdURL = document.getElementById('txtProductURLModal');
        var addBtn = document.getElementById('btnAddProduct');
        var cancelBtn = document.getElementById('btnCancelProduct');
        prdTitle.textContent = product[0].Title;    
        prdSKU.textContent = product[0].SKU;        
        var link = document.createElement('a');
        link.setAttribute('href',product[0].ShortURL);
        link.setAttribute('target','_blank');
        link.textContent = product[0].ShortURL;
        prdURL.appendChild(link);
        ProductSearchModal.style.display = 'block';

        addBtn.onclick = ()=>
        {           
            console.log('This is where product is added');
            var sku = document.getElementById('txtProductSKUModal');    
            var result  = appendPrdToTable(sku.innerText);
            prdTitle.textContent = '';
            prdSKU.textContent = '';
            prdURL.textContent = '';
            link.textContent = '';
            console.log(result); 
        };

        cancelBtn.onclick = ()=>{
            prdTitle.textContent = '';
            prdSKU.textContent = '';
            prdURL.textContent = '';
            link.textContent = '';
            ProductSearchModal.style.display = 'none';
        }

    }
    else{        
        NotFoundModal.style.display = 'block';
        setTimeout(()=>{
            NotFoundModal.style.display = 'none';
        },1500);
       }
   
}

//this function appends a new product to the table
function appendPrdToTable(sku)
{    
    console.log(sku);
    if(sku.length != 0)
    {             
        //Get the product again from the service
        var query = 'products' +'/'+sku;
        var resultQuery = queryToAPI(query,'get');
        resultQuery.then((result)=>{
            var resJSON = JSON.parse(result.target.response);  
            console.log(resJSON);    
            var prd = 
            {
                SKU: resJSON[0].SKU,
                Title: resJSON[0].Title,               
                URL: resJSON[0].ShortURL                                
            }        
            if(containElement(listProducts, prd))
            {        
                ProductSearchModal.style.display = 'none';                
                return;
            } 
            else{
                listProducts.push(prd);
                //send the request to the API to add the new product
                if(listProducts.length == 1)   
                {
                    //Backend service needs modification to 
                    //support this functionlity
                    console.log('Post store');
                    var message = 
                    {
                        SKU: sku,
                        Name: listStores[0].Name,
                        Number:listStores[0].Number
                    }
                    console.log(message);
                    var query = 'storeproduct';
                    var resQ = queryToAPI(query,'post', message);
                    resQ.then((result)=>{
                        console.log(result);
                    }).catch((error)=>{
                        console.log(error);
                        return;
                    });
                }
                else
                {
                    console.log('Patch store');                   
                    var msj = {
                        SKU: sku,
                        Name: listStores[0].Name,
                        Number: listStores[0].Number
                    }                    
                    var query = 'storeProduct/';
                    var resQ = queryToAPI(query,'PATCH', msj);
                    resQ.then((resutl)=>{
                        console.log(resutl)
                    }).catch((error)=>{
                        console.log(error);
                    });
                }
            }
            var tr = document.createElement('tr');
            var th1 = document.createElement('th');
            th1.textContent = resJSON[0].Title;
            var th2 = document.createElement('th');
            th2.textContent = resJSON[0].SKU;
            var link = document.createElement('a');
            link.setAttribute('href',resJSON[0].ShortURL);
            link.setAttribute('target','_blank');
            link.textContent = resJSON[0].ShortURL;
            var th3 = document.createElement('th');            
            th3.appendChild(link);
            var dltBtn = document.createElement('button');
            dltBtn.setAttribute('class','btn-danger');            
            var spa = document.createElement('span');
            spa.setAttribute('class','fas fa-window-close fa-fw');
            dltBtn.appendChild(spa);
            
            var th4 = document.createElement('th');
            th4.appendChild(dltBtn);
               
            tr.appendChild(th1);
            tr.appendChild(th2);
            tr.appendChild(th3);
            tr.appendChild(th4);
            productContentBody.appendChild(tr);            
            ProductSearchModal.style.display = 'none';            
            
            // dltBtn.onclick = () =>{
            //     alert(th2.textContent);
            // }
            dltBtn.onclick = ()=>{                
                productContentBody.removeChild(tr);   
                var remObject =
                {
                    Title: th1.textContent,
                    SKU: th2.textContent,
                    URL: th3.textContent
                }             
                var res = removeElement(listProducts, remObject);
                console.log(res);
                listProducts = res;
            }
            
        }).catch((err)=>
        {
            console.log(err);
        });     
    }    
}

function searchStore(number)
{
    var query = 'store' +'/'+number;
    var resultQuery = queryToAPI(query,'get');
    resultQuery.then((result)=>{
        var resJSON = JSON.parse(result.target.response);
        showModalStore(resJSON);
        console.log(resJSON);
    }).catch((err)=>
    {
        console.log(err);
    });
}

function showModalStore(StoreData)
{
    console.log(StoreData);
    
    if(StoreData.length != 0)
    {
        var storeName = document.getElementById('txtStoreNameModal');
        var storeNumber = document.getElementById('txtStoreNumberModal');
        var storeLocation = document.getElementById('txtStoreLocationModal');
    if(StoreData.length != 0)
        storeName.textContent = StoreData[0].Name;    
        storeNumber.textContent = StoreData[0].Number;
        storeLocation.textContent = StoreData[0].Address + ', ' +StoreData[0].city;
        storeModal.style.display = 'block';
    }
    else{        
        NotFoundModal.style.display = 'block';
        setTimeout(()=>{
            NotFoundModal.style.display = 'none';
        },1500);
       }
}

function appendStoreToTable(storeNumber)
{    
    var tra = storeContentBody.lastElementChild;    
    if(tra != null)
    {    
        storeContentBody.deleteRow(tra);
    }         
    var query = 'store' +'/'+storeNumber;
    var resultQuery = queryToAPI(query,'get');
    resultQuery.then((result)=>{
        var storeInfo = JSON.parse(result.target.response);
        var store =
        {
            Number: storeInfo[0].Number,
            Name: storeInfo[0].Name
        }               
        listStores.push(store);
        var tr = document.createElement('tr');
        var th1 = document.createElement('th');
        var th2 = document.createElement('th');
        var th3 = document.createElement('th');   
        var th4_1 = document.createElement('th');
        var th5 = document.createElement('th');
        var th6 = document.createElement('th');
        var th4 = document.createElement('th');
        th1.textContent = storeInfo[0].Name;
        th2.textContent = storeInfo[0].Number;
        th3.textContent = storeInfo[0].Country+', '+ storeInfo[0].Province +', ' + storeInfo[0].City;
        th4_1.textContent = storeInfo[0].Address;
        th5.textContent = storeInfo[0].PostalCode;
        th6.textContent = storeInfo[0].Active;
        var listButton =  document.createElement('button');        
        listButton.setAttribute('class', 'btn-primary');
        listButton.textContent='List';      
        th4.appendChild(listButton);        
        tr.appendChild(th1);
        tr.appendChild(th2);
        tr.appendChild(th3);
        tr.appendChild(th4_1);
        tr.appendChild(th5);
        tr.appendChild(th6);
        tr.appendChild(th4);        
        storeContentBody.appendChild(tr);          
        
        listButton.onclick =()=>{
            alert('List');
        }               

    }).catch((err)=>
    {
        console.log(err);
    });
}

function populateProductsPerStore(storeID)
{
    console.log('Populate');
    var query = 'storeproduct/' + storeID;
    var resultQuery = queryToAPI(query,'get');
    resultQuery.then((result)=>{
        var resJSON = JSON.parse(result.target.response);        
        PopulateProducts(resJSON);
    }).catch((error)=>{
        console.log(error);
    });
}

function PopulateProducts(Jobject)
{      
    var exiting = productContentBody.lastElementChild;
    if(exiting!=null)
    {
      while(exiting)
      {
        productContentBody.removeChild(exiting);
        exiting = productContentBody.lastElementChild;
      }
    }

    if(Jobject.Result == "NoProducts")
    {
        alert('This store does not have products');
        return;
    }

    Jobject.forEach((resJSON, index, array)=>{
        
        if(resJSON.length > 0)
        {               
            var prod = 
            {
                SKU: resJSON[0].SKU,
                Title: resJSON[0].Title,               
                URL: resJSON[0].ShortURL                                
            }        
            if(containElement(listProducts, prod))
            {                 
                return;
            }            
            else{
                listProducts.push(prod);
            }            
            var tr = document.createElement('tr');
            var th1 = document.createElement('th');
            th1.textContent = resJSON[0].Title;
            var th2 = document.createElement('th');
            th2.textContent = resJSON[0].SKU;
            var link = document.createElement('a');
            link.setAttribute('href',resJSON[0].ShortURL);
            link.setAttribute('target','_blank');
            link.textContent = resJSON[0].ShortURL;
            var th3 = document.createElement('th');            
            th3.appendChild(link);
            var deleteBtn = document.createElement('button');
            var spa =  document.createElement('span');
            spa.setAttribute('class','fas fa-window-close fa-fw');
            deleteBtn.setAttribute('class','btn btn-danger');
            deleteBtn.appendChild(spa);                    
            var th4 = document.createElement('th');
            th4.appendChild(deleteBtn);                        
            tr.appendChild(th1);
            tr.appendChild(th2);
            tr.appendChild(th3);
            tr.appendChild(th4);
            productContentBody.appendChild(tr);
            ProductSearchModal.style.display = 'none';            
            deleteBtn.onclick = () =>{
                productContentBody.removeChild(tr);                
                deleteStore(resJSON[0].SKU);
            }           
        }

    });
}

function deleteStore(sku)
{
    var temp = [];
    //Remove the variable from the array 
    //where I keep the units of the store
    listProducts.forEach((item,index,array)=>{
        console.log(item.SKU); 
        if(item.SKU != sku)       
        {
            temp.push(item);
        }        
    });
    listProducts = [];
    listProducts = temp;
    console.log(temp);
    var delObj =
    {
        SKU: sku,
        Name: listStores[0].Name,
        Number: listStores[0].Number
    }
    var query = 'storeProduct';
    var resPromise = queryToAPI(query,'delete',delObj);
    resPromise.then((result)=>{
        console.log(result);
    }).catch((error)=>{
        console.log(error);
    });    
}

function populateStoreSelect() 
{
    var query = 'store';
    var resultQuery = queryToAPI(query,'get');
    resultQuery.then((result)=>
    {
        var resJSON = JSON.parse(result.target.response);
        populateStores(resJSON);
    }).catch((err)=>
    {
        console.log(err);
    });
}

function populateStores(Jobject)
{
    Jobject.forEach((store,index,array)=>
    {
        var opt = document.createElement('option');
        opt.text = store.Number +': '+store.Name;
        opt.value = store.Number;
        storeSelect.appendChild(opt);
    });
}
