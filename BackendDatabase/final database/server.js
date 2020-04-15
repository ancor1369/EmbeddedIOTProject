const express = require('express'); 
const app = express(); 
//app.use(require("cors")()) 
app.use(require('body-parser').json()) 
const _ = require('lodash');
var {product} = require('./models/product');
var {label} = require('./models/label');
var {labelproduct} = require('./models/labelproduct');
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

app.put('/product',(req,res)=>{
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


app.get('/label',(req,res)=>{
  console.log('getlabel');
  label.find({}).then((result)=>{
      res.send(result);
  });    
});

app.get('/label/:labelNumber',(req,res)=>{
  var id = req.params.labelNumber;    
  label.find({labelNumber:Number}).then((result)=>{
      res.send(result);
  }).catch((err)=>{
      res.send(err);
  })

});

app.post('/label',(req,res)=>{
  //If it can no create a new device, it will
  //update the existing one    
  console.log('postlabel');
  var body = _.pick(req.body,['LabelNumber','LabelName']);    
 
  var newlabel = new label({
      
      LabelNumber:body.LabelNumber,
      LabelName:body.LabelName
      
  });    
  console.log(newlabel);
  newlabel.save().then((result)=>{
      res.send(result);
  },(error)=>{ console.log('error');
      res.status(400).send(error);
      
  });
});

app.put('/label',(req,res)=>{
  //If it can no create a new device, it will
  //update the existing one    
  console.log('postlabel');
  var body = _.pick(req.body,['LabelNumber','LabelName']);    
 
  var newlabel = new label({
      
      LabelNumber:body.LabelNumber,
      LabelName:body.LabelName
      
  });    
  console.log(newlabel);
  newlabel.save().then((result)=>{
      res.send(result);
  },(error)=>{ console.log('error');
      res.status(400).send(error);
      
  });
});


app.patch('/label',(req,res)=>{
  //makes the update of the product
  console.log('patchlabel');
  var body = _.pick(req.body,['labelNumber','labelName']);   
  label.findOneAndUpdate({labelNumber:body.labelNumber},{
       
    labelNumber:body.labelNumber,
    labelName:body.labelName
   
  }).then((result)=>{
      console.log('result');
      res.send(result);
  }).catch((error)=>{
      console.log('error');
      res.send(error);
  });
});


app.get('/labelproduct',(req,res)=>{
  console.log('getlabelproduct');
  labelproduct.find({}).then((result)=>{
      res.send(result);
  });    
});

app.get('/labelproduct/:labelNumber',(req,res)=>{
  var id = req.params.labelNumber;   
  labelproduct.find({labelNumber:Number}).then((result)=>{
      res.send(result);
  }).catch((err)=>{
      res.send(err);
  })

});

app.post('/labelproduct',(req,res)=>{
  //If it can no create a new device, it will
  //update the existing one    
  console.log('postlabelproduct');
  var body = _.pick(req.body,['LabelNumber','ProductSKU']);    
 
  var newlabel = new labelproduct({
      
      LabelNumber:body.LabelNumber,
      ProductSKU:body.ProductSKU
      
  });    
  console.log(newlabel);
  newlabel.save().then((result)=>{
      res.send(result);
  },(error)=>{ console.log('error');
      res.status(400).send(error);
      
  });
});

// edit a labelproduct using put

app.put('/labelproduct',(req,res)=>{
  //If it can no create a new device, it will
  //update the existing one    
  console.log('postlabelproduct');
  var body = _.pick(req.body,['LabelNumber','ProductSKU']);    
 
  var newlabel = new labelproduct({
      
      LabelNumber:body.LabelNumber,
      ProductSKU:body.ProductSKU
      
  });    
  console.log(newlabel);
  newlabel.save().then((result)=>{
      res.send(result);
  },(error)=>{ console.log('error');
      res.status(400).send(error);
      
  });
});

app.patch('/labelproduct',(req,res)=>{
  //makes the update of the product
  console.log('patchlabelproduct');
  var body = _.pick(req.body,['LabelNumber','ProductSKU']);   
  labelproduct.findOneAndUpdate({labelNumber:body.ProductSKU},{
       
    labelNumber:body.labelNumber,
    ProductSKU:body.ProductSKU
   
  }).then((result)=>{
      console.log('result');
      res.send(result);
  }).catch((error)=>{
      console.log('error');
      res.send(error);
  });
});

//Create an endpoint called productForLabel with GET that takes as a parameter the deviceid object



// Adventure.findOne({ type: 'iphone' }, function (err, adventure) {});
app.get('/productForLabel',(req,res)=>{
  var body = _.pick(req.body,['DeviceID']);
 console.log(body.DeviceID)  
  labelproduct.findOne({LabelNumber:body.DeviceID}).then((result)=>{ 
   
   console.log(result.ProductSKU)
   
   product.findOne({SKU:result.ProductSKU}).then((result1)=>{   

    var resultObject = {
      ProductID: result1.ProductID,
      PriceDollar: result1.PriceDollar,
      PriceCents: result1.PriceCents,
      Description: result1.Description,
      SKU: result1.SKU,
      Model: result1.Model,
      DueDate: result1.DueDate,
      LayoutName: result1.LayoutName,
      Update: result1.Update,
      Blink: result1.Blink
    };    
    res.send(resultObject);

   }).catch((err)=>{    
    
  })    
  }).catch((err)=>{
   res.send(err);
 })

});


var listener = app.listen(port, () => {
console.log('Your app is listening on port ' + listener.address().port);
});