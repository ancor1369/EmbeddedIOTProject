
const app = document.getElementById('content-wraper');

//Create button definition
var createButton = document.createElement('Button');
createButton.setAttribute('type','button');
createButton.setAttribute('class','btn btn-primary');
createButton.setAttribute('id','BtncreateBranch');
createButton.textContent = 'Create Branch';

const container = document.createElement('div');
container.setAttribute('class','contain-fluid');

app.appendChild(createButton);
app.appendChild(container);
var storeToEdit = "";
var storeToEditID = "";

var CreateModal = document.getElementById('createBranch');
var EditModal = document.getElementById('editBranch');
var warningAlertModal = document.getElementById('createIncompleteAlert');
var warningEditModal = document.getElementById('editIncompleteAlert');
//Create the handlers fot the modal window
var createBranch = document.getElementById('btnCreateBranch');
var cancelBranch = document.getElementById('btnCancelBranch');
var editBranchSave = document.getElementById('btnEditBranch');
var cancelEditBranch = document.getElementById('btnCancelEditBranch');

//Branch data to create
var txtName = document.getElementById('txtName');
var txtNumber = document.getElementById('txtNumber');
var txtCountry = document.getElementById('txtCountry');
var txtProvince = document.getElementById('txtProvince');
var txtProvince = document.getElementById('txtProvince');
var txtAddress = document.getElementById('txtAddress');
var txtPC = document.getElementById('txtPC');

//to edit

var storeName = document.getElementById('txtEditName');
var store_Number = document.getElementById('txtEditNumber');
var storeCountry = document.getElementById('txtEditCountry');
var storeProvince = document.getElementById('txtEditProvince');
var storeCity = document.getElementById('txtEditCity');
var storeAddress = document.getElementById('txtEditAddress');                        
var storePostalCode = document.getElementById('txtEditPC');
var raEditTrue = document.getElementById('raEditTrue');
var raEditFalse = document.getElementById('raEditFalse');

loadStoresList();


//Populate the table upfront
// var AllStores = promiseGetAll();

// AllStores.then((result)=>{
//     var response = JSON.parse(result.target.response);
//     console.log(response);
// }).catch((error)=>{
//     console.log(error);
// });


editBranchSave.onclick = ()=>
{
    var actv;    
    if(raEditTrue.checked)
    {
        actv =  true;
    }
    else{
        actv =  false;
    }


    var msg = JSON.stringify({
        Name:storeName.value,
        Number:store_Number.value,
        Country:storeCountry.value,
        Province : storeProvince.value,
        City: storeCity.value,
        Address: storeAddress.value,
        PostalCode: storePostalCode.value,
        Active: actv
        });

    console.log(msg);   

    var endPoint= 'store/'+storeToEditID;
    var patchStore = promiseQuery(endPoint,'PATCH',msg);

    patchStore.then((result)=>{
        console.log(result);
        //location.reload();
    }).catch((error)=>{
        console.log(error);
    });
}

// cancelEditBranch.onclick = ()=>
// {

// }

//Clcik handler for the buttons in the form
createButton.onclick = ()=>{
    CreateModal.style.display = "block";
    warningAlertModal.style.display = "none"
    document.getElementById("raTrue").checked = true;
}

createBranch.onclick = ()=>{
  
    var active = document.getElementById('raTrue').checked;
    
    var message = JSON.stringify(
        {
            Name:txtName.value,
            Country:txtCountry.value,
            Province:txtProvince.value,
            City:txtCity.value,
            Number: txtNumber.value,
            Address: txtAddress.value,
            PostalCode:txtPC.value,
            Active: active
        }
    );        
    console.log(message);

    var createStore = promiseQuery('store','post',message);
    createStore.then((result)=>{
        console.log('Product created');
        console.log(result);
        //location.reload();
    }).catch((error)=>{
        console.log('There was a problem creating the store')
    });    
}

cancelBranch.onclick = ()=>
{
   
    txtName.value = "";
    txtNumber.value = "";
    txtCountry.value = "";
    txtProvince.value = "";
    txtAddress.value = "";
    txtPC.value = "";
    CreateModal.style.display = 'none';    
}

cancelEditBranch.onclick =()=> 
{
    storeName.value = "";
    store_Number.value = "";
    storeCountry.value = "";
    storeProvince.value = ""; 
    storeCity.value = ""; 
    storeAddress.value = ""; 
    storePostalCode.value = ""; 
    EditModal.style.display = "";     
}