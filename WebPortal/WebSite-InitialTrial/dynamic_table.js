const express = require('express'); 
const app = express(); 
//app.use(require("cors")()) 
app.use(require('body-parser').json()) 
const _ = require('lodash');
var {product} = require('./models/product');
var {mongoose} = require('./db/mongoose');
const port = 7000;

app.use(function(req, res, next)
{
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
    res.header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
    next();
});

app.get('/product',(req,res)=>{
  console.log('getproduct');
  product.find({}).then((result)=>{
      res.send(result);
  });    
});

app.get('/product/:ProductID',(req,res)=>{
  var id = req.params.ProductID;    
  product.find({ProductID:id}).then((result)=>{
      res.send(result);
  }).catch((err)=>{
      res.send(err);
  })

});

app.post('/product',(req,res)=>{
  //If it can no create a new device, it will
  //update the existing one    
  console.log('postproduct');
  var body = _.pick(req.body,['ProductID','Name','','PriceDollar','PriceCents',
  'Model','blink','Update','LayoutName','SKU','URL','Description','DueDate']);    
  var avl = false;
  if(body.SKU === "000")
  {
      avl = true;
  }   
  var newproduct = new product({
      
      ProductID:body.ProductID,
      Name:body.Name,
      PriceDollar:body.PriceDollar,
      PriceCents:body.PriceCents,
      Description:body.Description,
      URL:body.URL,
      SKU:body.SKU,
      Model:body.Model,
      DueDate:body.DueDate,
      LayoutName:body.LayoutName,
      Update:body.Update,
      Blink:body.blink,
      Available:body.avl

  });    
  console.log(newproduct);
  newproduct.save().then((result)=>{
      res.send(result);
  },(error)=>{ console.log('error');
      res.status(400).send(error);
      
  });
});

app.patch('/product',(req,res)=>{
  //makes the update of the product
  console.log('patchproduct');
  var body = _.pick(req.body,['ProductID','Name','','priceDollar','pricecents',
  'Model','blink','Update','LayoutName','SKU','URL','Description','DueDate']);   
  product.findOneAndUpdate({ProductID:body.ProductID},{
       
    ProductID:body.ProductID,
    Name:body.Name,
    PriceDollar:body.PriceDollar,
    PriceCents:body.pricecents,
    Description:body.Description,
    URL:body.URL,
    SKU:body.SKU,
    Model:body.Model,
    DueDate:body.DueDate,
    LayoutName:body.LayoutName,
    Update:body.Update,
    Blink:body.blink,
    Available: body.avl
   
  
  }).then((result)=>{
      console.log('result');
      res.send(result);
  }).catch((error)=>{
      console.log('error');
      res.send(error);
  });
});



var listener = app.listen(port, () => {
  console.log('Your app is listening on port ' + listener.address().port);
});



