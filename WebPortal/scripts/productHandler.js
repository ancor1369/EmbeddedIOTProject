

function loadProductsTable()
{
var request =new XMLHttpRequest();
request.open('GET', 'http://localhost:7000/product',true);
request.onload = function()
{
    var data = JSON.parse(this.response);
    console.log(data);
}
request.send();

}

























