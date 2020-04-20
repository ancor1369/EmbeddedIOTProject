function GenerateTable() {
    //Build an array containing Customer records.
    var customers = new Array();
    customers.push(["Customer Id", "Name", "Country"]);
    customers.push([1, "John Hammond", "United States"]);
    customers.push([2, "Mudassar Khan", "India"]);
    customers.push([3, "Suzanne Mathews", "France"]);
    customers.push([4, "Robert Schidner", "Russia"]);

    //Create a HTML Table element.
    var table = document.createElement("TABLE");
    table.border = "1";

    //Get the count of columns.
    var columnCount = customers[0].length;

    //Add the header row.
    var row = table.insertRow(-1);
    for (var i = 0; i < columnCount; i++) {
        var headerCell = document.createElement("TH");
        headerCell.innerHTML = customers[0][i];
        row.appendChild(headerCell);
    }
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



    //Add the data rows.
    for (var i = 1; i < customers.length; i++) {
        row = table.insertRow(-1);
        for (var j = 0; j < columnCount; j++) {
            var cell = row.insertCell(-1);
            cell.innerHTML = customers[i][j];
        }
    }

    var dvTable = document.getElementById("dvTable");
    dvTable.innerHTML = "";
    dvTable.appendChild(table);
}