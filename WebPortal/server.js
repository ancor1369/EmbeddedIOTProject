var http = require('http');
var url = require('url');
var querystring = require('querystring');
var fs = require('fs');

const port = process.env.PORT || 3001;

http.createServer(function(req,res){
    pathname = url.parse(req.url).pathname;

    
   
    //pathname = '/Product.html';

    // if(pathname == '/')
    // {
    //     pathname = "/dashboard.html"

        
    // }    

    fs.readFile(__dirname + pathname, function(err,data)
    {       
        if(err)
        {
            res.writeHead(404,{'Content-Type':'text/plain'});
            res.write('Page not found');
            res.end();
        }
        else{            
            res.writeHead(200);
            res.write(data);
            res.end();
        }
    })
}).listen(port);

