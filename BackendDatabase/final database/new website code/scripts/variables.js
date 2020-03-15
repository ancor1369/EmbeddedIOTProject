
const queryURL = 'http://localhost:3000';

function concatPath(one,two){
    return one + '/' + two;
}


function queryToAPI(crud,method, message)
{
    console.log('Promise query');
    return new Promise((resolve,reject)=>{
        URL = queryURL;
        URL = concatPath(URL,crud);
        console.log(URL);
        console.log(message);
        var request =  new XMLHttpRequest();

        request.open(method,URL,true);    
        if(message!=undefined) 
        {
            console.log('With cors');
            request.setRequestHeader("Content-Type", "application/json;charset=UTF-8");       
            request.send(JSON.stringify(message));           
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
