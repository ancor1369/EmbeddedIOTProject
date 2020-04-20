
// This function will retrive the requested price from the database
function searchOnePrice(ProductSKU)
{    
    //In this method I make sure that the two methods are created so that they 
    //are trigered sequencially and I can make sure that the resulst come as are needed.
    var priceHistory = promiseUnits('prices',ProductSKU);   
    priceHistory.then(function(result){
        var priceHistory =  JSON.parse(result.explicitOriginalTarget.response);
        console.log(priceHistory);
        var product = promiseUnits('products',ProductSKU);
        product.then(function(result)
        {
            console.log("Enters here");
            var prd = JSON.parse(result.explicitOriginalTarget.response);
            //console.log(prd);
            ProductInfo(prd);
            createTablePrice(priceHistory);            
            console.log(prd);
        },function(err)
        {
            console.log(err);
        });
        
        console.log('Done');
    },function(err){
        console.log(err);
    });   
}

function saveNewPrice()
{
    var whole = parseInt(udtPrice.value);
    var fraction = (udtPrice.value-whole)*100;
    fraction = parseInt(fraction);
    console.log(fraction);
    udtType;
    udtStartDate;
    udtDueDate; 

    var message = {        
        "productSKU":ProductSKU, 
        "priceWhole":whole,
        "priceFraction":fraction,
        "type":udtType.value,
        "startDate":udtStartDate.value,
        "dueDate":udtDueDate.value 
    }

    var messageObject = JSON.stringify(message);
    console.log(message);
    var updateResult = promiseUpdate(messageObject);

    updateResult.then((result)=>
    {
        console.log(result);
    },(err)=>{
        
    });
}

function promiseUnits(crud,id)
{
    return new Promise((resolve,reject)=>{
        URL = queryURL;
        URL = concatPath(URL,crud);
        URL = concatPath(URL,id);
        var request =  new XMLHttpRequest();

        request.open('get',URL,true);
        request.send();        
        request.onload=function(result){
            if(result.target.status = 200)
            {
                resolve(result);
            }
            else{
                reject('Result not retrived');
            }
        }
    });
}

function promiseUpdate(messageObject)
{
    return new Promise((resolve,reject)=>{
        URL = queryURL;
        URL = concatPath(URL,'prices');        
        
        var request =  new XMLHttpRequest();

        request.open('PATCH',URL,true);
        request.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');
        request.send(messageObject);        
        request.onload=function(result){
            if(result.target.status = 200)
            {
                resolve(result);
            }
            else{
                reject('Result not retrived');
            }
        }
    });
}

function ProductInfo(prd)
{
    
    try
    {
        console.log("ProductInfo");
        var rmDiv = document.getElementById('prdDiv');
        console.log(rmDiv);
        rmDiv.remove();
    }
    catch(Err)
    {        
        console.log(Err);
    }
    console.log(prd)
    var productResult =  prd[0];
    console.log('Product info');    
    console.log(productResult);

    const divp1 = document.createElement('div');
    divp1.setAttribute('class','card mb-3');
    divp1.setAttribute('id','prdDiv');
    const divp2 = document.createElement('card-header');
    divp2.setAttribute('class','card-header');
    divp2.textContent = "Product Information";
    const divp3 = document.createElement('div');
    divp3.setAttribute('class','card-body');
    const divp4 = document.createElement('div');
    divp4.setAttribute('class','table-responsive');
    const tablep = document.createElement('table');
    tablep.setAttribute('class','table table-bordered');
    tablep.setAttribute('id','dataTable');
    tablep.setAttribute('width','100%');
    tablep.setAttribute('cellspacing','0');
    const theadp = document.createElement('thead');
    const tfootp = document.createElement('tfoot');
    const trp = document.createElement('tr');
    const th1p = document.createElement('th');
    th1p.textContent = 'Title';
    const th2p = document.createElement('th');
    th2p.textContent = 'SKU';
    const th3p = document.createElement('th');
    th3p.textContent = 'UPC';    
    const tbodyp = document.createElement('tbody');

    containder.appendChild(divp1);
    divp1.appendChild(divp2);
    divp2.appendChild(divp3);
    divp3.appendChild(divp4);
    divp4.appendChild(tablep);
    tablep.appendChild(theadp);
    tablep.appendChild(tfootp);
    tablep.appendChild(tbodyp);
    tfootp.appendChild(trp);
    theadp.appendChild(trp);
    trp.appendChild(th1p);
    trp.appendChild(th2p);
    trp.appendChild(th3p);        

    var trpr = document.createElement('tr');
    var tdp1 = document.createElement('td');
    tdp1.textContent = productResult.Title;
    var tdp2 =  document.createElement('td');
    tdp2.textContent = productResult.SKU;
    var tdp3 = document.createElement('td');
    tdp3.textContent = productResult.UPC;
    
    trpr.appendChild(tdp1);
    trpr.appendChild(tdp2);
    trpr.appendChild(tdp3);
    tbodyp.appendChild(trpr);

    var updatePrice = document.createElement('button');
    updatePrice.setAttribute('id','updatePrice');
    updatePrice.setAttribute('type','button');
    updatePrice.setAttribute('class','bg-primary mb-3');    
    updatePrice.innerHTML = 'New Price';
    divp1.appendChild(updatePrice);

    updatePrice.onclick = function()
    {
        udtPrice.value = '';
        udtType.value = '';
        udtStartDate.value = '';
        udtDueDate.value = '';
        modalUpdate.style.display = "block";
    }
}

function createTablePrice(pricehistory)
{
    //If the div already exists, it is removed, otherwise it does its natural task
    try{
        var rmDiv = document.getElementById('priceDif');
        rmDiv.remove();
    }
    catch{

    }
    
    console.log('Table Creation'); 
    //console.log(pricehistory);
    const div1 = document.createElement('div');
    div1.setAttribute('class','card mb-3'); 
    div1.setAttribute('id','priceDif');
    const div2 = document.createElement('card-header');
    div2.setAttribute('class','card-header');
    div2.textContent = "Price History";
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
    th1.textContent = 'Price';
    const th2 = document.createElement('th');
    th2.textContent = 'Start Date';
    const th3 = document.createElement('th');
    th3.textContent = 'End Date';
    const th4 = document.createElement('th');
    th4.textContent = 'Type';              
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

    var dueDate = createDateFormat(pricehistory.dueDate);
    var startDate = createDateFormat(pricehistory.startDate); 
    var _type = pricehistory.type;           
    var price = '$ ' +  pricehistory.priceWhole + '.' + parseInt(pricehistory.priceFraction);
    
    var trt =  document.createElement('tr');
    trt.setAttribute('class','bg-warning');
    var td1 = document.createElement('td');
    td1.textContent = price;
    var td2 = document.createElement('td');
    td2.textContent = startDate;
    var td3 = document.createElement('td');
    td3.textContent = dueDate;
    var td4 = document.createElement('td');
    td4.textContent = _type;
    trt.appendChild(td1);
    trt.appendChild(td2);
    trt.appendChild(td3);
    trt.appendChild(td4);
    tbody.appendChild(trt);        
    var prices = pricehistory.priceHistory;
    console.log(prices);
    for(i=0; i < Object.keys(prices).length ; i++)
    {
        var oldPrice = prices[i];
        console.log(oldPrice);
        var trpr = document.createElement('tr');
        var td1pr = document.createElement('td');
        td1pr.textContent = '$ ' + oldPrice.priceWhole + '.' + parseInt(oldPrice.priceFraction);
        var td2pr = document.createElement('td');
        td2pr.textContent = createDateFormat(oldPrice.startDate);
        var td3pr = document.createElement('td');
        td3pr.textContent = createDateFormat(oldPrice.dueDate);
        var td4pr = document.createElement('td');
        td4pr.textContent = oldPrice.type;

        trpr.appendChild(td1pr);
        trpr.appendChild(td2pr);
        trpr.appendChild(td3pr);
        trpr.appendChild(td4pr);
        tbody.appendChild(trpr);
    }    
}

function createDateFormat(dateFormat)
{
    var dateObjGen = new Date(dateFormat);
    var startDateMMGen = dateObjGen.getMonth(); 
    var startDateDayGen = dateObjGen.getUTCDate();
    var startDateYearGen = dateObjGen.getUTCFullYear();

    var startDate = startDateMMGen + '/' + startDateDayGen + '/' + startDateYearGen;
    return startDate;
}






