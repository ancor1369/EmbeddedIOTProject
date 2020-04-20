
//Requests to the API
function dltProductReq(SKU)
{
    var request = new XMLHttpRequest();
    var address = 'http://localhost:3000/products/' + SKU;    
    request.open('delete', address, true);
    //request.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');  
    request.send();    
    request.onload=function(parameter)
     {
        console.log(parameter);
        if(parameter.target.status == 200)
        {
            location.reload();          
        }
     }      
}

// var prod = JSON.parse(Product);
// console.log(prod);
// var editRequest = new XMLHttpRequest();
// var address = concatPath(queryURL, prod.SKU);
// console.log(address);
// editRequest.open('PATCH', address,true);
// editRequest.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
// editRequest.send(Product);

//Edit product
function edtProductReq(Product)
{    
    var prod = JSON.parse(Product);
    console.log(prod);
    var editRequest = new XMLHttpRequest();
    var URL = queryURL;
    URL = concatPath(URL,"products");
    var address = concatPath(URL, prod.SKU);
    console.log(address);
    editRequest.open('PATCH', address, true);
    editRequest.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
    editRequest.send(Product);

    editRequest.onload=function(parameter)
     {
        console.log(parameter);
        if(parameter.target.status == 200)
        {
            location.reload();                
        }
     }      
}

//Create product
function crtProductReq(message)
{
    var APIQuery = new XMLHttpRequest();
    APIQuery.open('post','http://localhost:3000/products');
    APIQuery.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
    APIQuery.send(message);
    
    APIQuery.onload=function(parameter)
    {
       console.log(parameter);
       if(parameter.target.status == 200)
       {
           location.reload();               
       }
    }   
}

//This method will obtain the product
function getSingleProduct(SKU){
    
    return new Promise((resolve,reject)=>{    
        var APIProduct = new XMLHttpRequest();
        var address = 'http://localhost:3000/products/' + SKU;
        console.log(address);
        APIProduct.open('get',address);
        APIProduct.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
        APIProduct.send();

        APIProduct.onload = function(parameter)
        {
            // console.log(parameter);
            // console.log(parameter.target.response);
            if(parameter.target.status == 200)
            {
                try{                    
                    resolve({
                        product: parameter.target.response
                    });
                }
                catch(e)
                {
                    console.log(e);
                    reject(JSON.stringify(e));
                }
            }
            else
            {
                reject('Not possible to obtain information');
            }
        }
    });
}

function loadProductsTable()
{
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
    table.setAttribute('id','dataTable');
    table.setAttribute('width','100%');
    table.setAttribute('cellspacing','0');
    const thead = document.createElement('thead');
    const tfoot = document.createElement('tfoot');
    const tr = document.createElement('tr');
    const th1 = document.createElement('th');
    th1.textContent = 'Title';
    const th2 = document.createElement('th');
    th2.textContent = 'SKU';
    const th3 = document.createElement('th');
    th3.textContent = 'UPC';
    const th4 = document.createElement('th');
    th4.textContent = 'Model';          
    const th5 = document.createElement('th');
    th5.textContent = 'URL';    
    const th6 = document.createElement('th');
    th6.textContent = 'Actions';
    const tbody = document.createElement('tbody');

    containder.appendChild(div1);
    div1.appendChild(div2);
    div2.appendChild(div3);
    div3.appendChild(div4);
    div4.appendChild(table);
    table.appendChild(thead);
    table.appendChild(tfoot);
    table.appendChild(tbody);
    tfoot.appendChild(tr);
    thead.appendChild(tr);
    tr.appendChild(th1);
    tr.appendChild(th2);
    tr.appendChild(th3);    
    tr.appendChild(th4);    
    tr.appendChild(th5);
    tr.appendChild(th6);

    var request = new XMLHttpRequest();
    request.open('GET', 'http://localhost:3000/products', true);    
    request.onload = function()
    {
        var data = JSON.parse(this.response);
        console.log(data);
    
        for(i=0; i < Object.keys(data).length ; i++)
        {
            var obj = data[i];                 
            var tre = document.createElement('tr');
            var td1 = document.createElement('td');
            td1.textContent = obj.Title;
            var td2 = document.createElement('td');
            td2.textContent = obj.SKU;
            const _SKU = obj.SKU;
            var td2_1 = document.createElement('td');
            td2_1.textContent = obj.UPC;
            var td3 = document.createElement('td');
            td3.textContent = obj.Model;
            var td4 = document.createElement('td');
            var link = document.createElement('a');
            link.setAttribute('href',obj.URL);
            link.setAttribute('target','_blank');            
            link.textContent = obj.URL;            
            td4.appendChild(link);
            // var td5 = document.createElement('td');
            // td5.textContent = obj.PriceDollar + ',' +obj.PriceCents;
            var td6 = document.createElement('td');
            const edit = document.createElement('button');
            edit.setAttribute('class', 'btn btn-primary');
            edit.setAttribute('type', 'button');           
            
            var sp = document.createElement('span');
            sp.setAttribute('class','fas fa-edit fa-fw');
            const del = document.createElement('button');
            del.setAttribute('class', 'btn btn-danger');
            del.setAttribute('type', 'button');
            //del.textContent = "Delete";
            var sp1 = document.createElement('span');
            sp1.setAttribute('class','fas fa-window-close fa-fw');
            td6.appendChild(edit);
            td6.appendChild(del)
            edit.appendChild(sp);
            del.appendChild(sp1);  
                        
            tre.appendChild(td1);
            tre.appendChild(td2);
            tre.appendChild(td2_1);
            tre.appendChild(td3);
            tre.appendChild(td4);
            // tre.appendChild(td5);      
            tre.appendChild(td6);     
            tbody.appendChild(tre);


            edit.onclick=function()
            {               
                
                getSingleProduct(_SKU).then((response)=>
                {
                    console.log(response);  
                     
                    try{
                        var product = JSON.parse(response.product);                    
                        var edtDesc = document.getElementById('txtEditDesc');
                        var edtSku = document.getElementById('txtEditSKU');
                        var edtUrl = document.getElementById('txtEditURL');
                        var edtModel = document.getElementById('txtEditModel');
                        var edtUPC = document.getElementById('txtEditUPC');
                        var edtTecSpect = document.getElementById('txtEditTecSpect');                        
                        
                        edtDesc.value = product[0].Title;                
                        edtSku.value = product[0].SKU;
                        edtUPC.value = product[0].UPC;
                        edtUrl.value = product[0].URL;
                        edtModel.value = product[0].Model;                                      
                        edtTecSpect.value = product[0].TechSpect;                            
                        EditModal.style.display = "block"; 
                    }     
                    catch(error){
                        console.log(error);
                    }             
                    
                    EditModal.style.display = "block";     
                },(reject)=>{
                    console.log('rejected', reject);
                });                                       
            }
            del.onclick = function(){                
                deleteModal.style.display = "block";
                SKUtoDelete = _SKU;                
            }
        }
    }
    request.send();
}

//Product listing on the screen
function loadProductsCards()
{
    var request = new XMLHttpRequest();

    request.open('GET', 'http://localhost:3000/products', true);    
    request.onload = function()
    {
        var data = JSON.parse(this.response);
        console.log(data);
    
        for(i=0; i < Object.keys(data).length ; i++)
        {
            var obj = data[i];            
            
            if((i%3)== 0)
            {
                const contain = document.createElement('div');
                contain.setAttribute('class','row');   
                containder.appendChild(contain);
            }

            const card = document.createElement('div');
            //card.setAttribute('class','card text-white bg-info mb-3'); 
            card.setAttribute('class','col-xl-3 col-sm-6 mb-3');
            var name = 'card' + i;
            card.setAttribute('name','card');
            card.setAttribute('id',name);
            const h1 = document.createElement('ul');
            h1.textContent = data[i].Description;
            h1.setAttribute('class','card-header');             
            
            const uiE = document.createElement('ul');
            uiE.setAttribute('class','list-group list-group-flush'); 
            const SKU = document.createElement('li');
            SKU.setAttribute('class','list-group-item'); 
            SKU.textContent = 'SKU: ' + obj.SKU;                
            uiE.appendChild(SKU);
            const URL = document.createElement('li');
            URL.setAttribute('class','list-group-item card-link'); 
            const Link = document.createElement('a');
            Link.setAttribute('href',obj.URL);
            Link.setAttribute('target','_blank');
            Link.textContent = 'URL: ' + obj.URL;
            URL.appendChild(Link);        
            uiE.appendChild(URL);

            const Model = document.createElement('li');
            Model.textContent = 'Model: ' + obj.Model;
            Model.setAttribute('class','list-group-item'); 
            uiE.appendChild(Model);
            const Price = document.createElement('li');
            Price.textContent = 'Price: ' + obj.PriceDollar + ','+ obj.PriceCents;;
            Price.setAttribute('class','list-group-item');         
            uiE.appendChild(Price);                   
            
            const btnEdit = document.createElement('Button');
            btnEdit.setAttribute('type','button');
            btnEdit.setAttribute('id','btnEdit');
            btnEdit.setAttribute('class','btn btn-primary');
            btnEdit.textContent = "Edit";
            btnEdit.onclick=function(){                
                var edtDesc = document.getElementById('txtEditDesc');
                var edtSku = document.getElementById('txtEditSKU');
                var edtUrl = document.getElementById('txtEditURL');
                var edtModel = document.getElementById('txtEditModel');
                var edtPrice = document.getElementById('txtEditPrice');
                var edtTecSpect = document.getElementById('txtEdittecSpect');
                var edtDueDate = document.getElementById('txtEditDueDate');                
                
                edtDesc.value = h1.textContent;                
                edtSku.value = SKU.textContent.substr(5);
                edtUrl.value = URL.textContent.substring(5);
                edtModel.value = Model.textContent.substr(7);
                edtPrice.value = Price.textContent.substring(7);

                EditModal.style.display = "block";              
            }
            uiE.appendChild(btnEdit);
            const btnDelete = document.createElement('button');
            btnDelete.setAttribute('type', 'button');
            btnDelete.setAttribute('id','deleteButton');
            btnDelete.setAttribute('class','btn btn-danger');
            btnDelete.textContent = 'Delete';
            btnDelete.onclick=function(){
                
                var sku = SKU.textContent.substring(5);                                
                var ans = confirm("Are you sure you want to delete this item?");
                if(ans==true)
                {
                    dltProductReq(sku);
                }                
            }
            uiE.appendChild(btnDelete);    

            containder.appendChild(card);            
            card.appendChild(h1);        
            card.appendChild(uiE); 
        }

    }

    request.send();
}