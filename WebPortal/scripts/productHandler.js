

function loadProductsTable()
{
    const div1 = document.createElement('div');
    div1.setAttribute('class','card mb-3');
    const div2 = document.createElement('card-header');
    div2.setAttribute('class','card -header');
    div2.textContent = "Product List";
    const div3 = document.createElement('div');
    div3.setAttribute('class','card mb-3');
    const div4= document.createElement('div');
    div4.setAttribute('class','table responsive');
    const table = document.createElement('table');
    table.setAttribute('class','table table-boarder');
    table.setAttribute('id','data table');
    table.setAttribute('width','100%');
    table.setAttribute('cellspacing','0');
    const thead = document.createElement('thead');
    const tfoot = document.createElement('tfoot');
    const tr = document.createElement('tr');
    const th1 = document.createElement('th');
    th1.textContent ='Product ID';
    const th2 = document.createElement('th');
    th2.textContent = 'Product Name';
    const th3 = document.createElement('th');
    th3.textContent = 'Price Dollar';
    const th4 = document.createElement('th');
    th4.textContent = 'Price Cent';
    const th5 = document.createElement('th');
    th5.textContent = 'Actions';
    const tbody = document.createElement('tbody');
    container.appendChild(div1);
    container.appendChild(div2);
    container.appendChild(div4);
    container.appendChild(table);
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

var request = new XMLHttpRequest();
request.open('GET','http://localhost:7000/product',true);
request.onload = function()
{
    var data = JSON.parse(this.response);
    console.log(data);
    for(i=0;i,Object.keys(data).length;i++)
        {
            console.log(data[i]);

            var obj =data[i];
            var tre = document.createElement('tr');
            var td1 = document.createElement('td');
            td1.textContent = obj.ProductID;
            var td2 = document.createElement('td');
            td2.textContent = obj.Name;
            
            var td3 = document.createElement('td');
            td3.textContent = obj.PriceDollar;
            // var tre = document.createElement('tr');
            var td4 = document.createElement('tr');
            td4.textContent = obj.PriceCents;
            var td5 = document.createElement('td');
            const edit = document.createElement('button');
            edit.setAttribute('class','btn btn-primary');
            edit.setAttribute('type','button');
            var sp = document.createElement('span');
            sp.setAttribute('class','fas fa-edit fa-fw');

            td5.appendChild(edit);

            tre.appendChild(td1);
            tre.appendChild(td2);
            tre.appendChild(td3);
            tre.appendChild(td4);
            tre.appendChild(td5);
            edit.appendChild(sp);
            tbody.appendChild(tre);
            
            

        }
}
request.send();


}

























