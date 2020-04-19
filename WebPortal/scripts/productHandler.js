


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
                for(i=0;i<Object.keys(data).length;i++)
                    {
                        console.log(data[i]);

                        var obj =data[i];
                        var tre = document.createElement('tr');
                        var td1 = document.createElement('td');
                        td1.textContent = obj.ProductID; 
                        const PrdID = obj.ProductID;
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
                        
                    edit.onclick = function()
                    {
                        getSinglegleProduct(PrdID).then((response)=>
                       {
                            var productData = JSON.parse(response.product);
                        
                            var txtPrdID = document.getElementById('txtEditProductID');
                            var txtProductName = document.getElementById('txtEditProductName');
                            var txtDollar = document.getElementById('txtEditDollar');
                            var txCents = document.getElementById('txtEditCents');
                            var txDescription = document.getElementById('txtEditDescription');
                            var txURL = document.getElementById('txtEditURL');
                            var txSKU = document.getElementById('txtEditSKU');
                            var txEdit = document.getElementById('txtEditModel');
                            var txDue = document.getElementById('txtEditDueDate');
                            var txLayout = document.getElementById('txtEditLayoutName');
                            var txUpdate = document.getElementById('txtEditUpdate');
                            var txBlink = document.getElementById('txtEditBlink');
                            

                            txtPrdID.value = productData.productID;
                            txtProductName.value = productData.Name;
                            txtDollar.value = productData.PriceDollar;
                            txCents.value = productData.priceCents;
                            txDescription.value = productData.Description;
                            txURL.value = productData.URL;
                            txSKU.value = productData.SKU;
                            txEdit.value = productData.Model;
                            txDue.value = productData.DueDate;
                            txLayout.value = productData.LayoutName;
                            txUpdate.value = productData.Update;
                            txBlink.value = productData.Blink;
                            
                            
                            
                            
                            editModal.style.display="block";
                            
                            
                            
                            
                            
                    });

                }     
                }
            }
                request.send();


        }
         
        function getSinglegleProduct(prdID)
                {
                    return new Promise((resolve,reject)=>
                    {
                        var productGetter = new XMLHttpRequest();
                        var endPoint = 'http://localhost:7000/product/' + prdID;
                        console.log(endPoint);
                       productGetter.open('GET',endPoint);
                       productGetter.setRequestHeader('content-Type','application/jsonl charset=UTF-8');
                       
                       productGetter.send();

                        productGetter.onload = function(parameter)
                      {
                          if(parameter.target.status == 200)
                          {
                              try
                              {resolve({
                                  product: parameter.target.response
                              });

                              }
                              catch(error){
                                  console.log(error);
                                  reject(JSON.stringify(error));
                              }
                              
                          }
                          else{
                              reject('Reject');
                          }
                        }
                    });
                }

                    



function postProduct(message)
{
    var postMaker = new XMLHttpRequest();
    postMaker.open('POST','http://localhost:7000/product');
    postMaker.setRequestHeader('Content-type','application/json; charset=UTF-8');
    postMaker.send(message);
    postMaker.onload = function(parameter)
    {
        console.log(parameter);
        if(parameter.target.status == 200)
        {
            location.reload();
        }
    }

}





















