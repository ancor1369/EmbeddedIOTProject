
//General function to interact with the API.
//Same method, different use cases
function promiseQuery(crud,method, message)
{
    console.log('Promise query');
    return new Promise((resolve,reject)=>{
        URL = queryURL;
        URL = concatPath(URL,crud);
        console.log(URL);
        var request =  new XMLHttpRequest();

        request.open(method,URL,true);    
        if(message!=undefined) 
        {
            console.log('With cors');
            request.setRequestHeader('Content-Type', 'application/json; charset=UTF-8');       
            request.send(message);
        }
        else
        {
            request.send();
        }
        
        request.onload=function(result){
            if(result.target.status == 200)
            {
                resolve(result);
            }
            else{
                reject('Result not retrived');
            }
        }
    });
}

function promiseGetAll()
{
    return promiseQuery('store','get','');
}


function loadStoresList()
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
    th1.textContent = 'Name';
    const th2 = document.createElement('th');
    th2.textContent = 'Number';
    const th3 = document.createElement('th');
    th3.textContent = 'Active';
    const th4 = document.createElement('th');
    th4.textContent = 'Location';          
    const th5 = document.createElement('th');
    th5.textContent = 'Address';    
    const th6 = document.createElement('th');
    th6.textContent = 'Actions';
    const tbody = document.createElement('tbody');

    container.appendChild(div1);
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

    var storesPromise = promiseQuery('store','get');

    storesPromise.then((result)=>{
        var data = JSON.parse(result.target.response);
        console.log(data);
        for(i=0; i<Object.keys(data).length; i++)
        {
            var obj = data[i];
            var tre = document.createElement('tr');
            var td1 = document.createElement('td');
            td1.textContent = obj.Name;
            var td2 = document.createElement('td');
            td2.textContent = obj.Number;
            const storeNumber = obj.Number;
            const id = obj._id;
            var td2_1 = document.createElement('td');
            if(obj.Active==true){
                td2_1.textContent = 'Yes';
            }
            else{
                td2_1.textContent = 'No';
            }
            var td3 = document.createElement('td');
            td3.textContent = obj.City+ ', ' + obj.Province + ', ' + obj.Country ;
            var td4 = document.createElement('td');                      
            td4.textContent = obj.Address + ',' + obj.PostalCode;
            var td6 = document.createElement('td');
            const edit = document.createElement('button');
            edit.setAttribute('class', 'btn btn-primary');
            edit.setAttribute('type', 'button');           
            
            var sp = document.createElement('span');
            sp.setAttribute('class','fas fa-edit fa-fw');
            const del = document.createElement('button');
            del.setAttribute('class', 'btn btn-danger');
            del.setAttribute('type', 'button');            
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
            tre.appendChild(td6);     
            tbody.appendChild(tre);

            edit.onclick=function()
            {               
                
                var crudStore = 'store/'+storeNumber;
                storeToEdit = storeNumber;       
                storeToEditID = id;         
                promiseQuery(crudStore,'get').then((response)=>{
                    
                    try{
                        var storeData = JSON.parse(response.target.response);                                           
                        storeName.value = storeData[0].Name;                
                        store_Number.value = storeData[0].Number;
                        storeCity.value = storeData[0].City;
                        storeCountry.value = storeData[0].Country;
                        storeProvince.value = storeData[0].Province;                                      
                        storeAddress.value = storeData[0].Address;  
                        storePostalCode.value = storeData[0].PostalCode;
                        console.log(storeData[0].Active);
                        if(storeData[0].Active == true)
                        {                            
                            raEditTrue.checked = true;                            
                        }
                        else{                                                        
                            raEditFalse.checked = true;
                        }
                        warningEditModal.style.display = "none";
                        EditModal.style.display = "block"; 
                        
                    }     
                    catch(error){
                        console.log(error);
                    }             
                    
                    EditModal.style.display = "block"; 
                    warningEditModal.style.display = "none";


                }).catch((error)=>{
                        console.log(error);
                });               
                                               
            }
            del.onclick = function(){       

                if(confirm('Are you sure you want to delete the store?'))
                {                      
                    var query = 'store/'+id; 
                    var delPromise = promiseQuery(query,'DELETE','');
                    delPromise.then((result)=>{                                                
                        location.reload();
                    }).catch((err)=>{
                        console.log('Error', + err);
                    });
                }   
                
                
            }


        }
    }).catch((error)=>
    {
        console.log(error);
    });
}

